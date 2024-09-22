#pragma once

#include <Windows.h>
#include <string>

using std::wstring;


BOOL BcreateWindow(
	HINSTANCE instance
);

ATOM BgetRegisteredClass(HINSTANCE instance);

LRESULT CALLBACK BWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
