#include "BroadCastShowWindow.h"
#include <string>
#include <iostream>
using std::wstring;

HINSTANCE hinstance;
ATOM BgetRegisteredClass(HINSTANCE instance) {
	WNDCLASSEX ex;
	ex.cbSize = sizeof(WNDCLASSEX);
	ex.lpfnWndProc = BWndProc;
	ex.cbClsExtra = 0;
	ex.cbWndExtra = 0;
	ex.hInstance = instance;
	ex.hIcon = LoadIcon(instance, IDI_APPLICATION);
	ex.hCursor = LoadCursor(NULL, IDC_ARROW);
	ex.hIconSm = LoadIcon(ex.hInstance, NULL);
	ex.style = CS_NOCLOSE | CS_OWNDC | CS_DBLCLKS;
	ex.hbrBackground = CreateSolidBrush(RGB(0,0,0));
	ex.lpszClassName = TEXT("BroadCastWin");
	ex.lpszMenuName = NULL;

	return RegisterClassExW(&ex);
}

BOOL BcreateWindow(
	HINSTANCE instance
) {
	UINT height = GetSystemMetrics(SM_CXSCREEN);
	UINT width = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = CreateWindow(TEXT("BroadCastWin"), TEXT("Broadcast"), WS_POPUP | WS_MAXIMIZE, 0, 0,0,0, NULL, NULL, instance, NULL);
	if (!hwnd) return FALSE;
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return TRUE;
}


LRESULT CALLBACK BWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	wstring target = TEXT("��Ҫ�ٽ�����,��\n��!��!��!��!"),ver_info=TEXT("Limitation Plan �汾 1001");

	HDC hdc;
	PAINTSTRUCT ps;
	HFONT ft1,ft2;
	RECT rect,content_rect;
	HWND f1;
	GetWindowRect(hwnd, &rect);
	int height = 0;

	content_rect = rect;
	content_rect.top = content_rect.bottom = (content_rect.top + content_rect.bottom) / 2;

	ft1 = CreateFont
	(
		50, 0,    //�߶�20, ��ȡ0��ʾ��ϵͳѡ�����ֵ
		0, 0,    //�ı���б����������б��Ϊ0
		FW_HEAVY,    //����
		0, 0, 0,        //��б�壬���»��ߣ����л���
		GB2312_CHARSET,    //�ַ���
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,        //һϵ�е�Ĭ��ֵ
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("����")   //��������
	);
	ft2 = CreateFont
	(
		15, 0,    //�߶�20, ��ȡ0��ʾ��ϵͳѡ�����ֵ
		0, 0,    //�ı���б����������б��Ϊ0
		FW_HEAVY,    //����
		0, 0, 0,        //��б�壬���»��ߣ����л���
		GB2312_CHARSET,    //�ַ���
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,        //һϵ�е�Ĭ��ֵ
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("΢���ź�")   //��������
	);
	
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SetTextColor(hdc, RGB(255, 252, 0));
		SetBkColor(hdc, RGB(0, 0, 0));

		SelectObject(hdc, ft1);
		height = DrawText(hdc, target.c_str(), target.size(), &content_rect, DT_CALCRECT | DT_CENTER | DT_VCENTER | DT_WORDBREAK);
		content_rect.top -= height / 2;
		content_rect.bottom += height / 2;
		content_rect.left = rect.left;
		content_rect.right = rect.right;
		DrawText(hdc, target.c_str(), target.size(), &content_rect, DT_CENTER  | DT_WORDBREAK);
		SetTextAlign(hdc, TA_CENTER);
		SetTextColor(hdc, RGB(255,255, 255));
		SelectObject(hdc, ft2);
		TextOut(hdc,  rect.right - 100, rect.bottom-30, ver_info.c_str(),ver_info.size());
		EndPaint(hwnd, &ps);
		break;
	default:
		return DefWindowProc(hwnd, message, wparam,lparam);
	}
	return 0;
}