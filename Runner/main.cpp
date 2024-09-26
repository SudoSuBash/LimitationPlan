#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>
#include <locale>

#include "../LimitationPlan/WINAPICaller.h"
#include "../LimitationPlan/WINAPIDllFunc.h"
#include "Command_ExecLocalCmd.h"
#include "CommandExecutor.h"
#include "glob.h"

using std::locale;
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
	//SetToCriticalProcess();
	
	cout << "Success.\nNow Privilege:";
	system("whoami");
	cout << endl;
	
	wstring tar;
	//���³������������Ƿ��ܹ��ɹ�ִ�б���ָ��(�ɹ�)
	while(true) {

		CommandExecutor c2;
		vector<any> ret;
		wcout << ">>> ";
		std::wcin.imbue(locale("chs"));
		getline(std::wcin,tar);
		LRESULT res = c2.execCmd(tar, ret);
		if (res == -1) {
			wcout << "Syntax Error.";
		}
		else if (res == -2) {
			wcout << "Command Error:Couldn't find the cmd.";
		}
		else if (res == -3) {
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