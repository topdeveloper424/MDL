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
#include "HelloWorldcmd.h"

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

void OutPutMsg(WCharCP );
void ScanTest(WCharCP );
void StartTool(WCharCP );
void CreateLineTool(WCharCP);
void StartFloodTool(WCharCP);
void StartMoveTool(WCharCP);

void TestCase1(WCharCP);
void TestCase2(WCharCP);
void TestCase3(WCharCP);