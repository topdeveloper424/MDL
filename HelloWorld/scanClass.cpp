#include "scanClass.h"

scanClass::scanClass()
{
	_scp = mdlScanCriteria_create();
}

scanClass::~scanClass()
{
	if (_scp) mdlScanCriteria_free(_scp);
}

ScanCriteriaP scanClass::getScp() const
{
	return _scp;
}

int scanClass::ref_callback(ElementRefP eleRefP, CallbackArgP args, ScanCriteriaP scp)
{
	ElementAgendaP agdP = reinterpret_cast<ElementAgendaP>(args); 
	agdP->Insert(eleRefP, mdlScanCriteria_getModel(scp));
	return FALSE;
}

void scanClass::DoScan(ElementAgendaR adgR)
{
	mdlScanCriteria_setReturnType(_scp, MSSCANCRIT_ITERATE_ELMREF, FALSE, FALSE);
	mdlScanCriteria_setElemRefCallback(_scp, ref_callback, &adgR);
	mdlScanCriteria_scan(_scp, NULL, NULL, NULL);
}

ElementAgenda scanClass::DoScan()
{
	ElementAgenda agd;
	DoScan(agd);
	return agd;
}

void scanClass::SetType(UShort typeMask[6])
{
	mdlScanCriteria_setElementTypeTest(_scp, typeMask, sizeof(typeMask));
}





