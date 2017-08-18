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

#include "DgnElementSetToolTestcmd.h"
#include "DgnElementSetToolTestids.h"

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

/************************************************************************/
/* Command Function													*/
/************************************************************************/
void CommandFunction_DgnElementSetToolTest(WCharCP);