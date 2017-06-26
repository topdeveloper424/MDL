#include "FloodTool.h"


RegionParams const& FloodTool::_GetRegionParams()
{
	m_regionParams.SetType(RegionType::Flood);
	m_regionParams.SetFloodParams(RegionLoops::Outer, 0);
	return m_regionParams;
}

BentleyStatus FloodTool::_OnProcessRegionResult(EditElementHandleR eeh)
{
	ElementPropertyUtils::ApplyActiveSettings(eeh);
	ElementPropertyUtils::ApplyActiveAreaSettings(eeh,-1);

	eeh.AddToModel();
	return SUCCESS;
}

void FloodTool::_OnRestartTool()
{
	InstallNewInstance(GetToolId());
}

void FloodTool::InstallNewInstance(int toolId)
{
	FloodTool* tool = new FloodTool(toolId);
	tool->InstallTool();
}
