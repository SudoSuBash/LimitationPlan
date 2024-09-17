#pragma once
#include <Windows.h>
#include <string>
class WINAPICaller
{
public:
	WINAPICaller();

	BOOL AdjustCurrentPrivilege();
	DWORD getProcessSessionId(std::wstring procs);

	HRESULT DuplicateProcessToken(DWORD pid, HANDLE* hd);
	HRESULT WCreateProcessWithToken(HANDLE parent,std::wstring proc);

	HRESULT WCopyFile(
		std::wstring Old,
		std::wstring New,
		BOOL FailIfExists
	);


};	