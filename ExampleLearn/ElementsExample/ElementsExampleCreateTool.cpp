#include "ElementsExample.h"

class ElementsCreateHelper
{
public:
	static bool CreateShapeElement(EditElementHandleR eeh, bvector<DPoint3d> points, bool applyActiveSettings);
	static bool CreateMultilineElement(EditElementHandleR eeh, bvector<DPoint3d> points, bool applyActiveSettings);
	static void SetElementProperties(EditElementHandleR eeh, WCharCP unparsed);
};

bool ElementsCreateHelper::CreateShapeElement(EditElementHandleR eeh, bvector<DPoint3d> points, bool applyActiveSettings)
{
	DgnModelP model = ISessionMgr::GetActiveDgnModelP();

	if (SUCCESS != ShapeHandler::CreateShapeElement(eeh, nullptr, points.data(), points.size(), model->Is3d(), *model))
		return false;

	if (applyActiveSettings)
		ElementPropertyUtils::ApplyActiveSettings(eeh);

	return true;
}

bool ElementsCreateHelper::CreateMultilineElement(EditElementHandleR eeh, bvector<DPoint3d> points, bool applyActiveSettings)
{
	DgnModelP model = ISessionMgr::GetActiveDgnModelP();

	double styleScale = 1.0;
	DVec3d normal = DVec3d::From(0, 0, 1);
	MultilineStylePtr activeStyle = MultilineStyle::GetSettings(*(ISessionMgr::GetActiveDgnFile()));

	if (SUCCESS != MultilineHandler::CreateMultilineElement(eeh, nullptr, *activeStyle, styleScale, normal, points.data(), (int)points.size(), model->Is3d(), *model))
		return false;

	if (applyActiveSettings)
		ElementPropertyUtils::ApplyActiveSettings(eeh);

	return true;
}

void ElementsCreateHelper::SetElementProperties(EditElementHandleR eeh, WCharCP unparsed)
{
	int value = -1;
	swscanf(unparsed, L"%ld", &value);
	if (-1 < value)
	{
		UInt32 color = (UInt32)(value % 256);
		UInt32 weight = (UInt32)(value % 32);
		Int32 style = (Int32)(value % 8);

		ElementPropertiesSetterPtr remapper = ElementPropertiesSetter::Create();
		remapper->SetColor(color);
		remapper->SetWeight(weight);
		remapper->SetLinestyle(style, nullptr);
		remapper->Apply(eeh);
	}
}

enum ElementPropsOptions
{
	ElementPropsOptions_None,
	ElementPropsOptions_Custom,
	ElementPropsOptions_Active
};

struct ElementsExampleCreateShapeTool :DgnPrimitiveTool
{
protected:
	ElementPropsOptions m_elemProps;
	WString	m_propertystring;

	bvector<DPoint3d> m_points;

	ElementsExampleCreateShapeTool(int toolName, int toolPrompt, ElementPropsOptions elemProps) :DgnPrimitiveTool(toolName, toolPrompt), m_elemProps(elemProps) {}

	virtual void _OnPostInstall() override;
	virtual void _OnRestartTool()override;
	virtual bool _OnDataButton(DgnButtonEventCR ev) override;
	virtual bool _OnResetButton(DgnButtonEventCR ev) override;
	virtual void _OnDynamicFrame(DgnButtonEventCR ev) override;

	bool CreateShapeElement(EditElementHandleR eeh, bvector<DPoint3d> const& points);
	void SetupAndPromptForNextAction();
	void SetPropertyString(WCharCP unparsed);
public:
	static void InstallNewInstance(int toolId, int toolPrompt, ElementPropsOptions eleProps, WCharCP unparsed);
};

void ElementsExampleCreateShapeTool::_OnPostInstall()
{
	AccuSnap::GetInstance().EnableSnap(true);

	__super::_OnPostInstall();
}

void ElementsExampleCreateShapeTool::_OnRestartTool()
{
	InstallNewInstance(GetToolId(), GetToolPrompt(), m_elemProps, m_propertystring.c_str());
}

bool ElementsExampleCreateShapeTool::_OnDataButton(DgnButtonEventCR ev)
{
	if (0 == m_points.size())
		_BeginDynamics();
	m_points.push_back(*ev.GetPoint());
	SetupAndPromptForNextAction();
	if (m_points.size() < 2)
		return false;

	EditElementHandle eeh;

	if (CreateShapeElement(eeh, m_points))
		eeh.AddToModel();

	m_points.clear();

	return _CheckSingleShot();
}

