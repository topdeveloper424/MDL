#pragma once
#include    <Mstn\MicroStation.r.h>
/************************************************************************/
/* MDL Application ID													*/
/************************************************************************/
#define MDLAPP_PDIWT_ZJCZL_C	1

/************************************************************************/
/* Stringlist ID														*/
/************************************************************************/
#define STRINGLISTID_Commands				0
#define STRINGLISTID_Prompts				1
#define STRINGLISTID_ERROR					2
#define STRINGLISTID_PileType				3
#define STRINGLISTID_PileCrossSectionType	4
/************************************************************************/
/* Command Table														*/
/************************************************************************/
#define CMDNAME_DrawPileAixsLine	1
/************************************************************************/
/* Prompt ID															*/
/************************************************************************/
#define PROMPT_FirstPoint		1
#define PROMPT_NextPoint		2
#define PROMPT_AceeptPoint		3
#define PROMPT_AceeptOrReset	4
/************************************************************************/
/* Error ID																*/
/************************************************************************/
#define ERR_Fatal				1
/************************************************************************/
/* DialogID                                                             */
/************************************************************************/
#define  DIALOGID_DevInfoBox	1
/************************************************************************/
/* CmdItemListRsc	enum												*/
/************************************************************************/
enum CmdItemListId
{
	ITEMLIST_DRAWAXISLINE = 1,
};
/************************************************************************/
/* GenericItem Item														*/
/************************************************************************/
#define GENERICID_CompanyLogo	1

/************************************************************************/
/* ComboxRsc ID															*/
/************************************************************************/
#define COMBOBOXID_PileType					1
#define COMBOBOXID_PileCrossSectionType		2

/************************************************************************/
/* TextRsc ID															*/
/************************************************************************/
#define TEXTID_PileCode					1
#define TEXTID_PileSideLength			2
#define TEXTID_PileWeight				3
#define TEXTID_PileUnderWaterWeight		4

/************************************************************************/
/* OptionButton ID														*/
/************************************************************************/
#define OPTIONBUTTONID_PileType					1
#define OPTIONBUTTONID_PileCrossSectionType		2

/************************************************************************/
/* GridLayout ID														*/
/************************************************************************/
#define GRIDLAYOUTID_2ColsPDIWTSetting			1
/************************************************************************/
/* Public Structures													*/
/************************************************************************/
struct PileProperty
{
	int PileType;
	int PileCrossSection;
	WChar PileCode[DGNPLATFORM_RESOURCE_MAXNAMELENGTH];
	double PileSideLength;
	double PileWeight;
	double PileUnderWaterWeight;
};

/************************************************************************/
/* HookItem	ID															*/
/************************************************************************/
#define HOOKITEMID_CompanyLogo			1
#define HOOKITEMID_PileType				2
#define HOOKITEMID_PileCrossSectionType 3