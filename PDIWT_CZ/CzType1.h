#pragma once
#include <Mstn\MstnDefs.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>
#include <DgnPlatform\DgnPlatformApi.h>
#include <Mstn\PSolid\mssolid.h>
#include <Mstn\PSolid\mssolid.fdf>

#include <boost/timer.hpp>

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

struct BDunInfo
{
	double para1;
	double para2;
	double para3;
	double para4;
	double para5;
};

class CzType1
{
public:
	CzType1();
	~CzType1();
	StatusInt CreateBDun();
	StatusInt CreateDB();
	StatusInt CreateMK();
	StatusInt CreateSSLD();
	StatusInt CreateXNG();
private:
	BDunInfo bduninfo;
	double UPM;
};


