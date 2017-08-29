#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>
#include <DgnPlatform\DgnPlatformApi.h>
#include <Mstn\PSolid\mssolid.h>
#include <Mstn\PSolid\mssolid.fdf>

#include <DgnView\DgnElementSetTool.h>
#include <DgnView\DgnTool.h>
#include <DgnView\AccuDraw.h>
#include <DgnView\AccuSnap.h>

#include <list>
#include <fstream>
#include <cmath>

#include "PDIWT_Gadgetcmd.h"
#include "PDIWT_Gadgetids.h"

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

#define Private
/************************************************************************/
/* Commnad Function														*/
/************************************************************************/
Private void ParallelArea(WCharCP);
Private void ShowLevelBox(WCharCP);
Private void CreateTable(WCharCP);
/************************************************************************/
/* Hook Function														*/
/************************************************************************/
void dgnLevel_optionBtnHook(DialogItemMessageP);
