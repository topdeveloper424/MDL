#include "HelloWorld.h"

struct MoveTool:DgnElementSetTool
{
protected:
	Transform m_transform;

	MoveTool(int toolId) : DgnElementSetTool(toolId){}

	virtual bool	_SetupForModify(DgnButtonEventCR ev, bool isDynamics) override;
	virtual StatusInt	_OnElementModify(EditElementHandleR el) override;
	virtual void	_OnRestartTool() override;

public:
	static void InstallNewInstance(int toolId);
};

bool MoveTool::_SetupForModify(DgnButtonEventCR ev, bool isDynamics)
{
	DPoint3d anchorPt;
	if (!_GetAnchorPoint(&anchorPt))
	{
		return false;
	}
	DVec3d vec;
	vec.DifferenceOf(*ev.GetPoint(), anchorPt);
	m_transform.InitFrom(vec);
	return true;

}

BENTLEY_NAMESPACE_NAME::StatusInt MoveTool::_OnElementModify(EditElementHandleR el)
{
	TransformInfo tInfo(m_transform);
	return el.GetHandler(MISSING_HANDLER_PERMISSION_Transform).ApplyTransform(el, tInfo);
}

void MoveTool::_OnRestartTool()
{
	InstallNewInstance(GetToolId());
}

void MoveTool::InstallNewInstance(int toolId)
{
	MoveTool* tool = new MoveTool(toolId);
	tool->InstallTool();
}

void StartMoveTool(WCharCP unparsed)
{
	MoveTool::InstallNewInstance(CMDNAME_MoveTool);
}