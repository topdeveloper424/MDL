#include "CellExample.h"

void CommandFunction_CellExample(WCharCP unparsed){}

static MdlCommandNumber s_commandNumber[] =
{
	{ CmdHandler(openDialogFunction),CMD_PDIWT_CELLEXAMPLE_OPEN},
	{ CmdHandler(setListView),CMD_PDIWT_CELLEXAMPLE_LISTTOGGLE},
	nullptr
};

extern "C" void MdlMain(int argc, WCharCP argv[])
{
	RscFileHandle rfHandle;
	if (mdlResource_openFile(&rfHandle, nullptr, RSC_READONLY))
	{
		mdlOutput_errorU(L"无法打开资源文件");
		mdlSystem_exit(-1, 1);
	}
	mdlSystem_registerCommandNumbers(s_commandNumber);
	mdlParse_loadCommandTable(nullptr);
	mdlState_registerStringIds(STRINGLISTID_Commands, STRINGLISTID_Prompts);
}

void PrintFloats(int n, ...)
{
	int i;
	double val;
	printf("Printing floats:");
	va_list	vl;
	va_start(vl, n);
	for (i = 0; i < n; i++)
	{
		val = va_arg(vl, double);
		printf("[%.2f]", val);
	}
	va_end(vl);
	printf("\n");
}


void GetFileNames(WString filePathList)
{
	BeFileListIterator fileIterator(R"(C:\*)", false);
	BeFileName filename;
	int i = 0;
	while (SUCCESS == fileIterator.GetNextFileName(filename))
	{
		wprintf(L"[File %d]:%s\n", i, filename.GetName());
		i++;
	}
}

void DisplayLevelsColorRGB(DgnFileR file)
{
	LevelCacheR levelCache = file.GetLevelCacheR();
	for (const auto & level : levelCache)
	{
		LevelDefinitionColor byLevelColor = level.GetByLevelColor();
		IntColorDef colorDef;
		DgnColorMap::ExtractElementColorInfo(&colorDef, nullptr, nullptr, nullptr, nullptr, byLevelColor.GetColor(), *byLevelColor.GetDefinitionFile());
		RgbColorDef rgbColorDef = colorDef.m_rgb;
		wprintf(L"Level name:%s, ByLevel color RGB:(%d,%d,%d)\n", level.GetName(), rgbColorDef.red, rgbColorDef.green, rgbColorDef.blue);
	}
}

void WriteTexts()
{
	DgnTextStylePtr textStyle = DgnTextStyle::GetByName(L"5mm", *ISessionMgr::GetActiveDgnFile());
	if (textStyle != nullptr)
	{
		TextBlockPtr textBlock = TextBlock::Create(*textStyle, *ISessionMgr::GetActiveDgnModelP());
		textBlock->AppendText(L"I love MS");
		textBlock->AppendParagraphBreak();
		ParagraphPropertiesPtr paraProps = textBlock->GetParagraphPropertiesForAdd().Clone();
		IndentationDataPtr indentationData = IndentationData::Create();
		indentationData->SetFirstLineIndent(200);
		paraProps->SetIndentation(*indentationData);
		textBlock->SetParagraphPropertiesForAdd(*paraProps);
		textBlock->AppendText(L"create by code!");

		EditElementHandle eeh;
		if (TEXTBLOCK_TO_ELEMENT_RESULT_Success == TextHandlerBase::CreateElement(eeh, nullptr, *textBlock))
		{
			eeh.AddToModel();
		}
	}
}

void GetCellLibraryNames()
{
	DgnFileP library;
	BeFileName libraryname;
	mdlCell_getLibraryName(libraryname);
	if (SUCCESS == mdlCell_getLibraryObject(&library, libraryname.GetName(), false))
	{
		mdlDialog_dmsgsPrint(library->GetFileName().c_str());
		DgnIndexIteratorP pDgnIndexIterator = mdlModelIterator_create(library);
		mdlModelIterator_setAcceptCellsOnly(pDgnIndexIterator, true);
		DgnIndexItemP pDgnIndexItem;
		while (pDgnIndexItem = mdlModelIterator_getNext(pDgnIndexIterator))
		{

			WPrintfString info(L"Cell Name:{%s} Cell Type:{%d}", pDgnIndexItem->GetName(),mdlModelItem_getCellType(pDgnIndexItem));
			mdlDialog_dmsgsPrint(info.c_str());
		}
		mdlModelIterator_free(pDgnIndexIterator);
		//auto models = library->GetLoadedModelsCollection();
		//for each (auto model in models)
		//{
		//	mdlDialog_dmsgsPrint(model->GetModelName());
		//}
		//ModelIndex modelindex = library->GetModelIndex();
		//for (auto itr = modelindex.begin(); itr != modelindex.end(); ++itr)
		//{
		//	mdlDialog_dmsgsPrint((*itr).GetName());
		//}
	}
}

