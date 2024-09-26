#include "Command_CloseBroadCast.h"
Command_CloseBc::Command_CloseBc() : BaseCommand(TEXT("CloseBroadCast"), 1, { TEXT("ub"),TEXT("cbr") }) {

}

LRESULT Command_CloseBc::ExecCmd(vector<wstring> args, vector<any>& ret) {
	if (args.size() != 0) {
		ret.push_back(wstring(L"Usage:ub|cbr"));
		return 1001;
	}
	HWND hwnd = FindWindow(L"BroadCastWin", L"Broadcast");
	if (hwnd == NULL) {
		ret.push_back(wstring(L"E:Broadcast Window does not exist."));
		return 1002;
	}
	SendMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
	return 0;
}