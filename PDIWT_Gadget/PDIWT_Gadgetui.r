#include <Mstn\MdlApi\dlogbox.r.h>
#include <Mstn\MdlApi\dlogids.r.h>

#include "PDIWT_Gadgetids.h"
#include "PDIWT_Gadgetcmd.h"
#include "chinese\PDIWT_Gadgettxt.h"


CmdItemListRsc	ITEMLIST_PARALLELARE =
{{
	BEGIN_VSTACK_LAYOUT(VSTACKLAYOUTID_Standard,"")
		BEGIN_HSTACK_LAYOUT(HSTACKLAYOUTID_Standard,"")
			{AUTO_XYWH,Label,0,ON,LABEL_LINKNEXT,"",""},
			{AUTO_XYWH,Text,TEXTID_OffsetWidth,NO_ITEMARGS},
		END_LAYOUT
	END_LAYOUT
}};

CmdItemListRsc	ITEMLIST_CREATETABLE =
{{
	BEGIN_VSTACK_LAYOUT(VSTACKLAYOUTID_Standard,"")
		BEGIN_HSTACK_LAYOUT(HSTACKLAYOUTID_Standard,"")
			{AUTO_XYWH,Label,0,ON,LABEL_LINKNEXT,"",""},
			{AUTO_XYWH,Text,TEXTID_TabelYTolerance,NO_ITEMARGS},
		END_LAYOUT
	END_LAYOUT
}};
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

DItem_TextRsc TEXTID_OffsetWidth =
{
	NOCMD,LCMD,NOSYNONYM,NOHELP,MHELP,NOHOOK,NOARG,
	15,"%.2lf","%lf","0.0","",NOMARK,NOCONCAT,
	TXT_OffsetWitdh,
	"g_offsetwidth.width"
};

DItem_TextRsc TEXTID_TabelYTolerance =
{
	NOCMD,LCMD,NOSYNONYM,NOHELP,MHELP,NOHOOK,NOARG,
	12,"%g","%g","1e-3","",NOMARK,NOCONCAT,
	TXT_TabelYTolerance,
	"g_tableytolerance.tolerance"
};
//DItem_TextRsc TEXTID_Basic =
//{
//	NOCMD,LCMD,SYNONYMID_Basic,NOHELP,MHELP,NOHOOK,NOARG,
//	4,"%ld","%ld","1","3",NOMARK,NOCONCAT,
//	TXT_Param1,
//	"g_basicGlobals.param1"
//};
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
#define XSIZE 20*XC
#define YSIZE 5*YC
DialogBoxRsc DIALOGID_Information =
{
	DIALOGATTR_DEFAULT,XSIZE,YSIZE,NOHELP,MHELP,
	NOHOOK,NOPARENTID,"Rassre",
	{
	BEGIN_HSTACK_LAYOUT(HSTACKLAYOUTID_DialogButtons,"")
		{ AUTO_XYWH,PushButton,PUSHBUTTONID_OK,NO_ITEMARGS },
		{ AUTO_XYWH,PushButton,PUSHBUTTONID_Cancel,NO_ITEMARGS },
	END_LAYOUT
	}
};
#undef YSIZE
#undef XSIZE
