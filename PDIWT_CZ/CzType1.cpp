#include "CzType1.h"



CzType1::CzType1()
{
}


CzType1::~CzType1()
{
}

void CzType1::CreateBDun()
{
	mdlDialog_openInfoBox(L"Wonderful");

}

void CzType1::CreateDB()
{
	mdlDialog_openInfoBox(L"Great");
}

void CzType1::CreateMK()
{
	mdlDialog_openMessageBox(DIALOGID_MsgBoxYesNo, L"test", MessageBoxIconType::BentleyB);
}
