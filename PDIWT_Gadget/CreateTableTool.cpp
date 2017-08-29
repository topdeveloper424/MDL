#include "PDIWT_Gadget.h"

extern TableYTolerance g_tableytolerance;
struct TextInfo
{
	WString m_textcontent;
	DPoint3d origin;
}; 

struct CreateTableTool : DgnElementSetTool
{
private :
	std::list<TextInfo> tabelInfo;

protected:
	CreateTableTool(int toolId) : DgnElementSetTool(toolId){}
	virtual StatusInt _OnElementModify(EditElementHandleR el) override;
	//state logic
	virtual bool _NeedAcceptPoint() override { return true; }
	virtual void _SetupAndPromptForNextAction() override;
	//Extended Selection
	virtual UsesDragSelect _AllowDragSelect() override { return UsesDragSelect::USES_DRAGSELECT_Box; }
	//Element Dynamic
	virtual bool _WantDynamics() override { return false; }
	//Button Event
	virtual void _OnRestartTool() override { InstallNewInstance(GetToolId()); }
	virtual bool _OnResetButton(DgnButtonEventCR ev) override { _OnRestartTool(); return true; }
	//Populating Elements
	virtual bool _FilterAgendaEntries() override;
	virtual bool _OnModifyComplete(DgnButtonEventCR ev) override;

	//Extract the textInfo
	StatusInt _ExtractTextInfo();
	void OutputTable(BeFileName outFileName);
	
public:
	static void InstallNewInstance(int toolId);
	
};

BENTLEY_NAMESPACE_NAME::StatusInt CreateTableTool::_OnElementModify(EditElementHandleR el)
{
	return ERROR;
}

void CreateTableTool::_SetupAndPromptForNextAction()
{
	UInt32 msgId;
	msgId = PROMPT_BoxSelectPoint;
	if (GetElementAgenda().GetCount() > 1)
		msgId = PROMPT_AceeptCreatePoint;
	mdlOutput_rscPrintf(MSG_PROMPT, NULL, STRINGLISTID_Prompts, msgId);
}

bool CreateTableTool::_FilterAgendaEntries()
{

	bool changed = false;
	ElementAgendaR agd = GetElementAgenda();
	//mdlDialog_dmsgsPrint(WPrintfString(L"Before Filter: The agenda number is %d", agd.GetCount()).c_str());

	ElementAgenda::iterator itr = agd.begin();
	while (itr!= agd.end())
	{
		int eleType = itr->GetElementType();
		if (eleType == TEXT_ELM || eleType == TEXT_NODE_ELM)
		{
			++itr;
		}
		else
		{
			itr = agd.erase(itr);
			changed = true;
		}
	}
	return changed;	
}

bool CreateTableTool::_OnModifyComplete(DgnButtonEventCR ev)
{
	if (_ExtractTextInfo() == SUCCESS)
	{
		tabelInfo.sort([](const TextInfo& left, const TextInfo& right) {return left.origin.x < right.origin.x;});
		tabelInfo.sort([](const TextInfo& left, const TextInfo& right) {return left.origin.y > right.origin.y; });
		BeFileName outcsvFile;
		if (FALSE == mdlDialog_fileCreate(outcsvFile, 0, 0, L"OutTable", L"*.csv,*.*", nullptr, L"输入要导出的文件名"))
		{
			//mdlDialog_dmsgsPrint(outcsvFile.c_str());
			OutputTable(outcsvFile);
			mdlOutput_messageCenter(OutputMessagePriority::Info, WPrintfString(L"%s 创建成功!", outcsvFile), WPrintfString(L"%s 创建成功!", outcsvFile), OutputMessageAlert::None);
		}
	}
	return __super::_OnModifyComplete(ev);
}

BENTLEY_NAMESPACE_NAME::StatusInt CreateTableTool::_ExtractTextInfo()
{
	tabelInfo.clear();
	ElementAgendaR agd = GetElementAgenda();
	for (auto ele : agd)
	{
		ITextQueryCP textQueryHandler = ele.GetITextQuery();
		if (textQueryHandler == nullptr) continue;
		T_ITextPartIdPtrVector textPartIds;
		textQueryHandler->GetTextPartIds(ele, *ITextQueryOptions::CreateDefault(), textPartIds);
		//Create TextInfo
		TextInfo textinfos;
		for each (auto textPartId in textPartIds)
		{
			TextBlockPtr textBlock = textQueryHandler->GetTextPart(ele, *textPartId);
			textinfos.m_textcontent += textBlock->ToString();
		}
		DisplayHandlerP  textDisplayHandler = ele.GetDisplayHandler();
		if (textDisplayHandler == nullptr) continue;
		textDisplayHandler->GetTransformOrigin(ele, textinfos.origin);
		tabelInfo.push_back(textinfos);
	}
	if (tabelInfo.empty()) return ERROR; else return SUCCESS;	
}

void CreateTableTool::OutputTable(BeFileName outFileName)
{
	std::wofstream oFile(outFileName,std::ios::out);
	oFile.imbue((std::locale)"chs");
	double forwardy = 0;
	double uorPerMM = ACTIVEMODEL->GetModelInfoCP()->GetUorPerMeter() / 1000;
	for (auto itr = tabelInfo.begin(); itr != tabelInfo.end(); ++itr)
	{
		if (itr == tabelInfo.begin())
		{
			forwardy = itr->origin.y;
			oFile << itr->m_textcontent.c_str() << ",";
		}
		else
		{
			if (std::abs(forwardy - itr->origin.y) >= g_tableytolerance.tolerance * uorPerMM)
				oFile << std::endl;
			oFile << itr->m_textcontent.c_str() << ",";
			forwardy = itr->origin.y;
		}
	}
	//int count = 0;
	//for each (auto info in tabelInfo)
	//{
	//	oFile << info.m_textcontent.c_str() << ",";
	//	count++;
	//	if (count == 12)
	//	{
	//		oFile << std::endl;
	//		count = 0;
	//	}
	//}
	oFile.close();
}

void CreateTableTool::InstallNewInstance(int toolId)
{
	CreateTableTool* tool = new CreateTableTool(toolId);
	tool->InstallTool();
}

void CreateTable(WCharCP unparsed)
{
	CreateTableTool::InstallNewInstance(CMDNAME_CreateTableTool);
}