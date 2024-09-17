#include <iostream>
#include <Windows.h>

#include "WINAPIDllFunc.h"
#include "WINAPICaller.h"
using std::cout;
using std::endl;

fnRtlSetProcessIsCritical critical;
WINAPICaller caller;

void SetToCriticalProcess() {
	critical = getRtlProcCritical();
	critical(TRUE, NULL, FALSE);
}

void START_OUTPUT() {
	cout << "Limitation Plan - Runner" << endl;
	cout << "Starting Running..." << endl;
}
int main() {
	cout << "Trying to run as System Critical Process...";
	caller.AdjustCurrentPrivilege();
	SetToCriticalProcess();
	cout << "Success.\nNow Privilege:";
	system("whoami");
	cout << "Please not close window..." << endl;
	Sleep(100000000);
}