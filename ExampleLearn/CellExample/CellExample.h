#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>
#include <DgnPlatform\DgnPlatformApi.h>
#include <Mstn\PSolid\mssolid.h>
#include <Mstn\PSolid\mssolid.fdf>
#include <PSolid\PSolidCoreAPI.h>

#include <DgnView\DgnElementSetTool.h>
#include <DgnView\DgnTool.h>
#include <DgnView\AccuDraw.h>
#include <DgnView\AccuSnap.h>

#include "CellExamplecmd.h"
#include "CellExampleids.h"

#include <cstdarg>
#include <Bentley/BeFileListIterator.h>
USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT
USING_NAMESPACE_BENTLEY_ECOBJECT

/************************************************************************/
/* Normal Function														*/
/************************************************************************/
void PrintFloats(int n, ...);

void GetCellLibraryNames();

void DisplayLevelsColorRGB(DgnFileR file);

void GetFileNames(WString filePathList);

void WriteTexts();

void DgnECManagerTest();

void SolidUtilTest();

void ElementTemplateTest();
/************************************************************************/
/* Command Function														*/
/************************************************************************/
void openDialogFunction(WCharCP unparsed)
{

	//PrintFloats(3, 1.22, 1.333, 4.555);
	//DisplayLevelsColorRGB(*ISessionMgr::GetActiveDgnFile());
	//DgnECManagerTest();
	ElementTemplateTest();
}
void setListView(WCharCP nuparsed)
{
	SolidUtilTest();
}

