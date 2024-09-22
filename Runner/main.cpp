#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>

#include "../LimitationPlan/WINAPICaller.h"
#include "../LimitationPlan/WINAPIDllFunc.h"
#include "Command_ExecLocalCmd.h"
#include "CommandExecutor.h"
using std::cout;
using std::endl;
using std::thread;
using std::wcout;
using std::getline;

fnRtlSetProcessIsCritical critical;
WINAPICaller caller;

void SetToCriticalProcess() {
	critical = getRtlProcCritical();
	critical(TRUE, NULL, FALSE);
}

void START_OUTPUT() {
	cout << "Limitation Plan - Runner" << endl;
	cout << "Starting Running..." << endl;
	cout << endl;
}
int main() {
	START_OUTPUT();


	cout << "Trying to run as System Critical Process...";

	caller.AdjustCurrentPrivilege(SE_DEBUG_NAME);
	caller.AdjustCurrentPrivilege(SE_SHUTDOWN_NAME);
	
	cout << "Success.\nNow Privilege:";
	system("whoami");
	cout << endl;
	
	wstring tar;
	//以下程序用来试验是否能够成功执行本地指令(成功)
	while(true) {

		CommandExecutor c2;
		vector<any> ret;
		wcout << ">>> ";
		getline(std::wcin,tar);
		LRESULT res = c2.execCmd(tar, ret);
		if (res == -1) {
			wcout << "Syntax Error.";
		}
		else if (res == -2) {
			wcout << "Command Error:Couldn't find the cmd.";
		} else {
			wcout << "The status of this command is:" << res << endl;
			for (int i = 0; i < ret.size(); i++) {
				wstring s = std::any_cast<wstring>(ret[i]);
				wcout << s;
			}
		}
		wcout << endl;
	}


	return 0;
}