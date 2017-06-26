#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>
#include <DgnPlatform\DgnPlatformApi.h>
#include <Mstn\PSolid\mssolid.h>
#include <Mstn\PSolid\mssolid.fdf>
#include <MStn\ElementPropertyUtils.h>
#include <DgnView\AccuDraw.h>

#include <DgnView\DgnElementSetTool.h>
#include <DgnView\DgnRegionElementTool.h>
#include <DgnPlatform\DropGraphics.h>
#include <DgnPlatform\NotificationManager.h>

#include "HelloWorldids.h"

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

struct FloodTool : DgnRegionElementTool
{
private:
	RegionParams m_regionParams;
protected:
	FloodTool(int toolId) : DgnRegionElementTool() { SetCmdName(toolId, 0); }

	virtual bool		_WantFloodDynamicArea() override { return true; }
	virtual RegionCreateMode	_GetRegionCreateMode() override { return DgnRegionElementTool::REGION_CREATE_ByParams; }
	virtual RegionParams const&		_GetRegionParams() override;
	virtual BentleyStatus		_OnProcessRegionResult(EditElementHandleR eeh) override;

	virtual void _OnRestartTool() override;

public:
	static void InstallNewInstance(int toolId);
};