#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>
#include <DgnPlatform\DgnPlatformApi.h>
#include <Mstn\PSolid\mssolid.h>
#include <Mstn\PSolid\mssolid.fdf>
#include <Mstn/cmdlist.r.h>

#include "BasicDialog.h"
#include "BasicDialogcmd.h"



#ifndef Private
#define Priavte
#endif


Priavte void basic_errorPrint(int errorNumber)
{
	WString errorMsg;
	if (SUCCESS != mdlResource_loadWString(errorMsg, NULL, MESSAGELISTID_BasicErrors, errorNumber))
		return;
	mdlDialog_dmsgsPrint(errorMsg.c_str());
}

Priavte BasicGlodbals g_basicGlobals = { 1,0 };

Priavte void basic_dialogHook(DialogMessage *dmP)
{
	if (dmP->dialogId != DIALOGID_Basic)
		return;

	dmP->msgUnderstood = TRUE;

	switch (dmP->messageType)
	{
	case DIALOG_MESSAGE_DESTROY:
	{
		mdlDialog_cmdNumberQueue(FALSE, CMD_MDL_UNLOAD, mdlSystem_getCurrTaskID(), INPUTQ_EOQ);
		break;
	}
	default:
		dmP->msgUnderstood = FALSE;
		break;
	}
}

Priavte void basic_toggleButtonHook(DialogItemMessage *dimP)
{
	dimP->msgUnderstood = TRUE;

	switch (dimP->messageType)
	{
	case DITEM_MESSAGE_CREATE:
	{
		g_basicGlobals.param2 = 0;
		break;
	}
	default:
		dimP->msgUnderstood = FALSE;
		break;
	}
}

Public	void basic_openModel(WCharP unparsedP)
{
	int lastAction;
	if (SUCCESS !=mdlDialog_openModal(&lastAction,NULL,DIALOGID_BasicModal))
	{
		basic_errorPrint(ERRID_ModelDialog);
		return;
	}
	if (lastAction == ACTIONBUTTON_OK && g_basicGlobals.param2)
	{
		g_basicGlobals.param1++;
		if (g_basicGlobals.param1 > 3)
			g_basicGlobals.param1 = 1;
		mdlDialog_synonymsSynch(NULL, SYNONYMID_Basic, NULL);
	}
}

Priavte DialogHookInfo	uHooks[] =
{
	{HOOKITEMID_ToggleButton_Basic,(PFDialogHook)basic_toggleButtonHook},
	{HOOKDIALOGID_Basic,(PFDialogHook)basic_dialogHook},
};

extern "C" void MdlMain(int argc, WCharCP argv[])
{
	SymbolSet *setP;
	RscFileHandle rscFileH;
	MSDialog *dbP;

	mdlResource_openFile(&rscFileH, NULL, 0);
	MdlCommandNumber s_commnadNumbers[] =
	{
		{(CmdHandler)basic_openModel,CMD_OPENMODEL},
		0
	};
	mdlSystem_registerCommandNumbers(s_commnadNumbers);

	if (mdlParse_loadCommandTable(nullptr) == nullptr)
		basic_errorPrint(ERRID_CoomandTabel);

	setP = mdlCExpression_initializeSet(VISIBILITY_DIALOG_BOX, 0, FALSE);
	mdlDialog_publishComplexVariable(setP,"basicglobals","g_basicGlobals", &g_basicGlobals);

	mdlDialog_hookPublish(sizeof(uHooks) / sizeof(uHooks[0]), uHooks);

	if ((dbP = mdlDialog_open(NULL, DIALOGID_Basic)) == nullptr)
		basic_errorPrint(ERRID_BasicDialog);
		
}