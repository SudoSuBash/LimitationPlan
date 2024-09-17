#include "RegManage.h"
#include <iostream>

using std::string;

RegManage::RegManage(HKEY root, std::wstring path) {
	this->root = root;
	this->path = path;

	LRESULT resr = RegCreateKeyEx(
		this->root,
		this->path.c_str(),
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS |
#ifndef _WIN64
		KEY_WOW64_32KEY,
#else
		KEY_WOW64_64KEY,
#endif
		NULL,
		&this->open_hkey,
		NULL
	);
	this->opened = resr == ERROR_SUCCESS;
}

HRESULT RegManage::setQword(std::wstring key, DWORD64 value) {
	if (!this->opened) return E_FAIL;

	LSTATUS c = RegSetValueEx(
		this->open_hkey,
		key.c_str(),
		0,
		REG_QWORD,
		(LPBYTE)&value,
		sizeof(DWORD64)
	);
	if (c != ERROR_SUCCESS) return c;
	return 0;
}

HRESULT RegManage::setString(std::wstring key,std::wstring value) {
	if (!this->opened) return E_FAIL;

	const WCHAR* target = value.c_str();
	LSTATUS c = RegSetValueEx(
		this->open_hkey,
		key.c_str(),
		0,
		REG_SZ,
		(LPBYTE)target,
		sizeof(target)
	);
	if (c != ERROR_SUCCESS) return c;
	return 0;
}

HRESULT RegManage::deleteKey(std::wstring key) {
	if (!this->opened) return E_FAIL;
	HRESULT res = RegDeleteValue(
		this->open_hkey,
		key.c_str()
	);
	return res;
}

HRESULT RegManage::setDword(std::wstring key, DWORD32 value) {
	if (!this->opened) return E_FAIL;

	LSTATUS c = RegSetValueEx(
		this->open_hkey,
		key.c_str(),
		0,
		REG_DWORD,
		(LPBYTE)&value,
		sizeof(DWORD32)
	);
	std::cout << c;
	if (c != ERROR_SUCCESS) return c;
	return 0;
}

LRESULT RegManage::getQword(std::wstring key, DWORD64* val) {
	if (!this->opened) return E_FAIL;

	DWORD dwSize = sizeof(DWORD64), dwType = REG_QWORD;

	DWORD32 data;
	LRESULT c = RegQueryValueEx(
		this->open_hkey,
		key.c_str(),
		0,
		&dwType,
		(LPBYTE)&data,
		&dwSize
	);

	if (c != ERROR_SUCCESS) return c;
	*val = data;
	return 0;
}

LRESULT RegManage::getDword(std::wstring key, DWORD32* val) {
	if (!this->opened) return E_FAIL;

	DWORD dwSize = sizeof(DWORD32), dwType = REG_DWORD;

	DWORD32 data;
	LRESULT c = RegQueryValueEx(
		this->open_hkey,
		key.c_str(),
		0,
		&dwType,
		(LPBYTE)&data,
		&dwSize
	);

	if (c != ERROR_SUCCESS) return c;
	*val = data;
	return 0;
}

LRESULT RegManage::getString(std::wstring key, std::wstring* val) {
	if (!this->opened) return E_FAIL;

	DWORD dwType = REG_SZ;

	DWORD bytesToRead = 1024, addBytes = 1024;
	WCHAR* data = (WCHAR*) malloc(sizeof(WCHAR) * bytesToRead);


	LRESULT c = RegQueryValueEx(
		this->open_hkey,
		key.c_str(),
		0,
		&dwType,
		(LPBYTE)data,
		&bytesToRead
	);

	while (c == ERROR_MORE_DATA) {
		bytesToRead += addBytes;
		data = (WCHAR*)malloc(sizeof(WCHAR) * bytesToRead);
		c = RegQueryValueEx(
			this->open_hkey,
			key.c_str(),
			0,
			&dwType,
			(LPBYTE)data,
			&bytesToRead
		);
	}
	if (c != ERROR_SUCCESS) return c;
	if (data == NULL) {
		*val = std::wstring();
	} else {
		*val = std::wstring(data);
	}
	return 0;
}

BOOL RegManage::valid() {
	return this->opened;
}