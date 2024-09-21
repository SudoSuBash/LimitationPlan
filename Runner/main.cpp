#include <iostream>
#include <Windows.h>
#include <thread>

#include "../LimitationPlan/WINAPICaller.h"
#include "../LimitationPlan/WINAPIDllFunc.h"
#include "Command_ExecLocalCmd.h"
using std::cout;
using std::endl;
using std::thread;
using std::wcout;

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

	caller.AdjustCurrentPrivilege(SE_DEBUG_NAME);
	caller.AdjustCurrentPrivilege(SE_SHUTDOWN_NAME);

	cout << caller.WJudgePermission() << endl;
	
	SetToCriticalProcess();
	cout << "Success.\nNow Privilege:";
	system("whoami");
	cout << endl;

	cout << "Please not close window..." << endl;
	
	//以下程序用来试验是否能够成功执行本地指令(成功)
	//Command_ExecLocalCmd c;
	//LRESULT r = c.ExecCmd({ TEXT("dir E:\\") });
	//wcout << c.getOutput() << endl;

	system("pause");



	return 0;
}