#include "PDIWT_Gadget.h"
#include "libxl.h"

using namespace System::Windows::Forms;
using namespace msclr::interop;

using namespace libxl;

//extern TableYTolerance g_tableytolerance;
struct TextInfo
{
	WString m_textcontent;
	DPoint3d origin;
};

struct TabelCellInfo
{
	size_t row;
	size_t column;
	DRange2d cellrange;
	WString text;
};

struct CreateTableTool : DgnElementSetTool
{
private:
	//Extract the textInfo
	void _GetGridXYRange(bstdset<double>& _xrange, bstdset<double>& _yrange);
	void _GetGridXYRange_ProcessLineEle(bstdset<double>& _xrange, bstdset<double>& _yrange,ElemAgendaEntry& _ele);
	void _GetGridCellInfo(bvector<TabelCellInfo>& _tablecellsinfo, const bstdset<double> _xrange, const bstdset<double> _yrange);
	void _ExtractTextInfo(bvector<TextInfo>& _selectedtextesinfo);
	StatusInt _OutputTable(WString outFileName);

protected:
	CreateTableTool(int toolId) : DgnElementSetTool(toolId) {}
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
	//virtual bool _FilterAgendaEntries() override;
	virtual bool _OnModifyComplete(DgnButtonEventCR ev) override;


public:
	static void InstallNewInstance(int toolId);
};

StatusInt CreateTableTool::_OutputTable(WString outFileName)
{
	bstdset<double> _xrange, _yrange;
	_GetGridXYRange(_xrange, _yrange);
	if (_xrange.size() > 0 && _yrange.size() > 0)
	{
		bvector<TabelCellInfo> _tabelcellinfo;
		_GetGridCellInfo(_tabelcellinfo, _xrange, _yrange);
		bvector<TextInfo> _selectedtextesinfo;
		_ExtractTextInfo(_selectedtextesinfo);

		for (auto _textinfo : _selectedtextesinfo)
		{
			auto itr = std::find_if(_tabelcellinfo.begin(), _tabelcellinfo.end(), [&_textinfo](TabelCellInfo _tt) { return _tt.cellrange.Contains(_textinfo.origin); });
			if (itr != _tabelcellinfo.end()) itr->text += _textinfo.m_textcontent;
		}
		Book* book = xlCreateXMLBook();
		if (book)
		{
			WString _excelsheetname = BeFileName::GetFileNameWithoutExtension(outFileName.GetWCharCP());
			Sheet* sheet = book->addSheet(_excelsheetname.GetWCharCP());
			if (sheet)
			{
				for each(auto _cellinfo in _tabelcellinfo)
				{
					//mdlDialog_dmsgsPrint(WPrintfString(L"row:{%d}, col:{%d}, Text {%s}", _cellinfo.row, _cellinfo.column, _cellinfo.text));

					//_sheet->Cells[_cellinfo.row, _cellinfo.column]->Value = marshal_as<System::String^>(_cellinfo.text);
					sheet->writeStr((int)_cellinfo.row, (int)_cellinfo.column, _cellinfo.text.GetWCharCP());
				}
			}
			if (book->save(outFileName.GetWCharCP())) return SUCCESS;
			book->release();
		}
	}
	return ERROR;
}

//  [11/3/2017 sudongsheng]
//	获得表格线的从小到大的_xrange和_yrange
void CreateTableTool::_GetGridXYRange(bstdset<double>& _xrange, bstdset<double>& _yrange)
{
	ElementAgendaR _eleagenda = GetElementAgenda();
	for (auto _ele : _eleagenda)
	{
		if (_ele.GetElementType() == LINE_ELM)
		{
			//LineHandler* _line_handlerP = dynamic_cast<LineHandler*>(_ele.GetDisplayHandler());
			//if (nullptr == _line_handlerP) continue;
			//CurveVectorPtr _linecv;
			//_line_handlerP->GetCurveVector(_ele, _linecv);
			//DVec3d _lineVector;
			//DPoint3d _lineStartPoint;
			//_linecv->GetStartEnd(_lineStartPoint, DPoint3d(), _lineVector, DVec3d());
			//if (_lineVector.IsParallelTo(DVec3d::UnitX()))
			//{
			//	_yrange.insert(_lineStartPoint.y);
			//}
			//else if (_lineVector.IsParallelTo(DVec3d::UnitY()))
			//{
			//	_xrange.insert(_lineStartPoint.x);
			//}
			_GetGridXYRange_ProcessLineEle(_xrange, _yrange, _ele);
		}
		else if (_ele.GetElementType() == SHAPE_ELM)
		{
			DisplayHandlerP _displayHandle = dynamic_cast<DisplayHandlerP>(_ele.GetDisplayHandler());
			if(nullptr == _displayHandle) continue;
			ElementAgenda _shapeeleagd;
			DropGeometryPtr _shapedg = DropGeometry::Create();
			_shapedg->SetOptions(DropGeometry::Options::OPTION_LinearSegments);
			_displayHandle->Drop(_ele, _shapeeleagd, *_shapedg);
			for (auto _subele : _shapeeleagd)
			{
				_GetGridXYRange_ProcessLineEle(_xrange, _yrange, _subele);
			}
		}
	}
}

