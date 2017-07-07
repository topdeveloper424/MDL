#include <Mstn\MdlApi\dlogbox.r.h>
#include <Mstn\MdlApi\dlogids.r.h>


#include "BasicDialog.h"
#include "chinese\BasicDialogtxt.h"
#include "BasicDialogcmd.h"

/*----------------------------------------------------------------------+
|                                                                       |
|   Dialog Box Resource Specification                                   |
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   DialogBoxRsc Structure                                              |
|                                                                       |
|   The DialogBoxRsc data structure (defined in "dlogbox.h") defines    |
|   a dialog box in a resource file. Its header section contains        |
|   information for the entire dialog (like its width and height),      |
|   and then a list of items.                                           |
|                                                                       |
|   typedef struct dialogboxrsc                                         |
|       {                                                               |
|       ULong           attributes;     # dialog attributes             |
|       int             width;          # dialog coords                 |
|       int             height;         # dialog coords                 |
|       ULong           helpInfo;       # help for entire dialog        |
|       char            *helpSource;    # help task ID                  |
|       long            dialogHookId;   # dialog hook ID                |
|       long            parentDialogId; # to inform when destroyed      |
|   #if defined (resource)                                              |
|       char            label[];        # dialog label (title)          |
|       DialogItemRsc   itemList[];     # array of dialog items         |
|   #else                                                               |
|       long            labelLength;    # length of label (title)       |
|       char            label[1];       # dialog label (title)          |
|   #endif                                                              |
|       } DialogBoxRsc;                                                 |
|                                                                       |
|                                                                       |
|   Each item in a dialog box needs to have an DialogItemRsc entry in   |
|   the DialogBoxRsc field, itemList. The order that items are listed   |
|   is important in two respects: the items are drawn in the order      |
|   specified, and the input focus moves from item to item based on     |
|   this order. DialogItemRsc data structure is declared as follows:    |
|                                                                       |
|   typedef struct dialogitemrsc                                        |
|       {                                                               |
|       Sextent extent;             # item area, origin                 |
|                                      (in dialog coords),              |
|                                      if width/height is zero, use     |
|                                      dimensions specified in item     |
|       long        type;           # item type                         |
|       long        id;             # item ID                           |
|       byte        attributes;     # item attributes                   |
|       long        itemArg;        # item argument                     |
|   #if defined (resource)                                              |
|       char        label[];        # item label                        |
|       char        auxInfo[];      # item auxiliary information        |
|   #else                                                               |
|       int         labelLength;    # length of item label              |
|       char        label[1];       # item label                        |
|   #endif                                                              |
|       } DialogItemRsc;                                                |
|                                                                       |
+----------------------------------------------------------------------*/
//#define X1  (14*XC)	//text & opntion button x postion
//#define X2	(7*XC)	//push button x postion
//#define XW	(9*XC)	//text & option button width
//#define BTN_WIDTH	(12*XC)	//push button width
//
//DialogBoxRsc DIALOGID_Basic =
//{
//	DIALOGATTR_DEFAULT | DIALOGATTR_SINKABLE,
//	25 * XC, 7 * YC,
//	NOHELP,MHELP,HOOKDIALOGID_Basic,NOPARENTID,
//	TXT_BasicDialogBox,
//	{
//		{{X1,GENY(1),XW,0},Text,TEXTID_Basic,ON,0,"",""},
//		{{X1,GENY(2),XW,0},OptionButton,OPTIONBUTTONID_Basic,ON,0,"",""},
//		{{X2,GENY(4),BTN_WIDTH,0},PushButton,PUSHBUTTONID_OModal,ON,0,"",""},
//	}
//};
//
//
//#undef BTN_WIDTH
//#undef XW
//#undef X2
//#undef X1

DialogBoxRsc DIALOGID_Basic =
{
	DIALOGATTR_DEFAULT | DIALOGATTRX_AUTOUPDATETEXTITEMS,
	25 * XC, 7 * YC,
	NOHELP,MHELP,HOOKDIALOGID_Basic,NOPARENTID,
	TXT_BasicDialogBox,
	{
		BEGIN_VSTACK_LAYOUT(VSTACKLAYOUTID_Standard,"")

		BEGIN_HSTACK_LAYOUT(0,"")
			{ AUTO_XYWH,Label, 0, ON, LABEL_LINKMIN, "", "" },
			{ AUTO_XYWH,Text,TEXTID_Basic,NO_ITEMARGS},
		END_LAYOUT

		BEGIN_HSTACK_LAYOUT(0,"")
			{ AUTO_XYWH,Label, 0, ON, LABEL_LINKMIN, "", "" },
			{ AUTO_XYWH,OptionButton,OPTIONBUTTONID_Basic,NO_ITEMARGS },
		END_LAYOUT

		BEGIN_HSTACK_LAYOUT(0,"")
			{ AUTO_XYWH,Label,0,ON,LABEL_LINKNEXT,"",""},
			{ AUTO_XYWH,OptionButton,OPTIONBUTTONID_ElementFill,NO_ITEMARGS},
		END_LAYOUT

			{ {0,0,8*XC,0},PushButton,PUSHBUTTONID_OModal,NO_ITEMARGS },
		END_LAYOUT
	}
};


