//#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MstnPlatformAPI.h>
#include <Mstn\PSolid\mssolid.h>
#include <Mstn\PSolid\mssolid.fdf>
#include <DgnPlatform\DgnPlatformApi.h>

#include <iostream>
#include <list>
#include <algorithm>
#include "scanClass.h"
#include "HelloWorldcmd.h"
#include "PlaceLineTool.h"
// 由mke文件中的
// $(genSrc)$(sAppName)cmd.h   : $(baseDir)$(appName)cmd.r
// 生成

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT
using namespace std;

double UPM = 0;

int Scan_refCallback(ElementRefP, CallbackArgP, ScanCriteriaP);

void CreateAComplexShape(DPoint3d* basePtP)
{
	MSElement el;
	MSElementDescrP edP = NULL;
	DPoint3d pts[3], tmpPt;
	mdlComplexChain_createHeader(&el, true, 1);
	mdlElmdscr_new(&edP, NULL, &el);
	pts[0] = pts[1] = pts[2] = *basePtP;
	pts[1].x += UPM*0.3; pts[1].y += UPM*0.7;
	pts[2].x += UPM; pts[2].y += UPM;
	mdlArc_createByPoints(&el, NULL, pts);
	mdlElmdscr_appendElement(edP, &el);
	tmpPt = pts[0]; pts[0] = pts[2]; pts[2] = tmpPt;
	pts[1].x = pts[0].x; pts[1].y = pts[2].y;
	mdlLineString_create(&el, NULL, pts, 3);
	mdlElmdscr_appendElement(edP, &el);
	EditElementHandle eeh(edP, true, false, ACTIVEMODEL);
	eeh.AddToModel();
}

void CreateSolid(DPoint3d* basePt)
{
	DPoint3d pts[3], endPt;
	MSElementDescrP sectionEdp = NULL, SolidEdp = NULL;
	pts[0] = pts[1] = pts[2] = endPt = *basePt;
	double lng = 5 * UPM;
	pts[1].x = pts[2].x = (pts[2].x + lng);
	pts[1].y = pts[2].y + lng;
	endPt.z += 10 * UPM;
	mdlElmdscr_createFromVertices(&sectionEdp, NULL, pts, 3, true, 1);
	mdlSurface_project(&SolidEdp, sectionEdp, pts, &endPt, NULL);
	mdlElmdscr_freeAll(&sectionEdp);
	EditElementHandle eeh(SolidEdp, true, false, ACTIVEMODEL);
	eeh.AddToModel();
}

void CreateKISolid()
{
	BODY_TAG body1, body2;
	MSElementDescrP edp;

	mdlSolid_beginCurrTrans(ACTIVEMODEL);
	double radius = 200 * UPM, radius_KI;
	mdlCurrTrans_invScaleDoubleArray(&radius_KI, &radius, 1);
	mdlSolid_makeSphere(&body1, radius_KI);
	mdlSolid_makeCuboid(&body2, 1.5*radius_KI, 1.5*radius_KI, 1.5*radius_KI);
	mdlSolid_unite(body2, body1);
	mdlSolid_endCurrTrans();
	mdlSolid_bodyToElement(&edp, body2, false, -1, -1, 1, NULL, ACTIVEMODEL);

	EditElementHandle eeh(edp, true, false);
	eeh.AddToModel();

}

void OutPutMsg(WCharCP unparsed)
{
	mdlDialog_openInfoBox(L"中交水运规划设计院有限公司");
}

void TestCase1(WCharCP unparsed)
{
	//NotificationManager::OpenMessageBox(NotificationManager::MESSAGEBOX_TYPE_LargeOk, L"Interesting", NotificationManager::MESSAGEBOX_ICON_Question);
}

