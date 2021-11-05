/*

#include "include.h"

BOOL CALLBACK refresh(HWND hwnd, [[maybe_unused]] LPARAM lparam) {
	RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
	return TRUE;
}

VOID WINAPI corrupt(HWND hMsg) {
	BITMAPINFO bit = { 0 };
	HDC hdcMsg, temp;
	HBITMAP bitmsg;
	RECT msgbox;

	GetWindowRect(hMsg, &msgbox);
	INT w = msgbox.right - msgbox.left;
	INT h = msgbox.bottom - msgbox.top;

	bit.bmiHeader.biSize = sizeof(BITMAPINFO);
	bit.bmiHeader.biBitCount = 32;
	bit.bmiHeader.biPlanes = 1;
	bit.bmiHeader.biWidth = w;
	bit.bmiHeader.biHeight = h;

	HANDLE heap = GetProcessHeap();
	tagRGBQUAD rgbpix = (tagRGBQUAD)HeapAlloc(heap, 0, w * h * sizeof(tagRGBQUAD));

	hdcMsg = GetDC(hMsg);
	temp = CreateCompatibleDC(hdcMsg);
	bitmsg = CreateDIBSection(hdcMsg, &bit, 0, &rgbpix, NULL, 0);
	SelectObject(temp, bitmsg);

	while (true) {
		fori(w * h) {
			rgbpix[(INT32)i].rgb = (rand() % 0x100) * 0x010101;
		}

		BitBlt(hdcMsg, 0, 0, w, h, temp, 0, 0, SRCCOPY);
		EnumChildWindows(hMsg, refresh, 0);
		Sleep(10);
	}

}*/