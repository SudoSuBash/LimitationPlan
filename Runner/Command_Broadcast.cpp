#include "Command_Broadcast.h"
#include "BroadCastShowWindow.h"

#include <thread>
#include <iostream>
#include "glob.h"

using std::wcout;
using std::thread;

thread recvmsg;

void WindowEvent() {
	HINSTANCE instance = GetModuleHandle(NULL);
	BgetRegisteredClass(instance);
	BcreateWindow(instance);
	MSG msg;
	HWND hwnd = FindWindow(L"BroadCastWin", L"Broadcast");
	SetForegroundWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		Sleep(100);
	}
}

Command_Broadcast::Command_Broadcast() : BaseCommand(TEXT("broadcast"), 1, { TEXT("br"),TEXT("broadcast") }) {

}

LRESULT Command_Broadcast::ExecCmd(vector<wstring> args, vector<any>& ret) {
	if (args.size() != 1) {
		ret.push_back(wstring(L"Usage:br|broadcast <text>"));
		return 1001;
	}
	target = new wstring(args[0]);
	HWND hwnd = FindWindow(L"BroadCastWin",L"Broadcast");
	if (hwnd != NULL) {
		ret.push_back(wstring(L"E:Already opened a Broadcast Window."));
		return 1002;
	}

	recvmsg = thread(WindowEvent);
	recvmsg.detach();

	return 0;
}
