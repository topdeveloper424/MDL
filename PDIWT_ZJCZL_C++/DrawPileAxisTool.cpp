#include "PDIWT_ZJCZL_C++.h"
#include <DgnView\IRedraw.h>
#include <DgnPlatform\CustomItemType.h>
extern PileProperty g_pileProperty;

#define _L(str)	L##str

struct DrawPileAxisTool : DgnPrimitiveTool
{
protected:
	DrawPileAxisTool(int toolName, int toolPrompt) :DgnPrimitiveTool(toolName, toolPrompt), libraryName(L"PDIWT_ZJCZL"),activeDgnFile(*mdlDgnFileObj_getMasterFile())	{}
	virtual void _OnRestartTool() override { InstallNewInstance(CMDNAME_DrawPileAixsLine, PROMPT_FirstPoint); }
	virtual void _OnPostInstall() override;
	virtual bool _OnDataButton(DgnButtonEventCR ev) override;
	virtual bool _OnResetButton(DgnButtonEventCR ev) override;
	virtual void _OnDynamicFrame(DgnButtonEventCR ev) override;
private:
	void SetupAndPromptForNextAction();
	bool CreateLineAxis(EditElementHandleR eeh, bvector<DPoint3d> const& points);
	bool CreateItemType();
	void ApplyPileAxisItemType(EditElementHandleR eeh);
	void ChangePileAxisItemTypeValue(EditElementHandleR eeh);
	WString libraryName;
	DgnFileR activeDgnFile;
	bvector<DPoint3d> m_points;
public:
	static void InstallNewInstance(int toolId, int toolPrompt);
};

void DrawPileAxisTool::_OnPostInstall()
{
	AccuSnap::GetInstance().EnableSnap(true);
	__super::_OnPostInstall();
}

bool DrawPileAxisTool::_OnDataButton(DgnButtonEventCR ev)
{
	if (m_points.empty())
		_BeginDynamics();

	m_points.push_back(*ev.GetPoint());
	SetupAndPromptForNextAction();

	if (m_points.size() < 2)
		return false;

	EditElementHandle eeh;
	if (CreateLineAxis(eeh, m_points))
	{
		ApplyPileAxisItemType(eeh);
		ChangePileAxisItemTypeValue(eeh);
		eeh.AddToModel();
	}

	m_points.clear();
	m_points.push_back(*ev.GetPoint());
	return _CheckSingleShot();
}

bool DrawPileAxisTool::_OnResetButton(DgnButtonEventCR ev)
{
	_OnRestartTool();
	return true;
}

void DrawPileAxisTool::_OnDynamicFrame(DgnButtonEventCR ev)
{
	bvector<DPoint3d> tmpPts = m_points;
	EditElementHandle eeh;

	tmpPts.push_back(*ev.GetPoint());
	if (!CreateLineAxis(eeh, tmpPts))
		return;

	RedrawElems redrawElems;
	redrawElems.SetDynamicsViews(IViewManager::GetActiveViewSet(), ev.GetViewport());
	redrawElems.SetDrawMode(DRAW_MODE_TempDraw);
	redrawElems.SetDrawPurpose(BENTLEY_NAMESPACE_NAME::DgnPlatform::DrawPurpose::Dynamics);

	redrawElems.DoRedraw(eeh);

}

void DrawPileAxisTool::SetupAndPromptForNextAction()
{
	WString msgString;
	RmgrResource::LoadWString(msgString, (RscFileHandle)0, STRINGLISTID_Prompts, 1 == m_points.size() ? PROMPT_FirstPoint : PROMPT_AceeptOrReset);
	NotificationManager::OutputPrompt(msgString.c_str());
	if (2 != m_points.size())
	{
		return;
	}
	DVec3d xVec = DVec3d::FromStartEndNormalize(m_points.front(), m_points.back());
	AccuDraw::GetInstance().SetContext(ACCUDRAW_SetXAxis, nullptr, &xVec);
}

