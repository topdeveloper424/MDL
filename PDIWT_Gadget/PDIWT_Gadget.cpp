#include "PDIWT_Gadget.h"
#define Private
/************************************************************************/
/* Global variables														*/
/************************************************************************/
Private OffSetWidth g_offsetwidth = { 10 };
Private DgnLevels g_dgnlevels = { "Default" };
Private TableYTolerance g_tableytolerance = { 1e-5 };

DialogHookInfo uHooks[] =
{
	{HOOKITEMID_DgnLevels,PFDialogHook(dgnLevel_optionBtnHook)},
};

static MdlCommandNumber s_commandNumber[] =
{
	{(CmdHandler)ParallelArea,CMD_PDIWT_GADGET_PARALLELAREA},
	{(CmdHandler)ShowLevelBox,CMD_PDIWT_GADGET_LEVELBOXUI },
	{(CmdHandler)CreateTable, CMD_PDIWT_GADGET_CREATETABLE },
	nullptr
};

extern	"C" void MdlMain(int argc, WCharCP argv[])
{
	RscFileHandle rfHandle;
	if (mdlResource_openFile(&rfHandle,nullptr,RSC_READONLY))
	{
		mdlOutput_errorU(L"无法打开资源文件");
		mdlSystem_exit(-1, 1);
	}
	mdlSystem_registerCommandNumbers(s_commandNumber);
	mdlParse_loadCommandTable(nullptr);
	mdlState_registerStringIds(STRINGLISTID_Commands, STRINGLISTID_Prompts);
	//publish variable
	SymbolSet* setp = mdlCExpression_initializeSet(VISIBILITY_DIALOG_BOX, 0, FALSE);
	mdlDialog_publishComplexVariable(setp, "OffSetWidth", "g_offsetwidth", &g_offsetwidth);
	mdlDialog_publishComplexVariable(setp, "DgnLevels", "g_dgnlevels", &g_dgnlevels);
	mdlDialog_publishComplexVariable(setp, "TableYTolerance", "g_tableytolerance", &g_tableytolerance);
	//publish hookfunction
	mdlDialog_hookPublish(sizeof(uHooks) / sizeof(DialogHookInfo), uHooks);
}