void DgnECManagerTest()
{
	DgnECManagerR ecManager = DgnECManager::GetManager();
	bvector<SchemaInfo> infos;
	DgnFilePtr activeDgnFile = ISessionMgr::GetActiveDgnFile();
	//ecManager.DiscoverSchemas(infos, *activeDgnFile, ECSCHEMAPERSISTENCE_Stored, DgnECHostType::File);
	//for (auto info : infos)
	//{
	//	ECN::ECSchemaPtr ecSchema = ecManager.LocateSchemaInDgnFile(info, ECN::SCHEMAMATCHTYPE_Exact, true);
	//	if (!ecSchema.IsNull())
	//	{
	//		//WString xmlSchema;
	//		//if (ECN::SchemaWriteStatus::SCHEMA_WRITE_STATUS_Success == ecSchema->WriteToXmlString(xmlSchema))
	//		//{
	//		//	wprintf(L"%s",xmlSchema);
	//		//}
	//		wprintf(L"SchemaName:%s\n", ecSchema->GetFullSchemaName());
	//		for (auto ecClass : ecSchema->GetClasses())
	//		{
	//			wprintf(L"|___ClassName:%s\n", ecClass->GetName());
	//			for (auto ecProperty : ecClass->GetProperties())
	//			{
	//				wprintf(L"    |___PropertyName:%s,PropertyType:%s\n", ecProperty->GetName(), ecProperty->GetTypeName());
	//			}
	//		}
	//	}
	//}
	auto findInstanceScopeOption = FindInstancesScopeOption(DgnECHostType::Element);
	auto findinstanceScope = FindInstancesScope::CreateScope(*activeDgnFile, findInstanceScopeOption);
	auto ecQuery = ECQuery::CreateQuery(ECQueryProcessFlags::ECQUERY_PROCESS_SearchAllClasses);
	auto ecInstances = ecManager.FindInstances(*findinstanceScope, *ecQuery);
	if (ecInstances.IsNull())
		return;
	size_t instancesNum = 0;
	for (auto ecInstance : ecInstances)
	{
		ECClassCR ecClass = ecInstance->GetClass();
		wprintf(L"Class Name:%s\n", ecClass.GetFullName());
		for (auto ecProperty : ecClass.GetProperties())
		{
			WString propertyName = ecProperty->GetName();
			ECValue ecValue;
			if (ECOBJECTS_STATUS_Success == ecInstance->GetValue(ecValue, propertyName.c_str()))
			{
				wprintf(L"		Property Name:%s---Value:%s\n", propertyName, ecValue.ToString());
			}
		}
		++instancesNum;
	}
	wprintf(L"The total instances number is %d", instancesNum);

}

void SolidUtilTest()
{
	DgnSphereDetail sphereDetail(DPoint3d::From(1000,1000,1000),1000);
	ISolidPrimitivePtr sphere = ISolidPrimitive::CreateDgnSphere(sphereDetail);
	ISolidKernelEntityPtr sphereKernelPtr = nullptr;
	if (BentleyStatus::SUCCESS == SolidUtil::Create::BodyFromSolidPrimitive(sphereKernelPtr, *sphere, *ACTIVEMODEL))
	{
		//SolidUtil::Debug::DumpEntity(*sphereKernelPtr, L"Sphere");
	}
}

void ElementTemplateTest()
{
	DgnFileP activeDgnFile = ISessionMgr::GetActiveDgnFile();
	//Create the element by path
	ElementTemplateNodePtr	elementTemplate = nullptr;
	if (ETSTATUS_Success != ElementTemplateUtils::CreateByPath(elementTemplate, LR"(Test\Default)", *activeDgnFile))
		return;
	IECInstancePtr etPropertyInstance = elementTemplate->GetOrCreateDefaultInstance();
	if (etPropertyInstance.IsNull())
		return;
	int lineWeight = 2;
	UInt32 elementColor = 5;
	ElementTemplateParamsHelper::AddLevelByName(*etPropertyInstance, L"Piping");
	ElementTemplateParamsHelper::AddLineStyleById(*etPropertyInstance, 0, *activeDgnFile);
	ElementTemplateParamsHelper::AddLineWeight(*etPropertyInstance, lineWeight);
	ElementTemplateParamsHelper::AddElementColor(*etPropertyInstance, elementColor, *activeDgnFile);
	ElementTemplateUtils::WriteTemplateNode(*elementTemplate);
	mdlDialog_openInfoBox(L"Done!");
}
