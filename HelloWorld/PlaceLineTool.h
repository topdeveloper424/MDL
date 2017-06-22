#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\ElementPropertyUtils.h>
#include <DgnPlatform\DgnPlatformApi.h>
#include <DgnView\AccuDraw.h>
#include <DgnView\IRedraw.h>
#include "HelloWorldids.h"

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT
USING_NAMESPACE_BENTLEY_DGNPLATFORM

struct PlaceLineTool : DgnPrimitiveTool
{
protected:
	bvector<DPoint3d> m_points;
	PlaceLineTool(int toolName, int toolPrompt) : DgnPrimitiveTool(toolName, toolPrompt) {}

	virtual void _OnPostInstall() override;
	virtual void _OnRestartTool() override;
	virtual bool _OnDataButton(DgnButtonEventCR ev) override;
	virtual bool _OnResetButton(DgnButtonEventCR ev) override;
	virtual void _OnDynamicFrame(DgnButtonEventCR ev) override;
	virtual void _OnUndoPreviousStep()override;

	bool CreateElement(EditElementHandleR eeh, bvector<DPoint3d> const& points);
	void CreateAcceptedSegmentsTransient();
	void SetupAndPromptForNextAction();

public:
	static void InstallNewInstance(int toolId, int toolPrompt);
};

struct CreateLine2Tool :DgnPrimitiveTool
{
protected:
	bvector<DPoint3d> m_points;
	
	CreateLine2Tool(int toolName, int toolPrompt) :DgnPrimitiveTool(toolName, toolPrompt){}

	virtual	void _OnPostInstall() override;
	virtual	void _OnRestartTool() override;
	virtual bool _OnDataButton(DgnButtonEventCR ev) override;
	virtual bool _OnResetButton(DgnButtonEventCR ev) override;
	virtual void _OnDynamicFrame(DgnButtonEventCR ev) override;

	bool CreateElement(EditElementHandleR eeh, bvector<DPoint3d> const& points);
	void SetupAndPromptForNextAction();

public:
	static void InstallNewInstance(int toolId, int toolPrompt);
};