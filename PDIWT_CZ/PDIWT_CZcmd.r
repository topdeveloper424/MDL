/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/Elements/exampleSolids/exampleSolidsCmd.r $
|
|  $Copyright: (c) 2015 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
#pragma suppressREQCmds

#include <Mstn\MdlApi\rscdefs.r.h>
#include <Mstn\MdlApi\cmdclass.r.h>

#define CT_NONE         0
#define CT_MAIN         1
#define CT_CREATE       2
#define CT_TYPE1		3
#define CT_TYPE2		4

/*----------------------------------------------------------------------+
 Main command table
+----------------------------------------------------------------------*/
CommandTable CT_MAIN =
{ 
    { 1, CT_CREATE,     MANIPULATION,   REQ,           "PDIWTMDLCZ" }
};

CommandTable CT_CREATE =
{
    { 1, CT_TYPE1,		INHERIT,        REQ,            "TYPE1" },
    { 2, CT_TYPE2,		INHERIT,        REQ,            "TYPE2" }
};

CommandTable CT_TYPE1 =
{
    { 1, CT_NONE,       INHERIT,        DEF,            "DB"},
    { 2, CT_NONE,       INHERIT,        NONE,           "BDUN"},
    { 3, CT_NONE,       INHERIT,        NONE,           "MK"},
    { 4, CT_NONE,       INHERIT,        NONE,           "SSLD"},
	{ 5, CT_NONE,		INHERIT,		NONE,			"XNG"}
};
CommandTable CT_TYPE2 =
{
    { 1, CT_NONE,       INHERIT,        DEF,            "DB"},
    { 2, CT_NONE,       INHERIT,        NONE,           "BDUN"},
    { 3, CT_NONE,       INHERIT,        NONE,           "MK"},
    { 4, CT_NONE,       INHERIT,        NONE,           "SSLD"},
	{ 5, CT_NONE,		INHERIT,		NONE,			"XNG"}
};