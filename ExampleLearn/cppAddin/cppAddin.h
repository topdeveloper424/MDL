// cppAddin.h

#pragma once

using namespace System;
using namespace System::Collections::Generic;
namespace BD = Bentley::DgnPlatformNET;
namespace BG = Bentley::GeometryNET;

namespace PDIWTCodeQueryLib
{
	public ref class LayerInfo
	{
	public:
		property String^ LayerNum;
		property double Qfi;
		property double Qri;
		property double Betasi;
		property double Xifi;
		property double Xifi2;
		property double Xii;
		property double PsiSi;

		virtual String^ ToString() override
		{
			return String::Format("Layer Info of {8}:{0}Qfi={1}{0}" +
				"Qri={2}{0}Betasi={3}{0}Xifi={4}{0}Xifi2={5}{0}Xii={6}{0}PsiSi={7}{0}",
				Environment::NewLine,
				Qfi, Qri, Betasi, Xifi, Xifi2, Xii, PsiSi,LayerNum);
		}
	};

	public ref class ColumnLayerInfo
	{
	public:
		property BG::DPoint3d TopPoint;
		property BG::DPoint3d BottomPoint;
		property LayerInfo^ Info;

		void SetTopPoint(DPoint3dCR point)
		{
			TopPoint.Set(point.x, point.y, point.z);
		}

		void SetBottomPoint(DPoint3dCR point)
		{
			TopPoint.Set(point.x, point.y, point.z);
		}

		virtual String^ ToString() override
		{
			Text::StringBuilder^ sb = gcnew Text::StringBuilder();
			sb->Append("Intersect Layer Info:\r\n");
			sb->Append(Info->ToString());
			sb->Append("Intersect TopPoint:\r\n");
			sb->Append(TopPoint.ToString());
			sb->Append("Intersect BottomPoint:\r\n");
			sb->Append(BottomPoint.ToString());
			return sb->ToString();
		}
	};

	public ref class AllLayerInfo
	{
	public :
		property List<LayerInfo^>^ IntersectLayers;
		virtual String^ ToString() override
		{
			auto sb = gcnew Text::StringBuilder();
			sb->Append("\r\n");
			sb->Append(String::Format("Total Number of Intersection Layer is {0}\r\n", IntersectLayers->Count));
			for each (auto layerinfo in IntersectLayers)
			{
				sb->Append(layerinfo->ToString());
			}
			return sb->ToString();
		}
	};

	public enum class PDIWTCodeQueryErrorCode
	{
		Success,
		NotFoundColumn,
		NotFoundLayer,
		NoIntersection,
		UnkonwnError
	};

	public ref class PDIWTQuery
	{
	public:
		PDIWTCodeQueryErrorCode QueryById(AllLayerInfo% result, long id);
	};
}