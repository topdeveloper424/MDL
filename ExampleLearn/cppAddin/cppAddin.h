// cppAddin.h

#pragma once

#include <random>	
using namespace System;
using namespace System::Collections::Generic;
namespace BD = Bentley::DgnPlatformNET;
namespace BG = Bentley::GeometryNET;

namespace PDIWTCodeQueryLib
{
	public ref class LayerInfo
	{
	public:
		property String^ LayerNum;
		property double Qfi;
		property double Qri;
		property double Betasi;
		property double Xifi;
		property double Xifi2;
		property double Xii;
		property double PsiSi;

		virtual String^ ToString() override
		{
			return String::Format("Layer Info of {8}:{0}Qfi={1}{0}" +
				"Qri={2}{0}Betasi={3}{0}Xifi={4}{0}Xifi2={5}{0}Xii={6}{0}PsiSi={7}{0}",
				Environment::NewLine,
				Qfi, Qri, Betasi, Xifi, Xifi2, Xii, PsiSi, LayerNum);
		}
	};

	public ref class ColumnLayerInfo
	{
	public:
		property BG::DPoint3d TopPoint;
		property BG::DPoint3d BottomPoint;
		property LayerInfo^ Info;

		void SetTopPoint(DPoint3dCR point)
		{
			TopPoint.Set(point.x, point.y, point.z);
		}

		void SetBottomPoint(DPoint3dCR point)
		{
			TopPoint.Set(point.x, point.y, point.z);
		}

		virtual String^ ToString() override
		{
			Text::StringBuilder^ sb = gcnew Text::StringBuilder();
			sb->Append("Intersect Layer Info:\r\n");
			sb->Append(Info->ToString());
			sb->Append("Intersect TopPoint:\r\n");
			sb->Append(TopPoint.ToString());
			sb->Append("Intersect BottomPoint:\r\n");
			sb->Append(BottomPoint.ToString());
			return sb->ToString();
		}
	};

	public ref class AllLayerInfo
	{
	public:
		property List<LayerInfo^>^ IntersectLayers;
		virtual String^ ToString() override
		{
			auto sb = gcnew Text::StringBuilder();
			sb->Append("\r\n");
			sb->Append(String::Format("Total Number of Intersection Layer is {0}\r\n", IntersectLayers->Count));
			for each (auto layerinfo in IntersectLayers)
			{
				sb->Append(layerinfo->ToString());
			}
			return sb->ToString();
		}
	};

	public enum class PDIWTCodeQueryErrorCode
	{
		Success,
		NotFoundColumn,
		NotFoundLayer,
		NoIntersection,
		UnkonwnError
	};

	public ref class PDIWTQuery
	{
	public:
		PDIWTCodeQueryErrorCode QueryById(AllLayerInfo% result, long id);
	};

	public ref class MeshTest
	{
	public:
		static void ConstructMesh()
		{
			mdlCurrTrans_begin();
			mdlCurrTrans_masterUnitsIdentity(FALSE);
			bvector<DPoint3d> points = { {0,0,0},{10000,0,0},{0,10000,0},{10000,10000,0},{5000,5000,5000} };
			PolyfaceHeaderPtr mesh = PolyfaceHeader::CreateXYTriangulation(points);
			double mesharea;
			DPoint3d meshcentroid;
			RotMatrix meshRotmatrix;
			DVec3d meshmomentxyz;
			mesh->ComputePrincipalAreaMoments(mesharea, meshcentroid, meshRotmatrix, meshmomentxyz);
			EditElementHandle meshHandle;
			DraftingElementSchema::ToElement(meshHandle, *mesh, nullptr, *ACTIVEMODEL);
			mdlDialog_dmsgsPrint(WPrintfString(L"The number area of the mesh is : %d\nThe mesh centroid is :[%d,%d,%d]", mesharea, meshcentroid.x, meshcentroid.y, meshcentroid.z));
			mdlCurrTrans_end();
			meshHandle.AddToModel();
		}
		static void DgnFileTest()
		{
			WString file(L"D:\\闸首切图.dgn");
			DgnDocumentPtr pDoc = DgnDocument::CreateForLocalFile(file.c_str());
			DgnFilePtr dgnFile = DgnFile::Create(*pDoc, DgnFileOpenMode::PreferablyReadWrite);
			DgnFileStatus fileStatus = dgnFile->LoadDgnFile(nullptr);
			if (fileStatus != DgnFileStatus::DGNFILE_STATUS_Success)
			{
				mdlOutput_messageCenter(OutputMessagePriority::Error, L"无法打开文件", WPrintfString(L"%s 打开失败，错误原因%d\n", dgnFile->GetFileName(), fileStatus), OutputMessageAlert::Dialog);
				return;
			}
			dgnFile->FillDictionaryModel();
			dgnFile->ProcessChanges(DgnSaveReason::FileClose, 0);
			dgnFile->DoSaveTo(L"D:\\Test.dgn", DgnFileFormatType::Current);
			//}
		}
		static void DgnModel()
		{
			//DgnFilePtr dgnfile = mdlDgnFileObj_getMasterFile();
			//ModelIndex index = dgnfile->GetModelIndex();
			////WString str;
			////for each (auto model in index)
			////{
			////	str += WString(model.GetName()) + L"\n";
			////}
			//int num = 0;
			//for each (auto model in index)
			//{
			//	num++;
			//}
			//mdlOutput_message(WPrintfString(L"The number of model in dgnfile %s is %d",dgnfile->GetFileName(), num));
			//DgnModelRefR model = *mdlModelRef_getActive();
			//if (nullptr != model.GetDgnAttachmentsCP())
			//{
			//	for each(DgnAttachmentP attachment in *model.GetDgnAttachmentsCP())
			//	{
			//		mdlDialog_dmsgsPrint(WPrintfString(L"Referencing file %s, model %s\n", attachment->GetAttachFileName().c_str(), attachment->GetAttachModelName()));
			//	}
			//}
			DgnFilePtr activeDgnFile = ISessionMgr::GetActiveDgnFile();
			ModelId mId = activeDgnFile->FindModelIdByName(L"平抛");
			if (mId != INVALID_MODELID)
			{
				DgnModelP modelp = activeDgnFile->LoadRootModelById(nullptr, mId, true, true,false);
			}
		}
	};
}