#define X1 (1*XC)
#define X2 (3*XC)
#define X3 (14*XC)
DialogBoxRsc DIALOGID_BasicModal =
{
	DIALOGATTR_DEFAULT | DIALOGATTR_MODAL,
	25 * XC,6 * YC,
	NOHELP,MHELP,HOOKDIALOGID_Basic,NOPARENTID,
	TXT_BasicModalDialogBox,
	{
		{ {X1,GENY(1),0,0},	ToggleButton,TOGGLEID_Basic,ON,0,"",""},
		{ {X2,GENY(3),BUTTON_STDWIDTH,0}, PushButton, PUSHBUTTONID_OK,ON,0,"",""},
		{ {X3,GENY(3),BUTTON_STDWIDTH,0},PushButton,PUSHBUTTONID_Cancel,ON,0,"","" },
	}
};
#undef X3
#undef X2
#undef X1

/*----------------------------------------------------------------------+
|                                                                       |
|   Text Item Resource Definitions                                      |
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   The text item is defined in a resource file with the following      |
|   structure:                                                          |
|                                                                       |
|   typedef struct ditem_textrsc                                        |
|      {                                                                |
|      ULong   commandNumber;                                           |
|      ULong   commandSource;                                           |
|      long    synonymsId;                                              |
|      ULong   helpInfo;                                                |
|      ULong   helpSource;                                              |
|      long    itemHookId;                                              |
|      long    itemHookArg;                                             |
|      byte    maxSize;              /* max # of chars in field         |
|      char    formatToDisplay[16];  /* conv to display<-internal       |
|      char    formatToInternal[16]; /* conv to internal->display       |
|      char    minimum[16];          /* minimum value                   |
|      char    maximum[16];          /* maximum value                   |
|      ULong   mask;                 /* only used with int types        |
|      UShort  attributes;           /* other attributes                |
|   #if defined (resource)                                              |
|      char    label[];                                                 |
|      char    accessStr[];                                             |
|   #else                                                               |
|     long    labelLength;                                              |
|      char    label[1];                                                |
|   #endif                                                              |
|      } DItem_TextRsc;                                                 |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_TextRsc TEXTID_Basic =
{
	NOCMD,LCMD,SYNONYMID_Basic,NOHELP,MHELP,NOHOOK,NOARG,
	4,"%ld","%ld","1","3",NOMARK,NOCONCAT,
	TXT_Param1,
	"g_basicGlobals.param1"	
};

DItem_OptionButtonRsc OPTIONBUTTONID_Basic =
{
	SYNONYMID_Basic, NOHELP,MHELP,NOHOOK,NOARG,
	TXT_Param1,
	"g_basicGlobals.param1",
	{
		{ NOTYPE,NOICON,NOCMD,LCMD,1,NOMASK,ON,TXT_Value1 },
		{ NOTYPE,NOICON,NOCMD,LCMD,2,NOMASK,ON,TXT_Value2 },
		{ NOTYPE,NOICON,NOCMD,LCMD,3,NOMASK,ON,TXT_Value3 },
	}
};
/*----------------------------------------------------------------------+
|                                                                       |
|   Push Button Item Resource Definitions                               |
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   The push button item is defined in a resource file with the         |
|   following structure:                                                |
|                                                                       |
|   typedef struct ditem_pushbuttonrsc                                  |
|      {                                                                |
|      char    isDefault;      # TRUE if this is default button         |
|      ULong   helpInfo;                                                |
|      ULong   helpSource;                                              |
|      long    itemHookId;                                              |
|      long    itemHookArg;                                             |
|      ULong   commandNumber;                                           |
|      ULong   commandSource;                                           |
|   #if defined (resource)                                              |
|      char    unparsed[];                                              |
|      char    label[];                                                 |
|   #else                                                               |
|      long    unparsedLength;                                          |
|                                                                       |
|      char    unparsed[1];                                             |
|   #endif                                                              |
|   } DItem_PushButtonRsc;                                              |
|                                                                       |
|   Multi-lined push button items can be displayed by placing newline   |
|   characters ("\n") in the push button item label.                    |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_PushButtonRsc PUSHBUTTONID_OModal =
{
	NOT_DEFAULT_BUTTON,NOHELP,MHELP,NOHOOK,NOARG,
	CMD_OPENMODEL,LCMD,"",
	TXT_OpenMondal
};

/*
	Toggle button Item
*/

DItem_ToggleButtonRsc TOGGLEID_Basic =
{
	NOCMD,LCMD,NOSYNONYM,NOHELP,MHELP,
	HOOKITEMID_ToggleButton_Basic, NOARG,NOMASK, NOINVERT,
	TXT_IncrementParam1,
	"g_basicGlobals.param2"
};

DItem_SynonymsRsc SYNONYMID_Basic =
{
	{
		{Text,			TEXTID_Basic},
		{OptionButton,	OPTIONBUTTONID_Basic},
	}
};