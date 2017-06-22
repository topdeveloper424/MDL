#include "CzType1.h"

CzType1::CzType1()
{
	bduninfo = { 300,200,100,400,500 };
}


CzType1::~CzType1()
{
}

StatusInt CzType1::CreateBDun()
{
	bvector<Dpoint3d> points =
	{
		{0,0}, //#1
		{bduninfo.para1,0}, //#2
		{bduninfo.para1,bduninfo.para2},  //#3
		{bduninfo.para1 -bduninfo.para3,bduninfo.para2}, //#4
		{bduninfo.para1-bduninfo.para3,bduninfo.para2+bduninfo.para4},  //#5
		{bduninfo.para1,bduninfo.para2+bduninfo.para4},  //#6
		{bduninfo.para1,bduninfo.para2+bduninfo.para4+bduninfo.para5}, //#7
		{0,bduninfo.para2 + bduninfo.para4 + bduninfo.para5 } //#8
	};

	EditElementHandle eeh;
	ShapeHandler::CreateShapeElement(eeh, NULL, &points[0], points.size(), ACTIVEMODEL->Is3d(), *ACTIVEMODEL);
	CurveVectorPtr curves = ShapeHandler::ElementToCurveVector(eeh);
	DgnExtrusionDetail dgnExDetail(curves, DVec3d::From(DPoint3d{0,0,100}), true);
	auto dd = ISolidPrimitive::CreateDgnExtrusion(dgnExDetail);
	DraftingElementSchema::ToElement(eeh, *dd, NULL, *ACTIVEMODEL);
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
