#pragma once

#include<Windows.h>
#include<string>

class RegManage {
private:
	HKEY root;
	std::wstring path;
	HKEY open_hkey;
	BOOL opened;
public:
	RegManage(HKEY root, std::wstring path);
	
	HRESULT setQword(std::wstring key, DWORD64 value);
	HRESULT setDword(std::wstring key, DWORD32 value);
	HRESULT setString(std::wstring key, std::wstring value);

	HRESULT deleteKey(std::wstring key);

	LRESULT getQword(std::wstring key,DWORD64* value);
	LRESULT getDword(std::wstring key, DWORD32* value);
	LRESULT getString(std::wstring key,std::wstring* val);

	BOOL valid();
};