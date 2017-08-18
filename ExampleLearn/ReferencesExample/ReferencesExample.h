#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>
#include <DgnPlatform\DgnPlatformApi.h>
#include <Mstn\PSolid\mssolid.h>
#include <Mstn\PSolid\mssolid.fdf>

#include "ReferencesExampleids.h"
#include "ReferencesExamplecmd.h"

#include <random>
#include <chrono>

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

class ReferenceExample
{
public:
	ReferenceExample() : s_commandFlages(CommandFlags_Start) {}

	enum ExampleCommandValidityFlags
	{
		CommandFlags_Start,
		CommandFlags_ModelsCreated,
		CommandFlags_ReferencesCreated,
		CommandFlags_NestedReferencesShown,
		CommandFlags_ParallelReferencesShown
	};
	enum ExampleCommandOptions
	{
		CommandOptions_CreateModels,
		CommandOptions_CreateReferences,
		CommandOptions_ShowReferences,
		CommandOptions_ManipulateReference
	};
private:
	void DeleteModelIfExist()
	{

		DgnFileP activeDgnFile = ISessionMgr::GetActiveDgnFile();
		for each (auto modelname in modelNames)
		{
			ModelId mId = activeDgnFile->FindModelIdByName(modelname);
			if (mId != INVALID_MODELID)
			{
				DgnModelPtr someModel = activeDgnFile->LoadRootModelById(nullptr, mId);
				activeDgnFile->DeleteModel(*someModel);	//acturelly delete
			}
		}
	}

	void CreateReference(DgnModelRefR modelRef, DgnFileR activeDgnFile, WCharCP modelToAttach)
	{
		DgnAttachmentP refToCreate;
		modelRef.CreateDgnAttachment(refToCreate, *(activeDgnFile.GetDocument().GetMonikerPtr()), modelToAttach);
		refToCreate->SetNestDepth(99);
		refToCreate->WriteToModel();
	}

	void CreateGeometry(DgnModelR model, int someNumber)
	{
		double x = someNumber * 200;
		DPoint3d points[] = { {x,0,0},{x + 100,0,0},{x + 100,100,0},{x,100,0},{x,0,0} };
		EditElementHandle eeh;
		ShapeHandler::CreateShapeElement(eeh, nullptr, points, 5, model.Is3d(), model);

		ElementPropertiesSetterPtr remapper = ElementPropertiesSetter::Create();
		remapper->SetColor(UInt32(someNumber));
		remapper->Apply(eeh);
		eeh.AddToModel();
	}

	DgnAttachmentP GetDgnAttachmentByAttachedModelName(WCharCP modelName)
	{
		DgnAttachmentP requiredRef = nullptr;

		DgnFileP activeDgnFile = ISessionMgr::GetActiveDgnFile();
		ModelId mIdParallel = activeDgnFile->FindModelIdByName(s_mainModelParallel.c_str());
		if (mIdParallel != INVALID_MODELID)
		{
			DgnModelPtr mainModelParallel = activeDgnFile->LoadRootModelById(nullptr, mIdParallel, true, true, true);
			{
				for (DgnAttachmentP attachment : *(mainModelParallel->GetDgnAttachmentsP()))
				{
					if (0 == wcscmp(modelName, attachment->GetAttachModelName()))
					{
						requiredRef = attachment;
						break;
					}
				}
			}
		}
		return requiredRef;
	}

