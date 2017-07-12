#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>
#include <DgnPlatform\DgnPlatformApi.h>
#include <DgnView\AccuDraw.h>
#include <DgnView\AccuSnap.h>

#include <Mstn\PSolid\mssolid.h>
#include <Mstn\PSolid\mssolid.fdf>

#include "chinese/PDIWT_ZJCZL_C++txt.h"
#include "PDIWT_ZJCZL_C++cmd.h"
#include "PDIWT_ZJCZL_C++ids.h"

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT
USING_NAMESPACE_BENTLEY_ECOBJECT

#define Private

/************************************************************************/
/* Command Function														*/
/************************************************************************/
Private void StartDrawPileAxisTool(WCharCP);
Private void OpenInfoBox(WCharCP);

/************************************************************************/
/* Hook Function														*/
/************************************************************************/
Private void hookItem_GenericImage(DialogItemMessageP);
Private void hookItem_ComboBox_pileType(DialogItemMessageP);
