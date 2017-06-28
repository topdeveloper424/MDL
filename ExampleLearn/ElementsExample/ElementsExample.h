#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>
#include <DgnPlatform\DgnPlatformApi.h>
#include <Mstn\PSolid\mssolid.h>
#include <Mstn\PSolid\mssolid.fdf>

#include <DgnView\AccuDraw.h>
#include <DgnView\DgnElementSetTool.h>
#include <Mstn\ElementPropertyUtils.h>

#include "ElementsExampleids.h"
#include "ElementsExamplecmd.h"

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

//Create
void elementsExampleCreateMlineNone(WCharCP);
void elementsExampleCreateMlineActive(WCharCP);
void elementsExampleCreateMlineCustom(WCharCP);

void elementsExampleCreateShapeNone(WCharCP);
void elementsExampleCreateShapeActive(WCharCP);
void elementsExampleCreateShapeCustom(WCharCP);

//COPY
void elementsExampleCopyElement(WCharCP);

//Query
void elementsExampleQueryElementDisplay(WCharCP);
void elementsExampleQueryElementGeometry(WCharCP);
void elementsExampleQueryElementFill(WCharCP);