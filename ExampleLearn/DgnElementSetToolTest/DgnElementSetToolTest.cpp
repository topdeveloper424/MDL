#include "DgnElementSetToolTest.h"

static MdlCommandNumber s_commandNumber[] =
{
	{ CmdHandler(CommandFunction_DgnElementSetToolTest),CMD_PDIWT_DGNELEMENTSETTOOLTEST},
	nullptr
};

extern "C" void MdlMain(int argc, WCharCP argv[])
{
	RscFileHandle rfHandle;
	if (mdlResource_openFile(&rfHandle, nullptr, RSC_READONLY))
	{
		mdlOutput_errorU(L"无法打开资源文件");
		mdlSystem_exit(-1, 1);
	}
	mdlSystem_registerCommandNumbers(s_commandNumber);
	mdlParse_loadCommandTable(nullptr);
	mdlState_registerStringIds(STRINGLISTID_Commands, STRINGLISTID_Prompts);
}