void TestCase2(WCharCP unparsed)
{
	double upm = mdlModelRef_getUorPerMaster(ACTIVEMODEL);
	double offset = 10 * upm;
	if (unparsed)
	{
		try
		{
			wstringstream ss;
			ss << unparsed;
			ss >> offset;
		}
		catch (const std::exception&)
		{
			wstring ss(unparsed);
			ss.append(L"不是数字！");
			mdlDialog_openInfoBox(ss.c_str());
		}
	}
	bvector<ElementId> vec;
	auto elelist = ACTIVEMODEL->GetReachableElements();
	DPoint3d p1 = { -1,0,0 };
	for each (ElementHandle handle in elelist)
	{
		if (handle.GetElementType() == MSElementTypes::LINE_STRING_ELM)
		{
			vec.push_back(handle.GetElementId());
		}
	}

	//MSElementDescrP edp = NULL;
	for (bvector<ElementId>::iterator itr = vec.begin(); itr != vec.end(); itr++)
	{
		MSElementDescrP edp1 = NULL, edp2 = NULL;
		auto line = ACTIVEMODEL->GetDgnModelP()->FindElementByID(*itr);
		DPoint3d startp1, endp1,startp2,endp2;
		EditElementHandle handle(line);
		if (SUCCESS == mdlElmdscr_copyParallel(&edp1, handle.GetElementDescrP(), &p1, offset, NULL))
		{
			mdlElmdscr_extractEndPoints(&startp1, NULL, &endp1, NULL, edp1, ACTIVEMODEL);
			//mdlElmdscr_add(edp);
		}
		if (SUCCESS == mdlElmdscr_copyParallel(&edp2, handle.GetElementDescrP(), &p1, -offset, NULL))
		{
			//mdlElmdscr_add(edp);
			mdlElmdscr_extractEndPoints(&startp2, NULL, &endp2, NULL, edp2, ACTIVEMODEL);
		}
		DSegment3d line1{ startp1,startp2 }, line2{ endp1,endp2 };
		EditElementHandle line1handle, line2handle;
		auto ativemodel = ISessionMgr::GetActiveDgnModelRefP();
		LineHandler::CreateLineElement(line1handle, NULL, line1, true, *ativemodel);
		LineHandler::CreateLineElement(line2handle, NULL, line2, true, *ativemodel);
		//line1handle.AddToModel(); line2handle.AddToModel();

		edp1->AddToChain(line1handle.GetElementDescrP());
		edp1->AddToChain(edp2);
		edp1->AddToChain(line2handle.GetElementDescrP());
		mdlElmdscr_assembleChains(&edp1, 1, ACTIVEMODEL);
		mdlElmdscr_add(edp1);
		handle.DeleteFromModel();

		mdlElmdscr_freeAll(&edp1);
		mdlElmdscr_freeAll(&edp2);
	}

	mdlDialog_openInfoBox(L"Done!");
}

void BuildLineElmAgenda(ElementAgendaR elelist)
{
	ScanCriteriaP scp = ScanCriteria::Create();
	scp->SetDrawnElements();
	scp->SetModelRef(ACTIVEMODEL);
	scp->AddSingleElementTypeTest(MSElementTypes::LINE_ELM);
	mdlScanCriteria_setReturnType(scp, MSSCANCRIT_ITERATE_ELMREF, FALSE, FALSE);
	scp->SetElemRefCallback([](ElementRefP eleRefp, CallbackArgP args, ScanCriteriaP scp)->int
	{
		ElementAgendaP agdp = reinterpret_cast<ElementAgendaP>(args);
		agdp->Insert(eleRefp, scp->GetModelRef());
		return SUCCESS;
	}
	, &elelist);
	scp->Scan();
	ScanCriteria::Delete(scp);
}

void BuildJoinElmAgenda(ElementAgendaR outelelist, const ElementAgendaR inelelist)
{
	if (inelelist.size()==0)	return;
	if (inelelist.size()<2)
	{
		outelelist.Insert(inelelist.front().GetElementRef(), ACTIVEMODEL);
		return;
	}
	else
	{
		const ElemAgendaEntry* NextEle = inelelist.GetFirst();
		outelelist.Insert(NextEle->GetElementRef(), ACTIVEMODEL);
		ElemAgendaEntry* result;
		while (
			inelelist.end() != (result = find_if(inelelist.begin() + 1, inelelist.end(), [&](ElemAgendaEntry const a)
			{
			return a.GetElementCP()->line_3d.start.Distance(NextEle->GetElementCP()->line_3d.end) < 10;
			}))
		)
		{
			NextEle = result;
			outelelist.Insert(NextEle->GetElementRef(), ACTIVEMODEL);
		}
	}

}

