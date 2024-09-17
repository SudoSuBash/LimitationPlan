#include "WINAPIDllFunc.h"

fnRtlSetProcessIsCritical getRtlProcCritical() {
	fnRtlSetProcessIsCritical FN;
	HMODULE hNtDll = GetModuleHandleA("ntdll.dll");
	if (!hNtDll) return NULL;
	FN = (fnRtlSetProcessIsCritical)GetProcAddress(hNtDll, "RtlSetProcessIsCritical");
	return FN;
}