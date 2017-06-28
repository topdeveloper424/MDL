/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/Elements/exampleSolids/exampleSolidsCmd.r $
|
|  $Copyright: (c) 2015 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
#include <Mstn\MdlApi\rscdefs.r.h>
#include <Mstn\MdlApi\cmdclass.r.h>

#include "ElementsExampleids.h"

#define CT_NONE				0
#define CT_MAIN				1
#define CT_ELEMENTS			2
#define CT_CREATE			3
#define CT_OPERATIONS		4
#define CT_CREATEOPTIONS	5
#define CT_QUERY			6
#define CT_EDIT				7

#pragma suppressREQCmds

/*----------------------------------------------------------------------+
 Main command table
+----------------------------------------------------------------------*/
CommandTable CT_MAIN =
{ 
    { 1, CT_ELEMENTS,		MANIPULATION,   REQ,	"ELEMENTSEXAMPLE" },
};

CommandTable CT_ELEMENTS =
{
    { 1, CT_CREATE,			INHERIT,        REQ,	"SHAPE" },
    { 2, CT_CREATE,			INHERIT,        REQ,	"MULTILINE" },
    { 3, CT_OPERATIONS,		INHERIT,        REQ,	"ELEMENT" },
};

CommandTable CT_CREATE =
{
    { 1, CT_CREATEOPTIONS,	INHERIT,        REQ,	"CREATE" },
};

CommandTable CT_CREATEOPTIONS =
{
	{ 1, CT_NONE,			INHERIT,		DEF,	"NONE"},
	{ 2, CT_NONE,			INHERIT,		DEF,	"ACTIVE"},
	{ 3, CT_NONE,			INHERIT,		DEF,	"CUSTOM"},			
};

CommandTable CT_OPERATIONS =
{
	{ 1, CT_NONE,			INHERIT,		DEF,	"COPY"},
	{ 2, CT_QUERY,			INHERIT,		REQ,	"QUERY"},
};

CommandTable CT_QUERY = 
{
	{ 1, CT_NONE,			INHERIT,		DEF,	"DISPLAY"},
	{ 2, CT_NONE,			INHERIT,		NONE,	"GEOMETRY"},
	{ 3, CT_NONE,			INHERIT,		NONE,	"FILL"},
};

/*-----------------------------------------------------------------------
 Setup for native code only MDL app
-----------------------------------------------------------------------*/
#define DLLAPP_PRIMARY 1

DllMdlApp DLLAPP_PRIMARY =
{
    L"ELEMENTSEXAMPLE", L"elementsexample" // taskid, dllName
}