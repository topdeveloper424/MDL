#include "ToolTest.h"

void DgnTestTool::InstallNewInstance(int toolId)
{
	DgnTestTool* tool = new DgnTestTool(toolId);
	tool->InstallTool();
}

void CommandFunction_DgnElementSetToolTest(WCharCP unparsed)
{
	DgnTestTool::InstallNewInstance(CMDNAME_DgnElementSetToolTest);
}