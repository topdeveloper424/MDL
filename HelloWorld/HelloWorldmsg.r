/*--------------------------------------------------------------------------------------+
|
|  $Source: MstnExamples/Elements/exampleSolids/exampleSolidsCmd.r $
|
|  $Copyright: (c) 2015 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
#include <Mstn\MdlApi\rscdefs.r.h>
#include <Mstn\MdlApi\cmdclass.r.h>
#include "HelloWorldids.h"

/*----------------------------------------------------------------------+
	Command Names
+----------------------------------------------------------------------*/
MessageList STRINGLISTID_Commands =
{
	{
		{CMDNAME_PlaceBsSurfaceTool, "创建线"},
		{CMDNAME_FloodTool,	"创建面域"},
		{CMDNAME_MoveTool,"移动物体"},
	}
};

MessageList STRINGLISTID_Prompts =
{
	{
		{PROMPT_FirstPoint,			"输入第一个点"},
		{PROMPT_NextPoint,			"输入下一个点"},
		{PROMPT_NextPointOrReset,	"输入下一个点或按右键完成"},
	}
};