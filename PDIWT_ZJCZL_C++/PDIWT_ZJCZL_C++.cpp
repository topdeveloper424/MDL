#include "PDIWT_ZJCZL_C++.h"

Private PileProperty g_pileProperty;

static MdlCommandNumber s_commandNumber[] =
{
	{CmdHandler(StartDrawPileAxisTool),CMD_PDIWT_ZJCZL_C_DRAWAXISLINE},
	{CmdHandler(OpenInfoBox),CMD_PDIWT_ZJCZL_C_OPENINFOBOX},
	nullptr
};

DialogHookInfo uHooks[] = 
{
	{HOOKITEMID_CompanyLogo,PFDialogHook(hookItem_GenericImage)},
	{HOOKITEMID_PileType,PFDialogHook(hookItem_ComboBox_pileType)},
};

extern "C" void MdlMain(int argc, WCharCP argv[])
{
	RscFileHandle rfHandle;
	if (mdlResource_openFile(&rfHandle,nullptr,RSC_READONLY))
	{
		mdlOutput_errorU(L"无法打开资源文件");
		mdlSystem_exit(-1,1);
	}
	mdlSystem_registerCommandNumbers(s_commandNumber);
	mdlParse_loadCommandTable(nullptr);
	mdlState_registerStringIds(STRINGLISTID_Commands, STRINGLISTID_Prompts);

	mdlDialog_hookPublish(sizeof(uHooks) / sizeof(DialogHookInfo), uHooks);
	wcscpy(g_pileProperty.PileCode, L"108-A");
	g_pileProperty.PileSideLength = 1.0;
	g_pileProperty.PileWeight = 25.0;
	g_pileProperty.PileUnderWaterWeight = 15.0;
	SymbolSet* setP = mdlCExpression_initializeSet(VISIBILITY_DIALOG_BOX, 0, FALSE);
	mdlDialog_publishComplexVariable(setP, "PileProperty", "g_pileProperty", &g_pileProperty);
}

Private void OpenInfoBox(WCharCP unparsed)
{
	MSDialog::OpenModal(nullptr, NULL, DIALOGID_DevInfoBox);
	//WCharCP fileName = L"D:\\Programma\\Source\\C++\\DML\\PDIWT_Tool\\PDIWT_Tool\\PDIWT_ZJCZL_C++\\resource\\PDIWTLogo.jpg";
	////WChar device[MAXDEVICELENGTH] , directory[MAXDIRLENGTH] , name[MAXNAMELENGTH], extension[MAXEXTENSIONLENGTH];
	////mdlFile_parseName(fileName, device, directory, name, extension);
	////WPrintfString parsedname(L"device ; %s;directory : %s;name : %s;extension : %s", device, directory, name, extension);
	////mdlOutput_message(parsedname.c_str());
	////WChar iext[] = L".jpg";
	//BeFileName outfileName;
	//if (SUCCESS == mdlFile_find(&outfileName, fileName, nullptr, nullptr))
	//	mdlOutput_message(outfileName.c_str());

	//Point2d imageSize;
	//ImageColorMode colorMode;
	//int orientation;
	//if (SUCCESS == mdlImage_readFileInfo(&imageSize, &colorMode, &orientation, outfileName.c_str(), ImageFileFormat(-1)))
	//{
	//	WPrintfString outputstring(L"Image size (x,y) : (%d,%d)\ncolorMode : %d\norientation :%d", imageSize.x, imageSize.y, colorMode, orientation);
	//	mdlOutput_message(outputstring.c_str());
	//}
}