bool ElementsExampleCreateShapeTool::_OnResetButton(DgnButtonEventCR ev)
{
	_OnRestartTool();
	return true;
}

void ElementsExampleCreateShapeTool::_OnDynamicFrame(DgnButtonEventCR ev)
{
	bvector<DPoint3d> tmpPts = m_points;
	EditElementHandle eeh;

	tmpPts.push_back(*ev.GetPoint());

	if (!CreateShapeElement(eeh, tmpPts))
		return;

	RedrawElems redrawElems;
	redrawElems.SetDynamicsViews(IViewManager::GetActiveViewSet(), ev.GetViewport());
	redrawElems.SetDrawMode(BENTLEY_NAMESPACE_NAME::DgnPlatform::DRAW_MODE_TempDraw);
	redrawElems.SetDrawPurpose(BENTLEY_NAMESPACE_NAME::DgnPlatform::DrawPurpose::Dynamics);

	redrawElems.DoRedraw(eeh);
}

bool ElementsExampleCreateShapeTool::CreateShapeElement(EditElementHandleR eeh, bvector<DPoint3d> const& points)
{
	if (2 != points.size())
		return false;

	bvector<DPoint3d> somePoints;
	somePoints.push_back(points.at(0));
	somePoints.push_back(points.at(1));
	somePoints.push_back(points.at(1));
	somePoints.push_back(points.at(1));
	somePoints.push_back(points.at(0));

	somePoints[1].y = somePoints[0].y;
	somePoints[3].x = somePoints[0].x;

	bool applyActiveSettings = (ElementPropsOptions::ElementPropsOptions_Active == m_elemProps) ? true : false;

	if (!ElementsCreateHelper::CreateShapeElement(eeh, somePoints, applyActiveSettings))
		return false;

	if (ElementPropsOptions_Custom == m_elemProps)
		ElementsCreateHelper::SetElementProperties(eeh, m_propertystring.c_str());
	return true;
}

void ElementsExampleCreateShapeTool::SetupAndPromptForNextAction()
{
	UInt32 msgId;
	msgId = PROMPT_FristPoint;

	if (0 != m_points.size())
		msgId = PROMPT_OppsiteCorner;

	mdlOutput_rscPrintf(MSG_PROMPT, NULL, STRINGLISTID_Prompts, msgId);
}

void ElementsExampleCreateShapeTool::SetPropertyString(WCharCP unparsed)
{
	m_propertystring = unparsed;
}

void ElementsExampleCreateShapeTool::InstallNewInstance(int toolId, int toolPrompt, ElementPropsOptions eleProps, WCharCP unparsed)
{
	auto* tool = new ElementsExampleCreateShapeTool(toolId, toolPrompt, eleProps);

	if (ElementPropsOptions_Custom == eleProps)
		tool->SetPropertyString(unparsed);

	tool->InstallTool();
}
void elementsExampleCreateShapeNone(WCharCP unparsed)
{
	ElementsExampleCreateShapeTool::InstallNewInstance(CMDNAME_ElementsExampleCreateShapeNone, PROMPT_FristPoint, ElementPropsOptions_None, unparsed);
}
void elementsExampleCreateShapeActive(WCharCP unparsed)
{
	ElementsExampleCreateShapeTool::InstallNewInstance(CMDNAME_ElementsExampleCreateShapeActive, PROMPT_FristPoint, ElementPropsOptions_Active, unparsed);
}
void elementsExampleCreateShapeCustom(WCharCP unparsed)
{
	ElementsExampleCreateShapeTool::InstallNewInstance(CMDNAME_ElementsExampleCreateShapeCustom, PROMPT_FristPoint, ElementPropsOptions_Custom, unparsed);
}

//  [6/27/2017 sudongsheng]
//	Create MultilineElements
//

struct ElementsExampleCreateMlineTool:DgnPrimitiveTool
{
protected:
	ElementPropsOptions m_elemProps;
	WString m_propertyString;
	bvector<Dpoint3d> m_points;

	ElementsExampleCreateMlineTool(int toolName, int toolPrompt, ElementPropsOptions elemProps) : DgnPrimitiveTool(toolName, toolPrompt), m_elemProps(elemProps){}

	virtual void _OnPostInstall() override;
	virtual void _OnRestartTool() override;
	virtual bool _OnDataButton(DgnButtonEventCR ev) override;
	virtual bool _OnResetButton(DgnButtonEventCR ev) override;
	virtual void _OnDynamicFrame(DgnButtonEventCR ev) override;

