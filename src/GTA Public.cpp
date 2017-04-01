#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <TlHelp32.h>
#include <time.h>
#include "GetModuleBase.h"

using namespace std; // bla bla bla

//vars here
HANDLE phandle;
DWORD PID;
__int64 BaseAddress;

int WantedLevel = 0;
bool NeverWanted = false;

DWORD WantedBase = 0x01F7F6D0;
DWORD Offset1 = 0x8;
DWORD Offset2 = 0x0;
DWORD Offset3 = 0x8;
DWORD Offset4 = 0x2E0;
DWORD Offset5 = 0x798;
__int64 WantedLevelPointer = 0;

int pVelocity = 5;
bool RUN = false;
DWORD PlayerInfo = 0x10B8;
DWORD FastRun = 0xE8;
__int64 FastRunPointer = 0;

int main() {
	wchar_t* WindowName = L"Grand Theft Auto V";
	wchar_t* GameTitle = L"GTA5.exe";

	HWND WindowHandle = FindWindow(NULL, WindowName);
	BaseAddress = GetBase_c.GetModuleBaseAddress(GameTitle, GameTitle);

	GetWindowThreadProcessId(WindowHandle, &PID);
	phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, PID); //never forget

	if (!WindowHandle) {
		cout << "not found";
	}

	SetConsoleTitle(L"GTA V: Public");
	cout << "Welcome to GTA V: Public" << endl;
	cout << "------------------------" << endl;
	cout << "Cheat features" << endl;
	cout << "--------------" << endl;
	cout << "+ GOD Mode [NUMPAD0]" << endl;
	cout << "+ Never Wanted [NUMPAD1]" << endl;
	cout << "+ Ever Wanted [NUMPAD2]" << endl;
	cout << "+ Fast Run [NUMPAD3]" << endl;

	for (;;) { //infinite loop
		if (GetAsyncKeyState(VK_NUMPAD1)) {
			NeverWanted = !NeverWanted;
			cout << "Never Watend: " << NeverWanted << endl;
			Sleep(150);
		}

		if (NeverWanted == true) {
			ReadProcessMemory(phandle, (void*)(BaseAddress + WantedBase), &WantedLevelPointer, sizeof(WantedLevelPointer), NULL);
			ReadProcessMemory(phandle, (void*)(WantedLevelPointer + Offset1), &WantedLevelPointer, sizeof(WantedLevelPointer), NULL);
			ReadProcessMemory(phandle, (void*)(WantedLevelPointer + Offset2), &WantedLevelPointer, sizeof(WantedLevelPointer), NULL);
			ReadProcessMemory(phandle, (void*)(WantedLevelPointer + Offset3), &WantedLevelPointer, sizeof(WantedLevelPointer), NULL);
			ReadProcessMemory(phandle, (void*)(WantedLevelPointer + Offset4), &WantedLevelPointer, sizeof(WantedLevelPointer), NULL);
			WriteProcessMemory(phandle, (void*)(WantedLevelPointer + Offset5), &WantedLevel, sizeof(WantedLevel), NULL);
		}

		if (GetAsyncKeyState(VK_NUMPAD3)) {
			RUN = !RUN;
			cout << "Fast Run Mode: " << RUN << endl;
			Sleep(150);
		}

		if (RUN== true) {
			ReadProcessMemory(phandle, (void*)(PlayerInfo + FastRun), &PlayerInfo, sizeof(PlayerInfo), NULL);
			WriteProcessMemory(phandle, (void*)(PlayerInfo + FastRun), &pVelocity, sizeof(pVelocity), NULL);
		}

		Sleep(1);
	}
	return 0;
}