void CreateTableTool::_GetGridXYRange_ProcessLineEle(bstdset<double>& _xrange, bstdset<double>& _yrange, ElemAgendaEntry & _ele)
{
	LineHandler* _line_handlerP = dynamic_cast<LineHandler*>(_ele.GetDisplayHandler());
	if (nullptr == _line_handlerP) return;
	CurveVectorPtr _linecv;
	_line_handlerP->GetCurveVector(_ele, _linecv);
	DVec3d _lineVector;
	DPoint3d _lineStartPoint;
	_linecv->GetStartEnd(_lineStartPoint, DPoint3d(), _lineVector, DVec3d());
	if (_lineVector.IsParallelTo(DVec3d::UnitX()))
	{
		_yrange.insert(_lineStartPoint.y);
	}
	else if (_lineVector.IsParallelTo(DVec3d::UnitY()))
	{
		_xrange.insert(_lineStartPoint.x);
	}

	//delete _line_handlerP;
}

// 将单元格行列数与单元格【起始索引为1,1】在二维空间中的范围联系起来
void CreateTableTool::_GetGridCellInfo(bvector<TabelCellInfo>& _tablecellsinfo, const bstdset<double> _xrange, const bstdset<double> _yrange)
{
	bvector<double> _xrangevector(_xrange.begin(), _xrange.end());
	bvector<double> _yrangevector(_yrange.rbegin(), _yrange.rend());

	size_t _totalrownum = _yrange.size() - 1;
	size_t _totalcolnum = _xrange.size() - 1;

	for (size_t _row = 0; _row < _totalrownum; _row++)
	{
		for (size_t _col = 0; _col < _totalcolnum; _col++)
		{
			TabelCellInfo _cell = { _row ,_col,DRange2d::From(_xrangevector[_col],_yrangevector[_row + 1],_xrangevector[_col + 1],_yrangevector[_row]),L"" };
			_tablecellsinfo.push_back(_cell);
		}
	}
}

//获得所选择的所有文字信息和位置信息
void CreateTableTool::_ExtractTextInfo(bvector<TextInfo>& _selectedtextesinfo)
{
	_selectedtextesinfo.clear();
	ElementAgendaR agd = GetElementAgenda();
	for (auto ele : agd)
	{
		if (ele.GetElementType() != TEXT_ELM && ele.GetElementType() != TEXT_NODE_ELM)
			continue;

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
		_selectedtextesinfo.push_back(textinfos);
	}
}

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


bool CreateTableTool::_OnModifyComplete(DgnButtonEventCR ev)
{
	WString _activefilename = BeFileName::GetFileNameWithoutExtension(ACTIVEMODEL->GetDgnFileP()->GetFileName().GetWCharCP())  ;
	WCharCP _activemodelname = ACTIVEMODEL->GetDgnModelP()->GetModelName();
	WPrintfString _defaultexcelname(L"%s-%s-OutTable", _activefilename, _activemodelname);
	BeFileName _outexclfile;
	if (FALSE == mdlDialog_fileCreate(_outexclfile, 0, 0, _defaultexcelname.GetWCharCP(), L"*.xlsx,*.*", nullptr, L"输入要导出的文件名"))
	{
		//mdlDialog_dmsgsPrint(outcsvFile.c_str());
		if (_OutputTable(_outexclfile.c_str()))
			mdlOutput_messageCenter(OutputMessagePriority::Error, WPrintfString(L"%s 创建失败!", _outexclfile), WPrintfString(L"%s 创建失败!", _outexclfile), OutputMessageAlert::Balloon);
		else
			mdlOutput_messageCenter(OutputMessagePriority::Info, WPrintfString(L"%s 创建成功!", _outexclfile), WPrintfString(L"%s 创建成功!", _outexclfile), OutputMessageAlert::None);
	}

	return __super::_OnModifyComplete(ev);
}


void CreateTableTool::InstallNewInstance(int toolId)
{
	CreateTableTool* tool = new CreateTableTool(toolId);
	tool->InstallTool();
}

public ref class CreateTableActionDelegate
{
public:
	static void DoAction()
	{
		CreateTableTool::InstallNewInstance(CMDNAME_CreateTableTool);
	}
};

void CreateTable(WCharCP unparsed)
{
	System::Action^ _doaction = gcnew System::Action(&CreateTableActionDelegate::DoAction);
	PDIWT_Encrypt::Entrance::VerifyActivationState(_doaction);
}