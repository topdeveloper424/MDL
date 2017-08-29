#include <Mstn\MdlApi\rscdefs.r.h>
#include <Mstn\MdlApi\cmdclass.r.h>
#include "..\PDIWT_Gadgetids.h"

MessageList STRINGLISTID_Commands =
{{
	{CMDNAME_ParallelAreaTool,"双边偏移形成面域"},
	{CMDNAME_CreateTableTool,"提取表格"},
}};

MessageList STRINGLISTID_Prompts = 
{{
	{PROMPT_FirstPoint,"请选择要偏移的线"},
	{PROMPT_NextPoint,"按住Ctrl键进行多选"},
	{PROMPT_AceeptPoint,"点击鼠标左键确认(或按住Ctrl进行多选)"},
	{PROMPT_BoxSelectPoint,"框选要提取的表格"},
	{ PROMPT_AceeptCreatePoint,"点击鼠标左键确认" },
}};

MessageList STRINGLISTID_ERROR =
{{
	{ERR_NOTALLOWED,"不支持所选择的元素"},
}};