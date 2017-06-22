#pragma once
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MstnPlatformAPI.h>
#include <Mstn\MstnDefs.h>
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
};


