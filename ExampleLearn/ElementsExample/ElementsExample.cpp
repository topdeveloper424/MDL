#include "ElementsExample.h"

/*!
 * \file ElementsExample.cpp
 *
 * \author sudongsheng
 * \date 六月 2017
 *
 * May key-in to function commands
 */


static MdlCommandNumber s_commandNumbers[] =
{
	{ elementsExampleCreateMlineNone, CMD_ELEMENTSEXAMPLE_MULTILINE_CREATE_NONE },
	{ elementsExampleCreateMlineActive, CMD_ELEMENTSEXAMPLE_MULTILINE_CREATE_ACTIVE },
	{ elementsExampleCreateMlineCustom, CMD_ELEMENTSEXAMPLE_MULTILINE_CREATE_CUSTOM },
	{ elementsExampleCreateShapeNone, CMD_ELEMENTSEXAMPLE_SHAPE_CREATE_NONE },
	{ elementsExampleCreateShapeActive, CMD_ELEMENTSEXAMPLE_SHAPE_CREATE_ACTIVE },
	{ elementsExampleCreateShapeCustom, CMD_ELEMENTSEXAMPLE_SHAPE_CREATE_CUSTOM },
	{ elementsExampleCopyElement, CMD_ELEMENTSEXAMPLE_ELEMENT_COPY},
	{ elementsExampleQueryElementDisplay,CMD_ELEMENTSEXAMPLE_ELEMENT_QUERY_DISPLAY},
	{ elementsExampleQueryElementGeometry,CMD_ELEMENTSEXAMPLE_ELEMENT_QUERY_GEOMETRY },
	{ elementsExampleQueryElementFill,CMD_ELEMENTSEXAMPLE_ELEMENT_QUERY_FILL},
	0
};

extern	"C" void MdlMain(int argc, WCharCP argv[])
{
	RscFileHandle rfHandle;
	
	if (mdlResource_openFile(&rfHandle, nullptr, RSC_READONLY))
	{
		mdlOutput_errorU(L"无法打开资源文件");
		mdlSystem_exit(-1, 1);
	}
	mdlState_registerStringIds(STRINGLISTID_Commands, STRINGLISTID_Prompts);
	mdlSystem_registerCommandNumbers(s_commandNumbers);
	mdlParse_loadCommandTable(nullptr);
}