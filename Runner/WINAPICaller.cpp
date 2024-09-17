#include "WINAPICaller.h"
#include <tlhelp32.h>
#include <Windows.h>

#include <iostream>
#include <UserEnv.h>
#pragma comment(lib,"UserEnv.lib")

using std::wcout;
using std::cout;
using std::wstring;

WINAPICaller::WINAPICaller() {

}

DWORD WINAPICaller::getProcessSessionId(std::wstring name) {
	DWORD currentSessionId = WTSGetActiveConsoleSessionId();
	PROCESSENTRY32 entry{};
	HANDLE hd = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hd == INVALID_HANDLE_VALUE) return -1;
	entry.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hd, &entry)) return -1;
	do {
		wstring sr = wstring(entry.szExeFile);
		
		if (sr == name) {
			DWORD sessid = 0;
			BOOL res = ProcessIdToSessionId(entry.th32ProcessID, &sessid);
			if (ProcessIdToSessionId(entry.th32ProcessID, &sessid) && sessid == currentSessionId) {
				return entry.th32ProcessID;
			}
			
		}
	} while (Process32Next(hd, &entry));
	CloseHandle(hd);
	return -1;
}

HRESULT WINAPICaller::DuplicateProcessToken(DWORD pid,HANDLE* hd) {
	DWORD currentSessionId = WTSGetActiveConsoleSessionId();

	HANDLE hprocess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);

	if (hprocess == NULL) return GetLastError();
	HANDLE hptoken,hduptoken;
	BOOL openResult = ::OpenProcessToken(hprocess,
		TOKEN_DUPLICATE, &hptoken);
	if (hptoken == INVALID_HANDLE_VALUE) return GetLastError();
	//cout << "LE=" << GetLastError() << std::endl;

	BOOL dupResult = DuplicateTokenEx(hptoken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hduptoken);
	//cout << "LE2=" << GetLastError() << std::endl;

	//BOOL setResult = SetTokenInformation(hptoken, TokenSessionId, (LPVOID)&currentSessionId, sizeof(DWORD));
	//cout << "LE3=" << GetLastError() << std::endl;
	*hd = hduptoken;
	
	CloseHandle(hprocess);
	return ERROR_SUCCESS;
}

HRESULT WINAPICaller::WCreateProcessWithToken(HANDLE parent, std::wstring proc) {

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.lpDesktop = (LPWSTR)L"winsta0\\default";

	LPVOID envBlock;

	CreateEnvironmentBlock(&envBlock, parent, FALSE);

	DWORD flg = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	BOOL br = CreateProcessWithTokenW(
		parent,
		LOGON_NETCREDENTIALS_ONLY,
		NULL,
		(LPWSTR)proc.c_str(),
		NORMAL_PRIORITY_CLASS,
		NULL,
		NULL,
		&si,
		&pi
	);

	return br;
}
BOOL WINAPICaller::AdjustCurrentPrivilege() {

	HANDLE hToken;
	BOOL fOk = FALSE;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)) {
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);

		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);

		fOk = (GetLastError() == ERROR_SUCCESS);
		CloseHandle(hToken);
	}
	return fOk;
}