#pragma once
#include <Mstn\MstnDefs.h>		//需要包含mstndefs.h
#include <Mstn\MstnPlatformAPI.h>

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

class scanClass
{
public:
	scanClass();
	~scanClass();
	ScanCriteriaP getScp() const; //const 成员函数，不能修改类型的中的私有变量
	static int ref_callback(ElementRefP, CallbackArgP, ScanCriteriaP);
	void DoScan(ElementAgendaR);
	ElementAgenda DoScan();
	void SetType(UShort[6]);
private:
	ScanCriteriaP _scp;
};