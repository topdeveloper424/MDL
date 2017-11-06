#pragma suppressREQCmds

#include <Mstn\MdlApi\rscdefs.r.h>
#include <Mstn\MdlApi\cmdclass.r.h>
#include "PDIWT_Gadgetids.h"

/*----------------------------------------------------------------------+
 Main command table
 porotype
 {<number>, <subtableidentifier> (or zero if no subtable), <commandclass>, <options>, "<commandword>"},
<commandclass>
			Class  Value  Class  Value
			PLACEMENT  1  COMPRESS  15
			VIEWING  2  REFERENCE  16
			FENCE  3  DATABASE  17
			PARAMETERS  4  DIMENSION  18
			LOCKS  5  LOCATE  19
			USERCOMMAND  6  TUTORIAL  20
			MANIPULATION  7  WORKINGSET  21
			SHOW  8  ELEMENTLIST  22
			PLOT  9  UNDO  23
			NEWFILE  10  SUBPROCESS  24
			MEASURE  11  VIEWPARAM  25
			INPUT  12  VIEWIMMEDIATE  26
			CELLLIB  13  WINDOWMAN  27
			FILEDESIGN  14  DIALOGMAN  28
			INHERIT

<options>	DEF | REQ | TRY | CMDSTR (n) | HID
+----------------------------------------------------------------------*/

#define CT_NONE		0
#define CT_MAIN		1
#define CT_PDIWT	2
#define CT_GADGET	3

CommandTable CT_MAIN =
{
	{ 1,	CT_PDIWT,	PLOT,	REQ,	"PDIWT"},
};

CommandTable CT_PDIWT = 
{
	{ 1,	CT_GADGET,	INHERIT,	REQ,	"GADGET"},
};

CommandTable CT_GADGET = 
{
	{ 1,	CT_NONE,	INHERIT,	DEF,	"PARALLELAREA",	CMDNAME_ParallelAreaTool, ITEMLIST_PARALLELARE},
	{ 2,	CT_NONE,	INHERIT,	NONE,	"LEVELBOXUI" },
	{ 3,	CT_NONE,	INHERIT,	NONE,	"CREATETABLE"},
};