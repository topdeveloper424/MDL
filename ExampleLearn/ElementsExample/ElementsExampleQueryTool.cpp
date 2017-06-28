#include "ElementsExample.h"

enum ElementsExampleQueryOpitons
{
	ElementsExampleQuery_Display,
	ElementsExampleQuery_Geometry,
	ElementsExampleQuery_Fill
};

/************************************************************************/
/* Helper class to query different elements for different propertites;	*/
/************************************************************************/
class ElementsQueryHelper
{
private:
	static const WString format2;
public:
	static WString QueryShapeElement(ElementHandleCR eh, WCharCP type);
	static WString QueryMultilineElement(ElementHandleCR eh, WCharCP type);
	static WString QueryElementDisplay(ElementHandleCR eh);
	static WString QueryElementGeometry(ElementHandleCR eh);
	static WString QueryElementFill(ElementHandleCR eh);

	static WString QueryElement(ElementHandleCR eh, ElementsExampleQueryOpitons queryOption);
};

const WString ElementsQueryHelper::format2 = L"Point[%ld] :(%ld, %ld, %ld)\n";

WString ElementsQueryHelper::QueryShapeElement(ElementHandleCR eh, WCharCP type)
{
	WString messageInfo = L"";
	WString format1 = WString(type) + L"\nPoints Count: %ld\nLength/Perimeter:%lf\n";

	CurveVectorPtr pathCurve = ICurvePathQuery::ElementToCurveVector(eh);

	if (pathCurve.IsValid())
	{
		ICurvePrimitivePtr& pathMember = pathCurve->front();
		if (pathCurve->HasSingleCurvePrimitive() == ICurvePrimitive::CURVE_PRIMITIVE_TYPE_LineString)
		{
			bvector<DPoint3d> points = *(pathMember->GetLineStringCP());
			
			double length;
			pathMember->Length(length);
			WString::Sprintf(messageInfo, format1.c_str(), points.size(), length);

			int i = 0;
			for each (DPoint3d point in points)
			{
				WString pointStr;
				pointStr.Sprintf(format2.c_str(), i, point.x, point.y, point.z);
				i++;
				messageInfo += pointStr;
			}
		}
	}

	return messageInfo;
}

BENTLEY_NAMESPACE_NAME::WString ElementsQueryHelper::QueryMultilineElement(ElementHandleCR eh, WCharCP type)
{
	WString messageInfo = L"";
	WString format1 = WString(type) + L"\nPoints Count: %ld\n";

	Handler& elmHandler = eh.GetHandler();

	//MultilineHandler* mLineObj = dynamic_cast<MultilineHandler*>(&elmHandler);
	MultilineHandler *mLineObj = dynamic_cast<MultilineHandler *>(&elmHandler);
	if (nullptr != mLineObj)
	{
		UInt32 pointnum = mLineObj->GetPointCount(eh);
		messageInfo.Sprintf(format1.c_str(), pointnum);

		for (UInt32 i =0; i < pointnum; i++)
		{
			MultilinePointPtr mPoint = mLineObj->GetPoint(eh, i);
			DPoint3d point = mPoint->GetPoint();

			WPrintfString pointStr(format2.c_str(), i, point.x, point.y, point.z);

			messageInfo += pointStr;
		}
	}
	return messageInfo;
}

BENTLEY_NAMESPACE_NAME::WString ElementsQueryHelper::QueryElementDisplay(ElementHandleCR eh)
{
	WString format = L"Elemtns\'s Basic Properties\nColor : %ld\nWeigth : %ld\nLineStyle : %ld\n";
	ElementPropertiesGetterPtr propGetter = ElementPropertiesGetter::Create(eh);

	WString messageInfo = L"";
	if (propGetter.IsValid())
	{
		UInt32 color = propGetter->GetColor();
		UInt32 weight = propGetter->GetWeight();
		UInt32 linestyle = propGetter->GetLineStyle();
		messageInfo.Sprintf(format.c_str(), color, weight, linestyle);
	}
	else
		messageInfo = L"Cannot retrieve element basic Properties.";
	return messageInfo;
}

BENTLEY_NAMESPACE_NAME::WString ElementsQueryHelper::QueryElementGeometry(ElementHandleCR eh)
{
	Handler& h = eh.GetHandler();
	WString type;
	h.GetTypeName(type, 256);

	if (&ShapeHandler::GetInstance() == &eh.GetHandler())
		return QueryShapeElement(eh, type.c_str());
	else if (&MultilineHandler::GetInstance() == &eh.GetHandler())
		return QueryMultilineElement(eh, type.c_str());
	
	WString errormessage = L"Element is not supported by this Query Example. This Query Example only supports shape and Multiline elements.";

	return errormessage;
}