	bool IsCommandValid(ExampleCommandOptions commandOp)
	{
		WString errorMessage = L"";
		WString notCreateModel = L"Models are not created. Please create model first";
		WString notCreateReference = L"References are not created. Please create reference first.";
		//! "Create Model" command is always valid.
		if (CommandOptions_CreateModels == commandOp)
			return true;
		else if (CommandOptions_CreateReferences == commandOp)
		{
			if (CommandFlags_ModelsCreated == s_commandFlages)
				return true;
			else if (CommandFlags_Start == s_commandFlages)
				errorMessage = notCreateModel;
			else
				errorMessage = L"References are already created. Go ahead with manipulating them.";
		}
		else if (CommandOptions_ShowReferences == commandOp)
		{
			if (CommandFlags_Start == s_commandFlages)
				errorMessage = notCreateModel;
			else if (CommandFlags_ModelsCreated == s_commandFlages)
				errorMessage = notCreateReference;
			else
				return true;
		}
		else if (CommandOptions_ManipulateReference == commandOp)
		{
			if (CommandFlags_ParallelReferencesShown == s_commandFlages)
				return true;
			else if (CommandFlags_Start == s_commandFlages)
				errorMessage = notCreateModel;
			else if (CommandFlags_ModelsCreated == s_commandFlages)
				errorMessage = notCreateReference;
			else
				errorMessage = L"Parallel References are not shown. Please issue the command \"SHOWREFERENCES Parallel\" first";
		}
		mdlOutput_messageCenter(OutputMessagePriority::TempRight, errorMessage.c_str(), nullptr, OutputMessageAlert::Balloon);
		return false;
	}
public:
	void CreateModels()
	{
		if (IsCommandValid(CommandOptions_CreateModels))
		{
			DeleteModelIfExist();
			DgnFilePtr activeDgnFile = ISessionMgr::GetActiveDgnFile();
			long long seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::default_random_engine generator(seed);
			for each (auto modelName in modelNames)
			{
				DgnModelPtr model = activeDgnFile->CreateNewModel(nullptr, modelName, DgnModelType::Normal, true);
				CreateGeometry(*model, generator() % 5);
			}
			s_commandFlages = CommandFlags_ModelsCreated;
		}
	}

	void CreateReferences()
	{
		if (IsCommandValid(CommandOptions_CreateReferences))
		{
			DgnFilePtr activeDgnFile = ISessionMgr::GetActiveDgnFile();
			ModelId mIdParallel = activeDgnFile->FindModelIdByName(s_mainModelParallel.c_str());
			if (INVALID_MODELID != mIdParallel)
			{
				DgnModelPtr mainModelParallel = activeDgnFile->LoadRootModelById(nullptr, mIdParallel, true, true, true);

				CreateReference(*mainModelParallel, *activeDgnFile, s_childModelParallel1.c_str());
				CreateReference(*mainModelParallel, *activeDgnFile, s_childModelParallel2.c_str());
				CreateReference(*mainModelParallel, *activeDgnFile, s_childModelParallel3.c_str());
				CreateReference(*mainModelParallel, *activeDgnFile, s_childModelParallel4.c_str());
			}
			WCharCP nestedModelNames[] =
			{
				s_childModelNested4.c_str(),
				s_childModelNested3.c_str(),
				s_childModelNested2.c_str(),
				s_childModelNested1.c_str(),
				s_mainModelNested.c_str()
			};
			for (int i = 1; i < 5; i++)
			{
				ModelId mIdNested = activeDgnFile->FindModelIdByName(nestedModelNames[i]);
				if (INVALID_MODELID != mIdNested)
				{
					DgnModelPtr modelNested = activeDgnFile->LoadRootModelById(nullptr, mIdNested, true, true, true);
					CreateReference(*modelNested, *activeDgnFile, nestedModelNames[i - 1]);
				}
			}
			s_commandFlages = CommandFlags_ReferencesCreated;
		}
	}

	void ScaleReference()
	{
		if (IsCommandValid(CommandOptions_ManipulateReference))
		{
			DgnAttachmentP requiredRef = GetDgnAttachmentByAttachedModelName(s_childModelParallel1.c_str());
			if (nullptr != requiredRef)
			{
				double newScale = (1 == int(requiredRef->GetStoredScale())) ? 2 : 1;
				requiredRef->SetStoredScale(newScale);
				requiredRef->WriteToModel();
			}
		}
	}

