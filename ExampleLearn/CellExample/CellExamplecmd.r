#pragma suppressREQCmds

#include <Mstn\MdlApi\cmdclass.r.h>
#include <Mstn\MdlApi\rscdefs.r.h>
#include "CellExampleids.h"

/*----------------------------------------------------------------------+
Main command table porotype
{< number >, < subtableidentifier > (or zero if no subtable), < commandclass >, < options >, "<commandword >"},
< commandclass >
            Class  Value Class  Value
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

< options> DEF | REQ | TRY | CMDSTR(n) | HID
+ ----------------------------------------------------------------------*/

#define CT_NONE		0
#define CT_MAIN		1
#define CT_PDIWT	2
#define CT_ACTION	3

CommandTable CT_MAIN =
{
	{ 1,	CT_PDIWT,	PLACEMENT,	REQ,	"PDIWT"},
};

CommandTable CT_PDIWT =
{
	{ 1,	CT_ACTION,	INHERIT,	NONE,	"CELLEXAMPLE"},
};
CommandTable CT_ACTION =
{
	{ 1,	CT_NONE,	INHERIT,	NONE,	"OPEN"},
	{ 2,	CT_NONE,	INHERIT,	NONE,	"LISTTOGGLE"},
};
