#include <Mstn\MdlApi\rscdefs.r.h>
#include <Mstn\MdlApi\cmdclass.r.h>

#define DLLAPP_BASICDIALOG	1
DllMdlApp DLLAPP_BASICDIALOG =
{
	L"BASICDIALOG",L"basicdialog"
}

/**
	Local Define
*/
#define CT_NONE 0
#define CT_BASICDIALOG 1

CommandTable CT_BASICDIALOG =
{
	{1, CT_NONE, INPUT, NONE, "OPENMODEL"},
};
