#include "CzType1.h"

CzType1::CzType1()
{
	bduninfo = { 300,200,100,400,500 };
	UPM = mdlModelRef_getUorPerMaster(ACTIVEMODEL);
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
	boost::timer t;

	BODY_TAG body1, body2,body3;
	MSElementDescrP edp,edp2;
	double radius = 10 * UPM, radius_KI;
	mdlSolid_beginCurrTrans(ACTIVEMODEL);
	mdlCurrTrans_translateOrigin(new DPoint3d{ 100,0,0 });
	mdlCurrTrans_invScaleDoubleArray(&radius_KI, &radius, 1);

	mdlSolid_makeSphere(&body1, radius_KI);
	mdlSolid_makeCuboid(&body2, 1.5*radius_KI, 1.5*radius_KI, 1.5*radius_KI);
	mdlSolid_makePrism(&body3, radius_KI, radius_KI, 40);
	mdlSolid_unite(body2, body1);
	mdlSolid_endCurrTrans();
	mdlSolid_bodyToElement(&edp, body2, false, -1, -1, 1, NULL, ACTIVEMODEL);
	mdlSolid_bodyToElement(&edp2, body3, false, -1, -1, -1, NULL, ACTIVEMODEL);
	mdlElmdscr_add(edp2);
	//mdlElmdscr_add(edp);

	WPrintfString wpf(L"elapsed -> %0.2f", t.elapsed());
	mdlDialog_openInfoBox(wpf.c_str());
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
