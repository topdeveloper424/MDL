#include "ReferencesExample.h"

MdlCommandNumber s_commandNumbers[] =
{
	{ CmdHandler(referenceExample_CreateModel), CMD_REFERENCESEXAMPLE_CREATEMODELS },
	{ CmdHandler(referenceExample_CreateReference), CMD_REFERENCESEXAMPLE_CREATEREFERENCES },
	{ CmdHandler(referenceExample_ScaleReference), CMD_REFERENCESEXAMPLE_SCALEREFERENCES },
	{ CmdHandler(referenceExample_RotateReference), CMD_REFERENCESEXAMPLE_ROTATEREFERENCES },
	{ CmdHandler(referenceExample_ClipReference), CMD_REFERENCESEXAMPLE_CLIPREFERENCES },
	{ CmdHandler(referenceExample_ShowParallelReferences), CMD_REFERENCESEXAMPLE_SHOWREFERENCES_PARALLEL},
	{ CmdHandler(referenceExample_ShowNestedReferences), CMD_REFERENCESEXAMPLE_SHOWREFERENCES_NESTED },
	0
};


extern "C" void MdlMain(int argc, WCharCP argv[])
{
	RscFileHandle rfHandle;
	if (SUCCESS != mdlResource_openFile(&rfHandle, nullptr, RSC_READONLY))
	{
		mdlOutput_errorU(L"Can not open the Resource file!");
		mdlSystem_exit(-1, 1);
	}
	mdlSystem_registerCommandNumbers(s_commandNumbers);
	mdlParse_loadCommandTable(nullptr);
	
}