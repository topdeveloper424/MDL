#include "CzType1.h"

CzType1::CzType1()
{
	bduninfo = { 100,200,300,400,500 };
}


CzType1::~CzType1()
{
}

StatusInt CzType1::CreateBDun()
{
	bvector<Dpoint3d> points =
	{
		{0,0}, //#1
		{0,bduninfo.para1}, //#2
		{bduninfo.para1,bduninfo.para2},  //#3
		{bduninfo.para1 -bduninfo.para3,bduninfo.para2}, //#4
		{bduninfo.para1-bduninfo.para3,bduninfo.para2+bduninfo.para4},  //#5
		{bduninfo.para1,bduninfo.para2+bduninfo.para4},  //#6
		{bduninfo.para1,bduninfo.para2+bduninfo.para4+bduninfo.para5}, //#7
		{0,bduninfo.para2 + bduninfo.para4 + bduninfo.para5 } //#8
	};

	EditElementHandle eeh;
	ShapeHandler::CreateShapeElement(eeh, NULL, points, points.size(), ACTIVEMODEL->Is3d(), ACTIVEMODEL);
	eeh.AddToModel();

	return SUCCESS;
}

StatusInt CzType1::CreateDB()
{
	mdlDialog_openInfoBox(L"Great");
	return SUCCESS;

}

StatusInt CzType1::CreateMK()
{
	mdlDialog_openMessageBox(DIALOGID_MsgBoxYesNo, L"test", MessageBoxIconType::BentleyB);
	return SUCCESS;

}

StatusInt CzType1::CreateSSLD()
{
	return SUCCESS;
}

StatusInt CzType1::CreateXNG()
{
	return StatusInt();
}
