#include <Mstn\MdlApi\dlogbox.r.h>
#include <Mstn\MdlApi\dlogids.r.h>

#include "PDIWT_ZJCZL_C++ids.h"
#include "chinese\PDIWT_ZJCZL_C++txt.h"

#define XSIZE 30*XC
#define YSIZE 30*YC
DialogBoxRsc DIALOGID_DevInfoBox =
{
	DIALOGATTR_MODAL | DIALOGATTR_DEFAULT,XSIZE,YSIZE,NOHELP,MHELP,
	NOHOOK,NOPARENTID,"×®»ù³ÐÔØÁ¦Ä£¿é",
	{
		BEGIN_GRID_LAYOUT(GRIDLAYOUTID_2ColumnsOuter,"")
			GRID_ROW(0,"")
				{ AUTO_XYWH,Label,0,ON,ALIGN_CENTER|LABEL_FONT_BOLD,TXT_Brief,"colSpan='*'"},
			END_ROW
			GRID_ROW(0,"")
				{ AUTO_XYWH,Label,0,ON,ALIGN_CENTER,TXT_Version,"" },
				{ AUTO_XYWH,Label,0,ON,ALIGN_CENTER,TXT_DevTime,"" },
			END_ROW
			GRID_ROW(0,"")
				{ AUTO_XYWH,Label,0,ON,ALIGN_RIGHT,TXT_Commpany,""},
				{ AUTO_XYWH,Label,0,ON,ALIGN_RIGHT,TXT_DeveloperName,""},
			END_ROW
			GRID_ROW(0,"")
				{ AUTO_XYWH,Generic,GENERICID_CompanyLogo,NO_ITEMARGS},
			END_ROW
		END_LAYOUT
		//BEGIN_VSTACK_LAYOUT(VSTACKLAYOUTID_Standard,"")
		//	{AUTO_XYWH,Generic,GENERICID_CompanyLogo,NO_ITEMARGS},
		//END_LAYOUT
	}
};
#undef YSIZE
#undef XSIZE

// Generic item
DItem_GenericRsc GENERICID_CompanyLogo = 
{
	NOHELP,	MHELP,	HOOKITEMID_CompanyLogo, NOARG
};

#define MAXWIDTH 15*XC
//ItemList DrawPileAxis
CmdItemListRsc ITEMLIST_DRAWAXISLINE =
{ {
		BEGIN_GRID_LAYOUT(GRIDLAYOUTID_2ColsPDIWTSetting,"")
			GRID_ROW(0,"")
				{ AUTO_XYWH,Label,0,ON,ALIGN_RIGHT | LABEL_LINKNEXT,"",""},
				{{AUTO_XY,MAXWIDTH,0},OptionButton,OPTIONBUTTONID_PileType,NO_ITEMARGS},
			END_ROW
			GRID_ROW(0,"")
				{AUTO_XYWH,Label,0,ON,ALIGN_RIGHT | LABEL_LINKNEXT,"",""},
				{ { AUTO_XY,MAXWIDTH,0 },OptionButton,OPTIONBUTTONID_PileCrossSectionType,NO_ITEMARGS },
			END_ROW
			GRID_ROW(0,"")
				{AUTO_XYWH,Label,0,ON,ALIGN_RIGHT | LABEL_LINKNEXT,"",""},
				{ { AUTO_XY,MAXWIDTH,0 },Text,TEXTID_PileCode,NO_ITEMARGS },
			END_ROW
			GRID_ROW(0,"")
				{AUTO_XYWH,Label,0,ON,ALIGN_RIGHT | LABEL_LINKNEXT,"",""},
				{ { AUTO_XY,MAXWIDTH,0 },Text,TEXTID_PileSideLength,NO_ITEMARGS },
			END_ROW
			GRID_ROW(0,"")
				{AUTO_XYWH,Label,0,ON,ALIGN_RIGHT | LABEL_LINKNEXT,"",""},
				{ { AUTO_XY,MAXWIDTH,0 },Text,TEXTID_PileWeight,NO_ITEMARGS },
			END_ROW
			GRID_ROW(0,"")
				{AUTO_XYWH,Label,0,ON,ALIGN_RIGHT | LABEL_LINKNEXT,"",""},
				{ { AUTO_XY,MAXWIDTH,0 },Text,TEXTID_PileUnderWaterWeight,NO_ITEMARGS },
			END_ROW
		END_LAYOUT
} };
#undef MAXWIDTH

