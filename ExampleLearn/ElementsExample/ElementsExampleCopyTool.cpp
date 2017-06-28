#include "ElementsExample.h"

struct ElementsExampleCopyTool: DgnElementSetTool
{
private:
	WString m_modelName;
	
	ElementsExampleCopyTool(int toolId, WCharCP modelName): DgnElementSetTool(toolId),m_modelName(modelName){}

	bool CopyElementToModel(ElementRefP elemRef, DgnModelP destinationModel);
	void CopyElement(ElementRefP elemRef);

protected:
	void _OnPostInstall() override;
	bool _OnDataButton(DgnButtonEventCR ev) override;
	void _OnRestartTool() override;
	void _SetupAndPromptForNextAction() override;

public:
	int _OnElementModify(EditElementHandleR el) override;
	static void InstallNewInstance(int toolId, WCharCP modelName);
};

bool ElementsExampleCopyTool::CopyElementToModel(ElementRefP elemRef, DgnModelP destinationModel)
{
	bool elemCopied = false;
	if (nullptr != destinationModel)
	{
		ElementCopyContext copier(destinationModel);
		EditElementHandle copied(elemRef, elemRef->GetDgnModelP());
		if (SUCCESS == copier.DoCopy(copied))
		{
			elemCopied = true;
			WString message = WString(L"Element copied to Model:") + destinationModel->GetModelName();
			mdlDialog_openInfoBox(message.c_str());
		}
	}
	return elemCopied;
}

void ElementsExampleCopyTool::CopyElement(ElementRefP elemRef)
{
	if (WString::IsNullOrEmpty(m_modelName.c_str()))
	{
		if (CopyElementToModel(elemRef, ISessionMgr::GetActiveDgnModelP()))
			return;
	}
	else
	{
		DgnFileP activeFile = ISessionMgr::GetActiveDgnFile();
		if (nullptr != activeFile)
		{
			ModelId mId = activeFile->FindModelIdByName(m_modelName.c_str());
			if (mId != INVALID_MODELID)
			{
				DgnModelP destinationModel = activeFile->LoadRootModelById(nullptr, mId, true);
				if (CopyElementToModel(elemRef, destinationModel))
					return;
			}
		}
	}
	mdlDialog_openInfoBox(L"Some problem occured while copying the element. Make sure the model specified does exist.");
}

void ElementsExampleCopyTool::_OnPostInstall()
{
	_SetLocateCursor(true);
}

bool ElementsExampleCopyTool::_OnDataButton(DgnButtonEventCR ev)
{
	HitPathCP hitPath = _DoLocate(ev, true, BENTLEY_NAMESPACE_NAME::DgnPlatform::ComponentMode::Innermost);
	if (nullptr != hitPath)
	{
		ElementRefP elemToCopy = hitPath->GetHeadElem();
		CopyElement(elemToCopy);

		_OnRestartTool();
	}
	return true;
}

void ElementsExampleCopyTool::_OnRestartTool()
{
	InstallNewInstance(GetToolId(), m_modelName.c_str());
}

void ElementsExampleCopyTool::_SetupAndPromptForNextAction()
{
	UInt32 msgId;
	msgId = PROMPT_FristPoint;

	bool doLoate = true;

	if (GetElementAgenda().GetCount()<1)
	{
		msgId = PROMPT_SelectElement;
		doLoate = true;
	}
	else
	{
		msgId = PROMPT_CopyPoint;
		doLoate = false;
	}

	mdlAccuSnap_enableSnap(!doLoate);
	__super::_SetLocateCursor(doLoate);
	mdlOutput_rscPrintf(MSG_PROMPT, NULL, STRINGLISTID_Prompts, MSG_PROMPT);
}

int ElementsExampleCopyTool::_OnElementModify(EditElementHandleR el)
{
	return ERROR;
}

void ElementsExampleCopyTool::InstallNewInstance(int toolId, WCharCP modelName)
{
	ElementsExampleCopyTool* tool = new ElementsExampleCopyTool(toolId, modelName);
	tool->InstallTool();
}

/************************************************************************/
/*In this case "unparsed" is expected to be a model name				*/
/************************************************************************/
Public void elementsExampleCopyElement(WCharCP unprased)
{
	ElementsExampleCopyTool::InstallNewInstance(CMDNAME_ElementsExampleCopy, unprased);
}