bool DrawPileAxisTool::CreateLineAxis(EditElementHandleR eeh, bvector<DPoint3d> const& points)
{
	if (2 != points.size())
		return false;
	if (SUCCESS != DraftingElementSchema::ToElement(eeh, *ICurvePrimitive::CreateLine(DSegment3d::From(points.front(), points.back())), nullptr, ACTIVEMODEL->Is3d(), *ACTIVEMODEL))
		return false;
	ElementPropertyUtils::ApplyActiveSettings(eeh);
	return true;
}
//! 创建附加在直线上的ItemTypeLibrary和ItemType
bool DrawPileAxisTool::CreateItemType()
{
	ItemTypeLibraryPtr libraryPtr = ItemTypeLibrary::FindByName(libraryName.c_str(), activeDgnFile);
	if (libraryPtr == nullptr)
	{
		libraryPtr = ItemTypeLibrary::Create(libraryName.c_str(), activeDgnFile);
		ItemTypeP pile = libraryPtr->AddItemType(L"PileProperty");
		CustomPropertyP pileProp = pile->AddProperty(L"PileType");
		pileProp->SetType(CustomProperty::Type::String);
		pileProp->SetDefaultValue(ECValue(L"实心桩或桩端封闭"));
		CustomPropertyP pileCrossSection = pile->AddProperty(L"PileCrossSectionType");
		pileCrossSection->SetType(CustomProperty::Type::String);
		pileCrossSection->SetDefaultValue(ECValue(L"方形截面"));
		CustomPropertyP pileCode = pile->AddProperty(L"PileAxisNet(H-V)");
		pileCode->SetType(CustomProperty::Type::String);
		CustomPropertyP pileSideLength = pile->AddProperty(L"PileSideLength(m)");
		pileSideLength->SetType(CustomProperty::Type::Double);
		pileSideLength->SetDefaultValue(ECValue(1.0));
		//pileSideLength->SetUnits(DgnECUnit(DgnECUnit::Distance));
		CustomPropertyP pileWeigth = pile->AddProperty(L"PileWeigth(kN/m)");
		pileWeigth->SetType(CustomProperty::Type::Double);
		pileWeigth->SetDefaultValue(ECValue(25.0));
		CustomPropertyP pileUnderWaterWeight = pile->AddProperty(L"PileUnderWaterWeigth(kN/m)");
		pileUnderWaterWeight->SetType(CustomProperty::Type::Double);
		pileUnderWaterWeight->SetDefaultValue(ECValue(15.0));
	}
	return libraryPtr->Write();
}

void DrawPileAxisTool::ApplyPileAxisItemType(EditElementHandleR eeh)
{
	ItemTypeLibraryPtr libraryPtr = ItemTypeLibrary::FindByName(libraryName.c_str(), activeDgnFile);
	if (libraryPtr == nullptr)
		return;
	ItemTypeCP pile = libraryPtr->GetItemTypeByName(L"PileProperty");
	if (pile == nullptr)
		return;
	CustomItemHost host(eeh);
	DgnECInstancePtr item = host.ApplyCustomItem(*pile);
	//DgnECInstancePtr item = WriteHost.GetCustomItem(libraryName.c_str(), L"PileProperty");
	//item->SetValue(pile->GetPropertyByName(L"PileSideLength(m)")->GetName(), ECValue(g_pileProperty.PileSideLength));
	//item->SetValue(pile->GetPropertyByName(L"PileWeigth(kN/m)")->GetId(), ECValue(g_pileProperty.PileWeight));
	//item->SetValue(pile->GetPropertyByName(L"PileUnderWaterWeigth(kN/m)")->GetId(), ECValue(g_pileProperty.PileUnderWaterWeight));
	//item->ScheduleWriteChanges(eeh);
	//DgnECManagerR ecmanager = DgnECManager::GetManager();
	item->ScheduleWriteChanges(eeh);
}

void DrawPileAxisTool::ChangePileAxisItemTypeValue(EditElementHandleR eeh)
{
	CustomItemHost host(eeh);
	DgnECInstancePtr instance = host.GetCustomItem(libraryName.c_str(), L"PileProperty");
	//----AccessString---
	WString accesstrings[] =
	{
		L"PileType",											//0										
		L"PileCrossSectionType",								//1
		L"PileAxisNet__x0028__H__x002D__V__x0029__",			//2
		L"PileSideLength__x0028__m__x0029__",					//3
		L"PileWeigth__x0028__kN__x002F__m__x0029__",			//4
		L"PileUnderWaterWeigth__x0028__kN__x002F__m__x0029__"	//5
	};
	WString PileTypeStr[] =
	{
		_L("实心桩或桩端封闭"),
		_L("钢管桩与预制混凝土管桩")
	};
	WString PileCrossSectionStr[] =
	{
		_L("环形截面"),
		_L("方型截面"),
		_L("方形空心截面"),
		_L("多边形截面")
	};
	instance->SetValue(accesstrings[0].c_str(), ECValue(PileTypeStr[g_pileProperty.PileType].c_str()));
	instance->SetValue(accesstrings[1].c_str(), ECValue(PileCrossSectionStr[g_pileProperty.PileCrossSection].c_str()));
	instance->SetValue(accesstrings[2].c_str(), ECValue(g_pileProperty.PileCode));
	instance->SetValue(accesstrings[3].c_str(), ECValue(g_pileProperty.PileSideLength));
	instance->SetValue(accesstrings[4].c_str(), ECValue(g_pileProperty.PileWeight));
	instance->SetValue(accesstrings[5].c_str(), ECValue(g_pileProperty.PileUnderWaterWeight));
	instance->ScheduleWriteChanges(eeh);
	//ECClassCR instanceClass = instance->GetClass();
	//ECPropertyIterable properties = instanceClass.GetProperties();
	//for (ECPropertyIterable::const_iterator it_local = properties.begin(); it_local!=properties.end();++it_local)
	//{
	//	ECValue value;
	//	ECPropertyCP pProp = *it_local;
	//	if (SUCCESS == instance->GetValue(value, pProp->GetName().c_str()))
	//	{
	//		WString output = pProp->GetName() + value.ToString();
	//		mdlOutput_messageCenter(OutputMessagePriority::Info, output.c_str(), nullptr, OutputMessageAlert::None);
	//	}

	//}
}

