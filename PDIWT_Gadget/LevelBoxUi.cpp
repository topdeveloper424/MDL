#include "PDIWT_Gadget.h"
extern DgnLevels g_dgnlevels;

void ShowLevelBox(WCharCP unparsed)
{
	MSDialog::OpenMessageBox(DIALOGID_MsgBoxYesNo, L"Test", MessageBoxIconType::Information);
}
void dgnLevel_optionBtnHook(DialogItemMessageP dimP)
{

}