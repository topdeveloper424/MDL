/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/Elements/exampleSolids/exampleSolidsCmd.r $
|
|  $Copyright: (c) 2015 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
#include <Mstn\MdlApi\rscdefs.r.h>
#include <Mstn\MdlApi\cmdclass.r.h>

#include "../ElementsExampleids.h"

MessageList STRINGLISTID_Commands =
{
	{
		{CMDNAME_ElementsExampleCreateMlineNone,	"创建没有属性的多线"},
		{CMDNAME_ElementsExampleCreateMlineActive,	"创建具有当前属性的多线"},
		{CMDNAME_ElementsExampleCreateMlineCustom,	"创建具有自定义属性的多线"},
		{CMDNAME_ElementsExampleCreateShapeNone,	"创建没有属性的形状"},
		{CMDNAME_ElementsExampleCreateShapeActive,	"创建具有当前属性的形状"},
		{CMDNAME_ElementsExampleCreateShapeCustom,	"创建具有自定义属性的形状"},
		{CMDNAME_ElementsExampleCopy,				"拷贝工具"},
		{CMDNAME_ElementsExampleQueryElementDisplay, "查询元素显示" },
		{CMDNAME_ElementsExampleQueryElementGeometry,"查询元素几何尺寸"},
		{CMDNAME_ElementsExampleQueryElementFill,	"查询元素填充" },
	}
};

MessageList STRINGLISTID_Prompts =
{
	{
		{PROMPT_FristPoint,		"输入第一个点"},
		{PROMPT_NextPoint,		"输入下一个点"},
		{PROMPT_OppsiteCorner,	"输入对角点"},
		{PROMPT_NextPointOrReset, "输入下一个点或重置"},
		{PROMPT_SelectElement,	"选择要复制的元素"},
		{PROMPT_CopyPoint,		"输入一个点来复制元素"},
	}
};

