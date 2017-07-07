#include <Mstn\MdlApi\dlogbox.r.h>
#include <Mstn\MdlApi\dlogids.r.h>

#include "PDIWT_Gadgetids.h"
#include "PDIWT_Gadgetcmd.h"
#include "chinese\PDIWT_Gadgettxt.h"


CmdItemListRsc	ITEMLIST_PARALLELARE =
{{
	BEGIN_HSTACK_LAYOUT(HSTACKLAYOUTID_Standard,"")
		{AUTO_XYWH,Label,0,ON,LABEL_LINKNEXT,"",""},
		{AUTO_XYWH,Text,TEXTID_OffsetWidth,NO_ITEMARGS},
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

//DItem_TextRsc TEXTID_Basic =
//{
//	NOCMD,LCMD,SYNONYMID_Basic,NOHELP,MHELP,NOHOOK,NOARG,
//	4,"%ld","%ld","1","3",NOMARK,NOCONCAT,
//	TXT_Param1,
//	"g_basicGlobals.param1"
//};