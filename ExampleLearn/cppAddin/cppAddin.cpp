// 这是主 DLL 文件。

#include "stdafx.h"
#include "cppAddin.h"
#include <vcclr.h>

using namespace PDIWTCodeQueryLib;

using namespace System::Collections::Generic;

namespace BD = Bentley::DgnPlatformNET;
namespace BG = Bentley::GeometryNET;
namespace BECN = Bentley::ECN;
namespace BECO = Bentley::ECObjects;
namespace BECOS = Bentley::ECObjects::Schema;
namespace BECOI = Bentley::ECObjects::Instance;
namespace BECOX = Bentley::ECObjects::XML;
namespace BECXA = Bentley::ECXAttributes;


typedef std::vector<int> IntArray;

/************************************************************************/
/* Element Finder 扫描文件，寻找相应的元素								*/
/************************************************************************/

class ElementFinder
{
private:
	DgnModelRefR	m_modelRef;
	bool			m_onlyVisible;
	std::vector<MSElementTypes> m_elementTypes;
public:
	ElementFinder(DgnModelRefR modleRef, bool onlyVisible = true) :m_modelRef(modleRef), m_onlyVisible(onlyVisible) {};

	void AddElementType(MSElementTypes elemType);
	void GetElements(ElementAgendaP foundElements);
};

void ElementFinder::AddElementType(MSElementTypes elemType)
{
	m_elementTypes.push_back(elemType);
}

void ElementFinder::GetElements(ElementAgendaP foundElements)
{
	ScanCriteriaP scp = ScanCriteria::Create();
	for each (auto elementType in m_elementTypes)
		scp->AddSingleElementTypeTest(elementType);
	scp->SetModelRef(&m_modelRef);
	scp->SetDrawnElements();
	if (m_onlyVisible)
		scp->SetPropertiesTest(0, ELEINVISIBLE);
	scp->SetElemRefCallback
	(
		[](ElementRefP elemRef, CallbackArgP argP, ScanCriteriaP scp)->StatusInt
	{
		if (elemRef == nullptr || scp == nullptr)
			return SUCCESS;
		ElementAgendaP agd = static_cast<ElementAgendaP>(argP);
		if (nullptr == agd)
			return SUCCESS;
		agd->Insert(elemRef, scp->GetModelRef());
		return SUCCESS;
	},
		foundElements
		);
	ScanCriteria::Delete(scp);
}

/************************************************************************/
/* Global Functions														*/
/************************************************************************/
//std::string getNativeString(String^ value)
//{
//	return msclr::interop::marshal_as<std::string>(value);
//}

ref class LayerInfoAttributteFilter : public BECOX::IECDeserializationFilter
{
public:
	virtual bool AcceptableSchema(BECOS::IECSchema^ ecSchema)
	{
		if ("AglosGeo" == ecSchema->Name)
			return true;
		return false;
	}
	virtual bool AcceptableClass(BECOS::IECSchema^ schema, String^ className)
	{
		if ("AglosGeo" == className)
			return true;
		return false;
	}
	virtual bool AcceptableProperty(BECOI::IECNamedValueContainer^ container, String^ propertyName)
	{
		return true;
	}
};

void getLayerInfo(LayerInfo^% layerInfo, BECOI::IECInstance^ instance)
{
	if (nullptr == instance)
		return;
	
	Type^ layerinfoType = layerInfo->GetType();
	auto props = layerinfoType->GetProperties();
	for each (auto propinfo in props)
	{
		if (propinfo->Name == "LayerNum")
			continue;
		propinfo->SetValue(layerInfo, instance[propinfo->Name]->DoubleValue);
	}
}

bool traversalLayerInfoDelegate(BECOI::IECInstance^ ecInstance, IntPtr XAttributeIterAsIntPtr, Object^ userObj)
{
	BECOI::ECInstanceList^ instanceList = dynamic_cast<BECOI::ECInstanceList^>(userObj);
	instanceList->Add(ecInstance);
	return false;
}

StatusInt getLayerInfoAttributtes(LayerInfo^% layerInfo, ElementHandleCR eh)
{
	if (BSPLINE_SURFACE_ELM != const_cast<ElementHandleR>(eh).GetElementType())
		return ERROR;

	BECOX::IECDeserializationFilter^ filter = gcnew LayerInfoAttributteFilter();

	BECOI::ECInstanceList^ instanceList = gcnew BECOI::ECInstanceList();
	BECXA::ECXAttributes::Traverse(gcnew BECXA::ECXAttributes::TraverseDelegate(&traversalLayerInfoDelegate),
		eh,
		XAttributeHandle::INVALID_XATTR_ID,
		filter, instanceList);

	StatusInt status = ERROR;
	for each (BECOI::IECInstance^ instance in instanceList)
	{
		if (instance->ClassDefinition->Name == "AglosGeo")
		{
			getLayerInfo(layerInfo, instance);
			status = SUCCESS;
		}
	}
	return status;
}

/************************************************************************/
/* Main Class implementation											*/
/************************************************************************/

PDIWTCodeQueryErrorCode PDIWTCodeQueryLib::PDIWTQuery::QueryById(AllLayerInfo % result, long id)
{
	result.IntersectLayers = nullptr;

	ElementAgenda bssurfaceagd;
	ElementFinder bssurfaceFinder(*ACTIVEMODEL, true);
	bssurfaceFinder.AddElementType(BSPLINE_SURFACE_ELM);
	bssurfaceFinder.GetElements(&bssurfaceagd);
	size_t bssurfaceSize = bssurfaceagd.size();
	if (bssurfaceSize <= 0)
		return PDIWTCodeQueryErrorCode::NotFoundLayer;
	return PDIWTCodeQueryErrorCode();
}

BD::StatusInt PDIWTCodeQueryLib::CellFunction::AttachLibrary()
{
	BeFileName outcelllibName;
	pin_ptr<const wchar_t> pCelllibPath = PtrToStringChars(cellLibPath);
	mdlCell_attachLibrary(outcelllibName, &BeFileName(pCelllibPath), nullptr, TRUE);
	return BD::StatusInt::Success;
}

BD::StatusInt PDIWTCodeQueryLib::CellFunction::PutCell(String ^ cellName)
{
	return BD::StatusInt::Success;
}
