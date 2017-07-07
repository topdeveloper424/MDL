#include "PDIWT_Gadget.h"
extern OffSetWidth g_offsetwidth;


struct ParallelAreaTool : DgnElementSetTool
{
private:
	double m_upm;
	bool m_isAceeptPoint = false;
protected:
	ParallelAreaTool(int toolId) : DgnElementSetTool(toolId)
	{
		m_upm = mdlModelRef_getUorPerMaster(ACTIVEMODEL);
	}
	virtual bool _WantDynamics() override { return false; }		//不进行动态
	virtual bool _NeedAcceptPoint() override { return true; }	//不需要额外的点进行确认
	//virtual UsesDragSelect _AllowDragSelect() override { return UsesDragSelect::USES_DRAGSELECT_Box; }	//允许进行框选
	virtual void _OnRestartTool()override { InstallNewInstance(GetToolId()); }
	virtual bool _OnResetButton(DgnButtonEventCR ev) override { _OnRestartTool(); return true; }

	virtual void _OnPostInstall() override;
	virtual void _SetupAndPromptForNextAction() override;
	virtual bool _FilterAgendaEntries() override;
	virtual bool _OnPostLocate(HitPathCP path, WStringR cantAcceptReason) override;
	//virtual EditElementHandleP _BuildLocateAgenda(HitPathCP path, DgnButtonEventCP ev) override;
	virtual StatusInt _OnElementModify(EditElementHandleR el) override;
	virtual bool _WantAdditionalLocate(DgnButtonEventCP ev) override;
public:
	static void InstallNewInstance(int toolId);
};


void ParallelAreaTool::_OnPostInstall()
{
	AccuSnap::GetInstance().EnableSnap(true);
	__super::_OnPostInstall();
}

void ParallelAreaTool::_SetupAndPromptForNextAction()
{
	UInt32 msgId;
	msgId = PROMPT_FirstPoint;

	if (GetElementAgenda().GetCount() >= 1)
		msgId = PROMPT_AceeptPoint;
	mdlOutput_rscPrintf(MSG_PROMPT, NULL, STRINGLISTID_Prompts, msgId);
}

BENTLEY_NAMESPACE_NAME::StatusInt ParallelAreaTool::_OnElementModify(EditElementHandleR el)
{
	if (g_offsetwidth.width == 0)
		return ERROR;
	MSElementDescrP edp1 = nullptr, edp2 = nullptr;
	DPoint3d startp1, endp1, startp2, endp2, oritation = {-1,0,0};
	if (SUCCESS == mdlElmdscr_copyParallel(&edp1, el.GetElementDescrP(),&oritation,g_offsetwidth.width*m_upm,nullptr))
		mdlElmdscr_extractEndPoints(&startp1, nullptr, &endp1, nullptr, edp1, ACTIVEMODEL);
	if (SUCCESS == mdlElmdscr_copyParallel(&edp2, el.GetElementDescrP(), &oritation, -g_offsetwidth.width*m_upm, nullptr))
		mdlElmdscr_extractEndPoints(&startp2, nullptr, &endp2, nullptr, edp2, ACTIVEMODEL);

	DSegment3d line1{ startp1,startp2 }, line2{ endp1,endp2 };
	EditElementHandle line1handle, line2handle;
	auto ativemodel = ISessionMgr::GetActiveDgnModelRefP();
	LineHandler::CreateLineElement(line1handle, &el, line1, true, *ativemodel);
	LineHandler::CreateLineElement(line2handle, &el, line2, true, *ativemodel);

	edp1->AddToChain(line1handle.GetElementDescrP());
	edp1->AddToChain(edp2);
	edp1->AddToChain(line2handle.GetElementDescrP());
	mdlElmdscr_assembleChains(&edp1, 1, ACTIVEMODEL);
	mdlElmdscr_simplifyComplexChainOrShape(&edp1, ACTIVEMODEL);
	mdlElmdscr_add(edp1);
	el.DeleteFromModel();

	mdlElmdscr_freeAll(&edp1);
	mdlElmdscr_freeAll(&edp2);
	return SUCCESS;
}

bool ParallelAreaTool::_WantAdditionalLocate(DgnButtonEventCP ev)
{
	if (nullptr == ev)
		return true;

	return ev->IsControlKey();
}

bool ParallelAreaTool::_FilterAgendaEntries()
{
	auto agd = GetElementAgenda();
	auto number = agd.GetCount();
	for each (auto ele in agd)
	{
		int eleType = ele.GetElementType();
		if (eleType == MSElementTypes::LINE_ELM || eleType == MSElementTypes::LINE_STRING_ELM || eleType == MSElementTypes::CMPLX_STRING_ELM)
			continue;
		else
			ele.Invalidate();
	}
	number++;
	agd.DropInvalidEntries();
	return true;
}

bool ParallelAreaTool::_OnPostLocate(HitPathCP path, WStringR cantAcceptReason)
{
	if (!__super::_OnPostLocate(path, cantAcceptReason))
		return false;

	if (nullptr == path)
		return false;

	ElementHandle eh(path->GetHeadElem(), path->GetRoot());
	int eleType = eh.GetElementType();
	if (eleType == MSElementTypes::LINE_ELM || eleType == MSElementTypes::LINE_STRING_ELM || eleType == MSElementTypes::CMPLX_STRING_ELM)
		return true;
	
	return false;
}

//EditElementHandleP ParallelAreaTool::_BuildLocateAgenda(HitPathCP path, DgnButtonEventCP ev)
//{
//	if (ev->IsControlKey() && 0!= GetElementAgenda().GetCount())
//	{
//		GetElementAgenda().Clear();
//	}
//	EditElementHandle eeh(path->GetHeadElem(), path->GetRoot());
//	return GetElementAgenda().Insert(eeh);
//}

void ParallelAreaTool::InstallNewInstance(int toolId)
{
	ParallelAreaTool* tool = new ParallelAreaTool(toolId);
	tool->InstallTool();
}

void ParallelArea(WCharCP unparsed)
{
	ParallelAreaTool::InstallNewInstance(CMDNAME_ParallelAreaTool);
}