	bool CreateMlineElement(EditElementHandleR eeh, bvector<Dpoint3d> const& points);
	void SetupAndPromptForNextAction();
	void SetPropertyString(WCharCP unparsed);

public:
	static void InstallNewInstance(int toolId, int toolPrompt, ElementPropsOptions elemProps, WCharCP unparsed);
};

void ElementsExampleCreateMlineTool::InstallNewInstance(int toolId, int toolPrompt, ElementPropsOptions elemProps, WCharCP unparsed)
{
	ElementsExampleCreateMlineTool* tool = new ElementsExampleCreateMlineTool(toolId, toolPrompt, elemProps);

	if (elemProps == ElementPropsOptions_Custom)
		tool->SetPropertyString(unparsed);

	tool->InstallTool();
}

void ElementsExampleCreateMlineTool::_OnPostInstall()
{
	AccuSnap::GetInstance().EnableSnap(true);

	__super::_OnPostInstall();
}

void ElementsExampleCreateMlineTool::_OnRestartTool()
{
	InstallNewInstance(GetToolId(), GetToolPrompt(), m_elemProps, m_propertyString.c_str());
}

bool ElementsExampleCreateMlineTool::_OnDataButton(DgnButtonEventCR ev)
{
	m_points.push_back(*ev.GetPoint());
	if (1 == m_points.size())
		_BeginDynamics();

	SetupAndPromptForNextAction();

	return false;
}

bool ElementsExampleCreateMlineTool::_OnResetButton(DgnButtonEventCR ev)
{
	EditElementHandle eeh;
	if (CreateMlineElement(eeh, m_points))
		eeh.AddToModel();

	_OnRestartTool();

	return true;
}

void ElementsExampleCreateMlineTool::_OnDynamicFrame(DgnButtonEventCR ev)
{
	bvector<DPoint3d> tmpPts = m_points;
	EditElementHandle eeh;
	
	tmpPts.push_back(*ev.GetPoint());

	if (!CreateMlineElement(eeh, tmpPts))
		return;

	RedrawElems redrawElems;

	redrawElems.SetDynamicsViews(IViewManager::GetActiveViewSet(), ev.GetViewport());
	redrawElems.SetDrawMode(BENTLEY_NAMESPACE_NAME::DgnPlatform::DRAW_MODE_TempDraw);
	redrawElems.SetDrawPurpose(BENTLEY_NAMESPACE_NAME::DgnPlatform::DrawPurpose::Dynamics);

	redrawElems.DoRedraw(eeh);
}

bool ElementsExampleCreateMlineTool::CreateMlineElement(EditElementHandleR eeh, bvector<Dpoint3d> const& points)
{
	if (points.size() < 2)
		return false;

	bool applyActiveSettings = (m_elemProps == ElementPropsOptions_Active) ? true : false;
	if (!ElementsCreateHelper::CreateMultilineElement(eeh, points, applyActiveSettings))
		return false;

	if (m_elemProps == ElementPropsOptions_Custom)
		ElementsCreateHelper::SetElementProperties(eeh,m_propertyString.c_str());

	return true;
}

void ElementsExampleCreateMlineTool::SetupAndPromptForNextAction()
{
	UInt32 msgId;
	msgId = PROMPT_FristPoint;

	if (1 == m_points.size())
		msgId = PROMPT_NextPoint;
	else
		msgId = PROMPT_NextPointOrReset;

	mdlOutput_rscPrintf(MSG_PROMPT, NULL, STRINGLISTID_Prompts, msgId);
}

void ElementsExampleCreateMlineTool::SetPropertyString(WCharCP unparsed)
{
	m_propertyString = unparsed;
}

void elementsExampleCreateMlineNone(WCharCP unparsed)
{
	ElementsExampleCreateMlineTool::InstallNewInstance(CMDNAME_ElementsExampleCreateMlineNone, PROMPT_FristPoint, ElementPropsOptions_None, unparsed);
}
void elementsExampleCreateMlineActive(WCharCP unparsed)
{
	ElementsExampleCreateMlineTool::InstallNewInstance(CMDNAME_ElementsExampleCreateMlineActive, PROMPT_FristPoint, ElementPropsOptions_Active, unparsed);
}
void elementsExampleCreateMlineCustom(WCharCP unparsed)
{
	ElementsExampleCreateMlineTool::InstallNewInstance(CMDNAME_ElementsExampleCreateMlineCustom, PROMPT_FristPoint, ElementPropsOptions_Custom, unparsed);
}
