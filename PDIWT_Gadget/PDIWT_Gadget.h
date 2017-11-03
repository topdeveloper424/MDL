#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>
#include <DgnPlatform\DgnPlatformApi.h>
#include <Mstn\PSolid\mssolid.h>
#include <Mstn\PSolid\mssolid.fdf>

#include <DgnView\DgnElementSetTool.h>
#include <DgnView\DgnTool.h>
#include <DgnView\AccuDraw.h>
#include <DgnView\AccuSnap.h>
#include <Bentley\bstdset.h>

#include <list>
#include <set>
#include <fstream>
#include <cmath>
#include <algorithm>

#include <gcroot.h>
#include <vcclr.h>
#include <msclr\marshal.h>

#include "PDIWT_Gadgetcmd.h"
#include "PDIWT_Gadgetids.h"

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

#define Private
/************************************************************************/
/* Commnad Function														*/
/************************************************************************/
Private void ParallelArea(WCharCP);
Private void ShowLevelBox(WCharCP);
Private void CreateTable(WCharCP);
/************************************************************************/
/* Hook Function														*/
/************************************************************************/
void dgnLevel_optionBtnHook(DialogItemMessageP);

//#pragma comment(lib,"animcore.lib")
//#pragma comment(lib,"BaseGeoCoord.lib")
//#pragma comment(lib,"Bentley.GeoCoord.lib")
//#pragma comment(lib,"Bentley.imodelconnection.lib")
//#pragma comment(lib,"Bentley.imodelmessage.lib")
//#pragma comment(lib,"Bentley.lib")
//#pragma comment(lib,"Bentley.MicroStation.MaterialControl.lib")
//#pragma comment(lib,"Bentley.PrintDefinitions.lib")
//#pragma comment(lib,"Bentley.PrintFoundation.lib")
//#pragma comment(lib,"BentleyAllocator.lib")
//#pragma comment(lib,"BentleyGeom.lib")
//#pragma comment(lib,"BentleyGeomSerialization.lib")
//#pragma comment(lib,"BeXml.lib")
//#pragma comment(lib,"Constraint2dCore.lib")
//#pragma comment(lib,"Constraint2dElement.lib")
//#pragma comment(lib,"dbpwise.lib")
//#pragma comment(lib,"DgnGeoCoord.lib")
//#pragma comment(lib,"DgnPlatform.lib")
//#pragma comment(lib,"DgnView.lib")
//#pragma comment(lib,"ECObjects.lib")
//#pragma comment(lib,"ImageLib.lib")
//#pragma comment(lib,"InsolationLib.lib")
//#pragma comment(lib,"mdlbltin.lib")
//#pragma comment(lib,"mdlxmltools.lib")
//#pragma comment(lib,"mspsolid.lib")
//#pragma comment(lib,"mstntoolsubs.lib")
//#pragma comment(lib,"nativewindow.lib")
//#pragma comment(lib,"nativewinmfc.lib")
//#pragma comment(lib,"PointCloud.lib")
//#pragma comment(lib,"PSolidAcisInterop.lib")
//#pragma comment(lib,"PSolidCore.lib")
//#pragma comment(lib,"Publish.lib")
//#pragma comment(lib,"RasterCore.lib")
//#pragma comment(lib,"rasterlib.lib")
//#pragma comment(lib,"RmgrTools.lib")
//#pragma comment(lib,"SmartFeature.lib")
//#pragma comment(lib,"splindlm.lib")
//#pragma comment(lib,"TerrainModelCore.lib")
//#pragma comment(lib,"TerrainModelElementHandler.lib")
//#pragma comment(lib,"videolib.lib")
//#pragma comment(lib,"VisEdgesLib.lib")