#pragma once
/************************************************************************/
/* Error message ID's													*/
/************************************************************************/
#define ERRID_CoomandTabel	1
#define ERRID_BasicDialog	2
#define ERRID_ModelDialog	3

/************************************************************************/
/*  Resource ID's														*/
/************************************************************************/

#define DIALOGID_Basic		1
#define DIALOGID_BasicModal	2

#define OPTIONBUTTONID_Basic	1
#define PUSHBUTTONID_OModal		1
#define TEXTID_Basic			1
#define TOGGLEID_Basic			1

#define SYNONYMID_Basic			1

#define MESSAGELISTID_BasicErrors	1

/************************************************************************/
/* Hook Fuction ID's													*/
/************************************************************************/
#define HOOKITEMID_ToggleButton_Basic	1
#define HOOKDIALOGID_Basic				2

/************************************************************************/
/* TypeDefs																*/
/************************************************************************/
typedef	struct basicglobals
{
	int param1;		// used by text & option button item
	int param2;		// used by toggle button item
} BasicGlodbals;


	