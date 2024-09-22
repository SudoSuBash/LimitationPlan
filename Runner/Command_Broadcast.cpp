#include "Command_Broadcast.h"
#include "BroadCastShowWindow.h"

#include <thread>
#include <iostream>

using std::wcout;
using std::thread;

thread recvmsg;

void WindowEvent() {
	HINSTANCE instance = GetModuleHandle(NULL);
	BgetRegisteredClass(instance);
	BcreateWindow(instance);
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		Sleep(100);
	}
}

Command_Broadcast::Command_Broadcast() : BaseCommand(TEXT("broadcast"), 1, { TEXT("br"),TEXT("broadcast") }) {

}

LRESULT Command_Broadcast::ExecCmd(vector<wstring> args, vector<any>& ret) {
	HWND hwnd = FindWindow(L"BroadCastWin",L"Broadcast");
	if (hwnd != NULL) {
		ret.push_back(wstring(L"E:Already opened a Broadcast Window."));
		return 1001;
	}

	recvmsg = thread(WindowEvent);
	recvmsg.detach();
	return 0;
}