void TestCase3(WCharCP unparsed)
{
	ElementAgenda elelist;
	BuildLineElmAgenda(elelist);

	ElementAgenda sortedelelist;
	BuildJoinElmAgenda(sortedelelist, elelist);

	wstringstream wss;
	for each (auto ele in sortedelelist)
	{
		wss << ele.GetElementId() << "->";
	}
	//WChar numstr[128];
	//WString str(numstr);
	//str = str + L"test";
	//
	//if (result != elelist.end())
	//{
	//	swprintf(numstr, L"The tail of first agenda eleID is: %d",result->GetElementId());
	//} 
	//else
	//{
	//	swprintf(numstr, L"Not Found the ElementID %d tail Element of %d elements!",elelist.GetFirst()->GetElementId(),elelist.size());
	//}
	mdlDialog_dmsgsPrint(wss.str().c_str());
}

int Scan_refCallback(ElementRefP elerefp, CallbackArgP args, ScanCriteriaP scp)
{
	ElementAgendaP adgp = reinterpret_cast<ElementAgendaP>(args);
	adgp->Insert(elerefp, scp->GetModelRef());
	return SUCCESS;
}
void ScanTest(WCharCP unparsed)
{
	ElementAgenda elelist;
	ScanCriteriaP scp = ScanCriteria::Create();
	scp->SetDrawnElements();
	scp->SetModelRef(ACTIVEMODEL);
	scp->AddSingleElementTypeTest(MSElementTypes::LINE_ELM);
	scp->AddSingleElementTypeTest(MSElementTypes::LINE_STRING_ELM);
	mdlScanCriteria_setReturnType(scp, MSSCANCRIT_ITERATE_ELMREF, FALSE, FALSE);
	scp->SetElemRefCallback((PFScanElemRefCallback)Scan_refCallback, &elelist);
	scp->Scan();
	ScanCriteria::Delete(scp);
	size_t elenum = elelist.size();
	WChar numstr[128];
	swprintf_s(numstr, 128, L"线串和线的总数为：%d", elenum);
	mdlDialog_dmsgsPrint(numstr);
}

void StartTool(WCharCP unparsed)
{
	PlaceLineTool::InstallNewInstance(CMDNAME_PlaceBsSurfaceTool, PROMPT_FirstPoint);
}

void CreateLineTool(WCharCP unparsed)
{
	CreateLine2Tool::InstallNewInstance(CMDNAME_PlaceBsSurfaceTool, PROMPT_FirstPoint);
}

static MdlCommandNumber s_commandNumbers[] =
{
	{ OutPutMsg, CMD_PDIWT_SHOWMSGDIALOG_CASE1 },
	{ OutPutMsg, CMD_PDIWT_SHOWMSGDIALOG_CASE2 },
	{ ScanTest,  CMD_PDIWT_SCANTEST },
	{ StartTool, CMD_PDIWT_STARTTOOL},
	{ CreateLineTool, CMD_PDIWT_CREATELINETOOL },
	{ TestCase1, CMD_TEST_CASE1 },
	{ TestCase2, CMD_TEST_CASE2 },
	{ TestCase3, CMD_TEST_CASE3 },
	0
};

extern "C" void MdlMain(int argc, WCharCP argv[])
{
	UPM = mdlModelRef_getUorPerMaster(ACTIVEMODEL);

	RscFileHandle rfHandle;
	if (mdlResource_openFile(&rfHandle, NULL, RSC_READONLY))
	{
		mdlOutput_errorU(L"无法打开资源文件");
		mdlSystem_exit(-1, 1);
	}
	mdlState_registerStringIds(STRINGLISTID_Commands, STRINGLISTID_Prompts);
	mdlSystem_registerCommandNumbers(s_commandNumbers);
	mdlParse_loadCommandTable(NULL);
}