#define MAIN_MARGIN	XC_3_2
#define ROW_SPACING	YC/3
#define GRID_HSPACING	XC
#define GRID_VSPACING	ROW_SPACING
GridLayoutRsc	GRIDLAYOUTID_2ColsPDIWTSetting = 
{
	{MAIN_MARGIN,MAIN_MARGIN,MAIN_MARGIN,MAIN_MARGIN},	//margin - Left, Top, Right, Bottom
	GRID_HSPACING,GRID_VSPACING,
	{
		{0,"LabelCol"},
		{0,"InputCol"},
		{1,"StretchCol"},
	}
};
#undef GRID_VSPACING
#undef GRID_HSPACING
#undef ROW_SPACING
#undef MAIN_MARGIN
//ComboxItemRsc
//DItem_ComboBoxRsc COMBOBOXID_PileType = 
//{
//	NOCMD,LCMD,NOSYNONYM,NOHELP,MHELP,HOOKITEMID_PileType,NOARG,64,"%S","%S","","",
//	NOMARK,0,15,0,20*XC,0,COMBOATTR_READONLY,
//	TXT_PileType,"g_pileProperty.PileType",
//	{ 
//		{0,64,ALIGN_LEFT,""},
//	}
//};
//
//DItem_ComboBoxRsc COMBOBOXID_PileCrossSectionType = 
//{
//	NOCMD,LCMD,NOSYNONYM,NOHELP,MHELP,NOHOOK,NOARG,64,"%S","%S","","",
//	NOMARK,0,15,0,20*XC,0,COMBOATTR_READONLY,
//	TXT_PileCrossSectionType,"g_pileProperty.PileCrossSection",
//	{
//		{0,64,ALIGN_LEFT,""},
//	}
//};

DItem_OptionButtonRsc OPTIONBUTTONID_PileType =
{
	NOSYNONYM, NOHELP,MHELP,NOHOOK,OPTNBTNATTR_NEWSTYLE,
	TXT_PileType,"g_pileProperty.PileType",
	{
		{ NOTYPE,NOICON,NOCMD,LCMD,0,NOMASK,ON,TXT_PileType_Solid },
		{ NOTYPE,NOICON,NOCMD,LCMD,1,NOMASK,ON,TXT_PileType_SteelAndConcrete },
	}
};
DItem_OptionButtonRsc OPTIONBUTTONID_PileCrossSectionType =
{
	NOSYNONYM,NOHELP,MHELP,NOHOOK,OPTNBTNATTR_NEWSTYLE,
	TXT_PileCrossSectionType,"g_pileProperty.PileCrossSection",
	{
		{ NOTYPE,NOICON,NOCMD,LCMD,0,NOMASK,ON,TXT_PileCrossSectionType_Annular },
		{ NOTYPE,NOICON,NOCMD,LCMD,1,NOMASK,ON,TXT_PileCrossSectionType_Square },
		{ NOTYPE,NOICON,NOCMD,LCMD,2,NOMASK,ON,TXT_PileCrossSectionType_SquareWithHole },
		{ NOTYPE,NOICON,NOCMD,LCMD,3,NOMASK,ON,TXT_PileCrossSectionType_Polygon },
	}
};

DItem_TextRsc TEXTID_PileCode =
{
	NOCMD,LCMD,NOSYNONYM,NOHELP,MHELP,NOHOOK,NOARG,
	255,"%S","%S","","",NOMARK,NOCONCAT,
	TXT_PileCode,
	"g_pileProperty.PileCode"
};

DItem_TextRsc TEXTID_PileSideLength =
{
	NOCMD,LCMD,NOSYNONYM,NOHELP,MHELP,NOHOOK,NOARG,
	15,"%0.2lf","%lf","0.0","",NOMARK,NOCONCAT,
	TXT_PileSideLength,
	"g_pileProperty.PileSideLength"
};

DItem_TextRsc TEXTID_PileWeight =
{
	NOCMD,LCMD,NOSYNONYM,NOHELP,MHELP,NOHOOK,NOARG,
	15,"%0.2lf","%lf","0","",NOMARK,NOCONCAT,
	TXT_PileWeight,
	"g_pileProperty.PileWeight"
};

DItem_TextRsc TEXTID_PileUnderWaterWeight =
{
	NOCMD,LCMD,NOSYNONYM,NOHELP,MHELP,NOHOOK,NOARG,
	15,"%0.2f","%lf","0.0","",NOMARK,NOCONCAT,
	TXT_PileUnderWaterWeight,
	"g_pileProperty.PileUnderWaterWeight"
};

