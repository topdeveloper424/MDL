#pragma once
#include "DgnElementSetToolTest.h"

class DgnTestTool : DgnElementSetTool
{
public:
	static void InstallNewInstance(int toolId);
protected:
	DgnTestTool(int toolId) : DgnElementSetTool(toolId){}
	void _OnPostInstall() override { mdlDialog_dmsgsPrint(L"_OnPostInatll"); __super::_OnPostInstall(); }
	virtual void _OnRestartTool() override { mdlDialog_dmsgsPrint(L"_OnRestartTool"); InstallNewInstance(GetToolId()); }
	virtual bool _OnResetButton(DgnButtonEventCR ev) override { mdlDialog_dmsgsPrint(L"_OnResetButton"); return __super::_OnResetButton(ev); }
	virtual UsesSelection _AllowSelection() override { return UsesSelection::USES_SS_None; }
	virtual bool _DoGroups() override { return false; }
	virtual bool _NeedAcceptPoint() override { return true; }
	virtual void _SetupAndPromptForNextAction() override { SetupAndPromptForNextActionHelper(); mdlDialog_dmsgsPrint(L"_SetupAndpromptForNextAction"); }
	virtual bool _WantAdditionalLocate(DgnButtonEventCP ev) override {/* mdlDialog_dmsgsPrint(L"_WantAdditionalLocate"); */return  true; }
	virtual bool _OnModifierKeyTransition(bool wentDown, int key) override { mdlDialog_dmsgsPrint(L"_OnModifierKeyTransition"); return true; }
	virtual StatusInt _OnElementModify(EditElementHandleR el) override { mdlDialog_dmsgsPrint(L"_OnElementModify"); return ERROR; }
	virtual EditElementHandleP _BuildLocateAgenda(HitPathCP path, DgnButtonEventCP ev) override { mdlDialog_dmsgsPrint(L"_BuildLocateAgenda"); return __super::_BuildLocateAgenda(path,ev); }
	virtual bool _OnModifyComplete(DgnButtonEventCR ev) override { mdlDialog_dmsgsPrint(L"_OnModifyComplete"); return __super::_OnModifyComplete(ev); }
	virtual bool _OnDataButton(DgnButtonEventCR ev) override { mdlDialog_dmsgsPrint(L"_OnDataButton"); return __super::_OnDataButton(ev); }
	virtual void _LocateOneElement(DgnButtonEventCR ev, bool newSearch) override { mdlDialog_dmsgsPrint(L"_LocateOneElement"); __super::_LocateOneElement(ev, newSearch); }
};