void DrawPileAxisTool::InstallNewInstance(int toolId, int toolPrompt)
{
	auto* tool = new DrawPileAxisTool(toolId, toolPrompt);
	tool->CreateItemType();
	tool->InstallTool();
}

Private void StartDrawPileAxisTool(WCharCP unparsed)
{
	DrawPileAxisTool::InstallNewInstance(CMDNAME_DrawPileAixsLine, PROMPT_FirstPoint);
}
Private void hookItem_GenericImage(DialogItemMessageP dimP)
{
	RawItemHdrP rihP = dimP->dialogItemP->rawItemP;
	dimP->msgUnderstood = true;

	switch (dimP->messageType)
	{
	case DITEM_MESSAGE_CREATE:
	{
		DialogItemP diP = dimP->dialogItemP;
		diP->attributes.acceptsKeystrokes = FALSE;
		diP->attributes.mouseSensitive = FALSE;

		BeFileNameP fullFileSpec = nullptr;
		WChar image[MAXFILELENGTH];
		byte* rgbBuffer = nullptr;

		dimP->u.init.initFailed = true;

		//Get an Image file Name
		WCharCP currentdirectory = _wgetcwd(nullptr, 0);
		mdlOutput_message(currentdirectory);
		wcscpy(image, L"PDIWTLogo.jpg");
		if (SUCCESS == mdlFile_find(fullFileSpec, image, nullptr, nullptr) && fullFileSpec != nullptr)
		{
			WPrintfString outputInfo(L"hookItem_GenericImage: load Image :%s\n", fullFileSpec->GetName());
			mdlOutput_messageCenter(OutputMessagePriority::Info, outputInfo.c_str(), outputInfo.c_str(), OutputMessageAlert::None);
		}
		else
		{
			WPrintfString outputInfo(L"hookItem_GenericImage: problem with image %s\n", image);
			mdlOutput_messageCenter(OutputMessagePriority::Error, outputInfo.c_str(), outputInfo.c_str(), OutputMessageAlert::Balloon);
			dimP->u.init.initFailed = true;
			break;
		}
		Point2d itemSize;
		itemSize.x = diP->rect.corner.x - diP->rect.origin.x + 1;
		itemSize.y = diP->rect.corner.y - diP->rect.origin.y + 1;
		if (SUCCESS == mdlImage_readFileToRGB(&rgbBuffer, nullptr, image, ImageFileFormat::IMAGEFILE_JPEG, nullptr))
		{
			rihP->userDataP = rgbBuffer;
			dimP->u.init.initFailed = FALSE;
		}
		break;
	}
	}
}

Private void hookItem_ComboBox_pileType(DialogItemMessageP dimP)
{
	RawItemHdrP riP = dimP->dialogItemP->rawItemP;

	dimP->msgUnderstood = TRUE;
	switch (dimP->messageType)
	{
	case DITEM_MESSAGE_CREATE:
	{
		ListModelP pListModel = mdlListModel_create(1);
		mdlListModel_insertString(pListModel, L"Fun", -1);
		mdlListModel_insertString(pListModel, L"Test", -1);
		mdlDialog_comboBoxSetListModelP(riP, pListModel);
		break;
	}
	case DITEM_MESSAGE_DESTROY:
	{
		ListModelP pListModel = mdlDialog_comboBoxGetListModelP(riP);
		mdlListModel_destroy(pListModel, true);
		break;
	}
	default:
		dimP->msgUnderstood = FALSE;
		break;;
	}
}