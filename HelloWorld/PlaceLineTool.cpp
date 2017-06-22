#include "PlaceLineTool.h"


void PlaceLineTool::_OnPostInstall()
{
	AccuSnap::GetInstance().EnableSnap(true);
	__super::_OnPostInstall();
}

void PlaceLineTool::_OnRestartTool()
{
	PlaceLineTool::InstallNewInstance(CMDNAME_PlaceBsSurfaceTool, PROMPT_FirstPoint);
}

bool PlaceLineTool::_OnDataButton(DgnButtonEventCR ev)
{
	if (0==m_points.size())
	{
		_BeginDynamics();
		EnableUndoPreviousStep();
	}
	m_points.push_back(*ev.GetPoint());
	SetupAndPromptForNextAction();
	CreateAcceptedSegmentsTransient();
	return false;
}

bool PlaceLineTool::_OnResetButton(DgnButtonEventCR ev)
{
	EditElementHandle eeh;
	if (CreateElement(eeh, m_points))
		eeh.AddToModel();

	_OnReinitialize();

	return true;
}

void PlaceLineTool::_OnDynamicFrame(DgnButtonEventCR ev)
{
	if (m_points.size() < 1)
		return;
	bvector<DPoint3d> tmpPts;
	EditElementHandle eeh;
	tmpPts.push_back(m_points.back());
	tmpPts.push_back(*ev.GetPoint());

	if (!CreateElement(eeh,tmpPts))
	{
		return;
	}

	RedrawElems  redrawElems;
	redrawElems.SetDynamicsViews(IViewManager::GetActiveViewSet(), ev.GetViewport());
	redrawElems.SetDrawMode(DgnDrawMode::DRAW_MODE_TempDraw);
	redrawElems.SetDrawPurpose(DrawPurpose::Dynamics);

	redrawElems.DoRedraw(eeh);
}

void PlaceLineTool::_OnUndoPreviousStep()
{
	if (m_points.size() < 2)
	{
		_OnRestartTool();
		return;
	}
	m_points.pop_back();
	SetupAndPromptForNextAction();
	CreateAcceptedSegmentsTransient();
}

bool PlaceLineTool::CreateElement(EditElementHandleR eeh, bvector<DPoint3d> const & points)
{
	if (points.size() < 2)
		return false;

	if (SUCCESS != DraftingElementSchema::ToElement(eeh, *ICurvePrimitive::CreateLineString(points), NULL, ACTIVEMODEL->Is3d(),
		*ACTIVEMODEL))
		return false;

	return true;
}

void PlaceLineTool::CreateAcceptedSegmentsTransient()
{
	EditElementHandle eeh;

	mdlTransient_free(&msTransientElmP, true);
	if (CreateElement(eeh, m_points))
		msTransientElmP = mdlTransient_addElemDescr(msTransientElmP, eeh.GetElementDescrP(), true, 0xffff, DRAW_MODE_Normal, false, false, true);
}


void PlaceLineTool::SetupAndPromptForNextAction()
{
	WString msgStr;

	RmgrResource::LoadWString(msgStr, (RscFileHandle)0, STRINGLISTID_Prompts, 1 == m_points.size() ? PROMPT_FirstPoint : PROMPT_NextPointOrReset, GetMdlDesc());
	NotificationManager::OutputPrompt(msgStr.c_str());

	if (m_points.size()<1)
		return;

	DVec3d	xVec = DVec3d::From(DVec3d::FromZero());
	DPoint3d origin = m_points.back();
	AccuDrawFlags flags = ACCUDRAW_SetOrigin;
	if (m_points.size()>1)
	{
		xVec = DVec3d::FromStartEndNormalize(m_points.back(), *(&m_points.back() - 1));
		flags = (AccuDrawFlags)(flags | ACCUDRAW_SetXAxis);
	}
	AccuDraw::GetInstance().SetContext(flags, &origin, &xVec);
}

void PlaceLineTool::InstallNewInstance(int toolId, int toolPrompt)
{
	PlaceLineTool* tool = new PlaceLineTool(toolId, toolPrompt);
	tool->InstallTool();
}

void CreateLine2Tool::_OnPostInstall()
{
	AccuSnap::GetInstance().EnableSnap(true);

	__super::_OnPostInstall();
}

void CreateLine2Tool::_OnRestartTool()
{
	InstallNewInstance(GetToolId(), GetToolPrompt());
}

bool CreateLine2Tool::_OnDataButton(DgnButtonEventCR ev)
{
	if (0 == m_points.size())
		_BeginDynamics();

	m_points.push_back(*ev.GetPoint());
	SetupAndPromptForNextAction();

	if (m_points.size() < 2)
		return false;
	EditElementHandle eeh;
	if (CreateElement(eeh, m_points))
		eeh.AddToModel();

	m_points.clear();
	m_points.push_back(*ev.GetPoint());
	return _CheckSingleShot();
}

bool CreateLine2Tool::_OnResetButton(DgnButtonEventCR ev)
{
	_OnRestartTool();
	return true;
}

void CreateLine2Tool::_OnDynamicFrame(DgnButtonEventCR ev)
{
	bvector<DPoint3d> tmpPts = m_points;
	EditElementHandle eeh;

	tmpPts.push_back(*ev.GetPoint());

	if(!CreateElement(eeh,tmpPts))
		return;

	RedrawElems redrawElems;
	redrawElems.SetDynamicsViews(IViewManager::GetActiveViewSet(), ev.GetViewport());
	redrawElems.SetDrawMode(DRAW_MODE_TempDraw);
	redrawElems.SetDrawPurpose(DrawPurpose::Dynamics);

	redrawElems.DoRedraw(eeh);
}

bool CreateLine2Tool::CreateElement(EditElementHandleR eeh, bvector<DPoint3d> const & points)
{
	if (2 != points.size())
		return false;

	if (SUCCESS != DraftingElementSchema::ToElement(eeh, *ICurvePrimitive::CreateLine(DSegment3d::From(points.front(), points.back())), NULL, ACTIVEMODEL->Is3d(), *ACTIVEMODEL))
		return false;
	ElementPropertyUtils::ApplyActiveSettings(eeh);
	return true;
}

void CreateLine2Tool::SetupAndPromptForNextAction()
{
	WChar msgStr[128];
	RmgrResource::LoadFromStringList(msgStr, (RscFileHandle)0, STRINGLISTID_Prompts, 1 == m_points.size() ? PROMPT_FirstPoint : PROMPT_NextPointOrReset);
	NotificationManager::OutputPrompt(msgStr);

	if (2!=m_points.size())
	{
		return;
	}
	DVec3d xVec = DVec3d::FromStartEndNormalize(m_points.front(), m_points.back());
	AccuDraw::GetInstance().SetContext(ACCUDRAW_SetXAxis, NULL,&xVec);
}

void CreateLine2Tool::InstallNewInstance(int toolId, int toolPrompt)
{
	CreateLine2Tool* tool = new CreateLine2Tool(toolId, toolPrompt);
	tool->InstallTool();
}
