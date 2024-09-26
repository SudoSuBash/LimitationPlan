#pragma once
#include <Windows.h>
#include <string>
class WINAPICaller
{
public:
	WINAPICaller();

	BOOL AdjustCurrentPrivilege(std::wstring name);
	DWORD getProcessSessionId(std::wstring procs);

	HRESULT DuplicateProcessToken(DWORD pid, HANDLE* hd);
	HRESULT WCreateProcessWithToken(HANDLE parent,std::wstring proc);

	BOOL WCopyFile(
		std::wstring Old,
		std::wstring New,
		BOOL FailIfExists
	);

	HRESULT WJudgePermission();

	HRESULT WGetModuleFileName(std::wstring* name);

	HRESULT captureScreen();
};	