BENTLEY_NAMESPACE_NAME::WString ElementsQueryHelper::QueryElementFill(ElementHandleCR eh)
{
	WString messageInfo = L"";

	IAreaFillPropertiesQuery* fillQueryP = dynamic_cast<IAreaFillPropertiesQuery*>(&eh.GetHandler());
	if (nullptr == fillQueryP)
	{
		messageInfo = L"Cannot retrieve Fill Properties. Possible Reason: The element does not support fill.";
		return messageInfo;
	}

	WString format = L"Element\'s Fill Properties\nArea Type(Solid/Hole) : %ls\n";

	bool isHole;
	if (fillQueryP->GetAreaType(eh, &isHole))
		messageInfo.Sprintf(format.c_str(), isHole ? L"Hole" : L"Solid");

	WString fillStr = L"";
	UInt32 fillColor;
	bool alwaysFilled;
	GradientSymbPtr gradient;
	PatternParamsPtr params;

	if (fillQueryP->GetSolidFill(eh,&fillColor,&alwaysFilled))
	{
		WString format1 = L"Element has Solid Fill. \nFill color: %ld.\nAlways Filled: %ld\n";
		fillStr.Sprintf(format1.c_str(), fillColor, alwaysFilled);
		messageInfo += fillStr;
	}
	else if (fillQueryP->GetGradientFill(eh,gradient))
	{
		UInt16 flags = gradient->GetFlags();
		double angle = gradient->GetAngle();
		double tint = gradient->GetTint();
		double shift = gradient->GetShift();

		WString format1 = L"Element has  Gradient Fill. \nFlags : %ld.\nAngle : %lf\nTint : %lf\nShift : %lf\n";
		fillStr.Sprintf(format1.c_str(), flags, angle, tint, shift);
		messageInfo += fillStr;

		for (int i = 0; i < gradient->GetNKeys(); i++)
		{
			RgbColorDef color;
			double pvalue;
			gradient->GetKey(color, pvalue, i);
			WString fillStr2 = L"";
			WString format3 = L"Gradient Info.\n Fraction : %lf.\nColor (RGB) : (%ld, %ld, %ld)\n";
			fillStr2.Sprintf(format3.c_str(), pvalue, color.red, color.green, color.blue);
			messageInfo += fillStr2;
		}
	}else if (fillQueryP->GetPattern(eh,params,nullptr,nullptr,0))
	{
		WString format3 = L"Element has Pattern Fill.\nPrimary Angle: %lf.\nPrimary Spacing: %lf\nSecondery Angle: %lf\nSecondery Spacing: %lf\nColor : %ld\nWeight : %ld\nStyle : %ld\n";
		fillStr.Sprintf(format3.c_str(),
			params->GetPrimaryAngle(),
			params->GetPrimarySpacing(),
			params->GetSecondaryAngle(),
			params->GetSecondarySpacing(),
			params->GetColor(),
			params->GetWeight(),
			params->GetStyle());

		messageInfo += fillStr;
	}
	return messageInfo;
}

BENTLEY_NAMESPACE_NAME::WString ElementsQueryHelper::QueryElement(ElementHandleCR eh, ElementsExampleQueryOpitons queryOption)
{
	if (queryOption == ElementsExampleQuery_Display)
		return QueryElementDisplay(eh);
	else if (queryOption == ElementsExampleQuery_Fill)
		return QueryElementFill(eh);
	else
		return QueryElementGeometry(eh);
}

/************************************************************************/
/* Element set Tool														*/
/************************************************************************/
struct ElementsExampleQueryTool : DgnElementSetTool
{
private:
	ElementsExampleQueryOpitons m_queryOption;

	ElementsExampleQueryTool(int toolName,ElementsExampleQueryOpitons queryOption): DgnElementSetTool(toolName),m_queryOption(queryOption){}

	void  _OnPostInstall() override;
	void _OnRestartTool() override;
	bool _OnDataButton(DgnButtonEventCR ev) override;

public:	
	int _OnElementModify(EditElementHandleR el)override;
	static void InstallNewInstance(int toolId, ElementsExampleQueryOpitons queryoption);
};

void ElementsExampleQueryTool::_OnPostInstall()
{
	_SetLocateCursor(true);

	__super::_OnPostInstall();
}

void ElementsExampleQueryTool::_OnRestartTool()
{
	InstallNewInstance(GetToolId(), m_queryOption);
}

bool ElementsExampleQueryTool::_OnDataButton(DgnButtonEventCR ev)
{
	HitPathCP hitPath = _DoLocate(ev, true, BENTLEY_NAMESPACE_NAME::DgnPlatform::ComponentMode::Innermost);

	if (nullptr != hitPath)
	{
		ElementRefP elemRef = hitPath->GetHeadElem();
		ElementHandle elem(elemRef);

		WString messageInfo = ElementsQueryHelper::QueryElement(elem, m_queryOption);
		mdlDialog_openInfoBox(messageInfo.c_str());
	}
	return true;
}

int ElementsExampleQueryTool::_OnElementModify(EditElementHandleR el)
{
	return ERROR;
}

void ElementsExampleQueryTool::InstallNewInstance(int toolId, ElementsExampleQueryOpitons queryoption)
{
	ElementsExampleQueryTool* tool = new ElementsExampleQueryTool(toolId, queryoption);
	tool->InstallTool();
}

/************************************************************************/
/*  Associate the keyin with the function								*/
/************************************************************************/

Public void elementsExampleQueryElementDisplay(WCharCP unparsed)
{
	ElementsExampleQueryTool::InstallNewInstance(CMDNAME_ElementsExampleQueryElementDisplay, ElementsExampleQuery_Display);
}

Public void elementsExampleQueryElementGeometry(WCharCP unparsed)
{
	ElementsExampleQueryTool::InstallNewInstance(CMDNAME_ElementsExampleQueryElementGeometry, ElementsExampleQuery_Geometry);
}

Public void elementsExampleQueryElementFill(WCharCP unparsed)
{
	ElementsExampleQueryTool::InstallNewInstance(CMDNAME_ElementsExampleQueryElementFill, ElementsExampleQuery_Fill);
}