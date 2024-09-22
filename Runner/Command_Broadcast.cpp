#include "Command_Broadcast.h"
#include "BroadCastShowWindow.h"

#include <thread>
#include <iostream>

using std::wcout;
using std::thread;

thread recvmsg;
void ProcMsg(MSG& msg) {


}

Command_Broadcast::Command_Broadcast() : BaseCommand(TEXT("broadcast"), 1, { TEXT("br"),TEXT("broadcast") }) {

}

LRESULT Command_Broadcast::ExecCmd(vector<wstring> args, vector<any>& ret) {
	HINSTANCE instance = GetModuleHandle(NULL);
	BgetRegisteredClass(instance);

	if (!BcreateWindow(instance)) {
		ret.push_back(wstring(TEXT("E:Could not create window.")));

		return 1001;
	}
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//BWTarget = TEXT("00");
	//recvmsg = thread(ProcMsg,msg);
	//recvmsg.join();
	return msg.wParam;
}

