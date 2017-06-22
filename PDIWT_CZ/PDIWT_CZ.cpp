#include "PDIWT_CZ.h"
#include "CzType1.h"
void CreateType1DB(WCharCP unparsed) { CzType1::CreateDB(); }
void CreateType1BDun(WCharCP unparsed) { CzType1::CreateBDun(); }
void CreateType1MK(WCharCP unparsed) { CzType1::CreateMK(); }
void CreateType1SSLD(WCharCP unparsed) {}
void CreateType1XNG(WCharCP unparsed) {}

void CreateType2DB(WCharCP unparsed) {}
void CreateType2BDun(WCharCP unparsed) {}
void CreateType2MK(WCharCP unparsed) {}
void CreateType2SSLD(WCharCP unparsed) {}
void CreateType2XNG(WCharCP unparsed) {}


extern "C" void MdlMain(int argc, WCharCP argv[])
{
	RscFileHandle rfHandle;
	mdlResource_openFile(&rfHandle, NULL, RSC_READONLY);
	mdlSystem_registerCommandNumbers(s_CommandNumber);
	mdlParse_loadCommandTable(NULL);
}