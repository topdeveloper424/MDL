#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>

#include "PDIWT_CZcmd.h"

void CreateType1DB(WCharCP);
void CreateType1BDun(WCharCP);
void CreateType1MK(WCharCP);
void CreateType1SSLD(WCharCP);
void CreateType1XNG(WCharCP);

void CreateType2DB(WCharCP);
void CreateType2BDun(WCharCP);
void CreateType2MK(WCharCP);
void CreateType2SSLD(WCharCP);
void CreateType2XNG(WCharCP);


static MdlCommandNumber s_CommandNumber[] =
{
	{ (CmdHandler)CreateType1DB, CMD_PDIWTMDLCZ_TYPE1_DB },
	{ (CmdHandler)CreateType1BDun, CMD_PDIWTMDLCZ_TYPE1_BDUN },
	{ (CmdHandler)CreateType1MK, CMD_PDIWTMDLCZ_TYPE1_MK },
	{ (CmdHandler)CreateType1SSLD, CMD_PDIWTMDLCZ_TYPE1_SSLD },
	{ (CmdHandler)CreateType1XNG, CMD_PDIWTMDLCZ_TYPE1_XNG },
	{ (CmdHandler)CreateType2DB, CMD_PDIWTMDLCZ_TYPE2_DB },
	{ (CmdHandler)CreateType2BDun, CMD_PDIWTMDLCZ_TYPE2_BDUN },
	{ (CmdHandler)CreateType2MK, CMD_PDIWTMDLCZ_TYPE2_MK },
	{ (CmdHandler)CreateType2SSLD, CMD_PDIWTMDLCZ_TYPE2_SSLD },
	{ (CmdHandler)CreateType2XNG, CMD_PDIWTMDLCZ_TYPE2_XNG },
	0
};