	void RotateReference()
	{
		if (IsCommandValid(CommandOptions_ManipulateReference))
		{
			DgnAttachmentP requiredRef = GetDgnAttachmentByAttachedModelName(s_childModelParallel2.c_str());
			if (nullptr != requiredRef)
			{
				DVec3d axis = DVec3d::UnitZ();
				RotMatrix rotation = (requiredRef->GetRotMatrix().IsIdentity()) ? RotMatrix::FromVectorAndRotationAngle(axis, fc_piover4) : RotMatrix::FromIdentity();
				requiredRef->SetRotMatrix(rotation);
				requiredRef->WriteToModel();
			}
		}
	}

	void ClipReference()
	{
		if (IsCommandValid(CommandOptions_ManipulateReference))
		{
			DgnAttachmentP requiredRef = GetDgnAttachmentByAttachedModelName(s_childModelParallel3.c_str());
			if (nullptr != requiredRef)
			{
				if (requiredRef->IsClipped())
				{
					requiredRef->SetClipPoints(nullptr, 0);
				}
				else
				{
					double x = 550;
					bvector<DPoint2d> points = { {x,-100},{x + 100,-100},{x + 100,200},{x,200},{x,-100} };
					requiredRef->SetClipPoints(&points[0], UInt32(points.size()));
				}
				requiredRef->WriteToModel();
			}
		}
	}

	void ShowReferences(bool nestedRefs)
	{
		if (IsCommandValid(CommandOptions_ShowReferences))
		{
			WString modelToActivate = nestedRefs ? s_mainModelNested : s_mainModelParallel;
			DgnFileP activeDgnFile = ISessionMgr::GetActiveDgnFile();
			DgnModelRefP model;
			mdlModelRef_createWorkingByName(&model, activeDgnFile, modelToActivate.c_str(), true, true);
			mdlModelRef_activateAndDisplay(model);
			s_commandFlages = nestedRefs ? CommandFlags_NestedReferencesShown : CommandFlags_ParallelReferencesShown;
		}
	}
private:
	WString s_mainModelParallel = L"MainModelParallel";
	WString s_childModelParallel1 = L"ChildModelParallel1";
	WString s_childModelParallel2 = L"ChildModelParallel2";
	WString s_childModelParallel3 = L"ChildModelParallel3";
	WString s_childModelParallel4 = L"ChildModelParallel4";

	WString s_mainModelNested = L"MainModelNested";
	WString s_childModelNested1 = L"ChildModelNested1";
	WString s_childModelNested2 = L"ChildModelNested2";
	WString s_childModelNested3 = L"ChildModelNested3";
	WString s_childModelNested4 = L"ChildModelNested4";

	WCharCP modelNames[10] =
	{
		s_mainModelParallel.c_str(),
		s_childModelParallel1.c_str(),
		s_childModelParallel2.c_str(),
		s_childModelParallel3.c_str(),
		s_childModelParallel4.c_str(),
		s_mainModelNested.c_str(),
		s_childModelNested1.c_str(),
		s_childModelNested2.c_str(),
		s_childModelNested3.c_str(),
		s_childModelNested4.c_str()
	};

	ExampleCommandValidityFlags s_commandFlages;
};


Public ReferenceExample	refexample;

Public void referenceExample_CreateModel(WCharCP)
{
	refexample.CreateModels();
}
Public void referenceExample_CreateReference(WCharCP)
{
	refexample.CreateReferences();
}
Public void referenceExample_ScaleReference(WCharCP)
{
	refexample.ScaleReference();
}
Public void referenceExample_RotateReference(WCharCP)
{
	refexample.RotateReference();
}
Public void referenceExample_ClipReference(WCharCP)
{
	refexample.ClipReference();
}
Public void referenceExample_ShowParallelReferences(WCharCP)
{
	refexample.ShowReferences(false);
}
Public void referenceExample_ShowNestedReferences(WCharCP)
{
	refexample.ShowReferences(true);
}