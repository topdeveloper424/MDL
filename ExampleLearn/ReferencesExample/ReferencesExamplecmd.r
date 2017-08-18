#include <Mstn\MdlApi\rscdefs.r.h>
#include <Mstn\MdlApi\cmdclass.r.h>
#include "ReferencesExampleids.h"

#pragma	suppressREQCmds

#define CT_NONE			0
#define CT_MAIN			1
#define	CT_REFERENCES	2
#define CT_SHOW			3
/*
*	Command Tables
*/

CommandTable CT_MAIN =
{
	{ 1,	CT_REFERENCES,	MANIPULATION,	NONE,	"REFERENCESEXAMPLE" },
};

CommandTable CT_REFERENCES =
{
	{ 1,	CT_NONE,	INHERIT,	NONE,	"CREATEMODELS",		CMDNAME_ReferencesExampleCreateModels },
	{ 2,	CT_NONE,	INHERIT,	NONE,	"CREATEREFERENCES", CMDNAME_ReferencesExampleCreateReferences },
	{ 3,	CT_NONE,	INHERIT,	NONE,	"SCALEREFERENCES",	CMDNAME_ReferencesExampleScaleReferences },
	{ 4,	CT_NONE,	INHERIT,	NONE,	"ROTATEREFERENCES", CMDNAME_ReferencesExampleRotateReferences },
	{ 5,	CT_NONE,	INHERIT,	NONE,	"CLIPREFERENCES",	CMDNAME_ReferencesExampleClipReferences },
	{ 6,	CT_SHOW,	INHERIT,	NONE,	"SHOWREFERENCES", },
};

CommandTable CT_SHOW = 
{
	{ 1,	CT_NONE,	INHERIT,	NONE,	"PARALLEL",			CMDNAME_ReferencesExampleShowReferencesParallel},
	{ 2,	CT_NONE,	INHERIT,	NONE,	"NESTED",			CMDNAME_ReferencesExmapleShowReferencesNested},
};