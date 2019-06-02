// FTLGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "offsets.h"
#include "globals.h"
#include "pointers.h"
#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#define VERSION 1 // 0 for discord, 1 for gog
HMODULE GetGameModHandle(HANDLE gHandle)
{
	HMODULE hMods[1024];
	DWORD cbNeeded;

	if (EnumProcessModules(gHandle, hMods, sizeof(hMods), &cbNeeded))
	{
		for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(gHandle, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				std::wstring wstrModName = szModName;
				//you will need to change this to the name of the exe of the foreign process
				std::wstring wstrModContain = L"FTLGame.exe";
				if (wstrModName.find(wstrModContain) != std::string::npos)
				{
					return hMods[i];
				}
			}
		}
	}
	return nullptr;
}
DWORD GetValuePointer(int address,int offset)
{
	int Address = address;
	ReadProcessMemory(globals::gameHandle, (LPCVOID)Address, &Address, 4, NULL);
	Address += offset;
	return Address;
}
DWORD GetValuePointers(int baseaddr, int offsets[], int offset)
{
	int Address = baseaddr;
	int total = offset;
	for (int i = 0; i < total; i++) //Loop trough the offsets
	{
		ReadProcessMemory(globals::gameHandle, (LPCVOID)Address, &Address, 4, NULL);
		Address += offsets[i];
	}
	return Address;
}
void setCursorPosition(int x, int y)
{
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}
BOOL WINAPI CTRL_C_Handler(DWORD dwCtrlType)
{
	puts("Closing handle...");
	CloseHandle(globals::gameHandle);
	puts("Done!\nBye!");
 	exit(0);
	return TRUE;
}
void ClearConsole(char fill = ' ')
{
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	GetConsoleScreenBufferInfo(hOut, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacterA(hOut, fill, cells, tl, &written);
	FillConsoleOutputAttribute(hOut, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(hOut, tl);
}
void setValues(int number = 1000,int hull = 30,BOOL rapid = 1, BOOL invisShip = 1)
{
	WriteProcessMemory(globals::gameHandle, (void*)globals::pScrap, &number, sizeof(number), nullptr);
	WriteProcessMemory(globals::gameHandle, (void*)globals::pWarp, &number, sizeof(number), nullptr);
	WriteProcessMemory(globals::gameHandle, (void*)globals::pScrap, &number, sizeof(number), nullptr);
	WriteProcessMemory(globals::gameHandle, (void*)globals::pWarp, &number, sizeof(number), nullptr);
	WriteProcessMemory(globals::gameHandle, (void*)globals::pRockets, &number, sizeof(number), nullptr);
	WriteProcessMemory(globals::gameHandle, (void*)globals::pDroneParts, &number, sizeof(number), nullptr);
	WriteProcessMemory(globals::gameHandle, (void*)globals::pHull, &hull, sizeof(hull), nullptr);
	if (rapid) {
		int full = 4;
		WriteProcessMemory(globals::gameHandle, (void*)globals::pWeapon1Ready, &full, sizeof(full), nullptr);
		WriteProcessMemory(globals::gameHandle, (void*)globals::pWeapon2Ready, &full, sizeof(full), nullptr);
		WriteProcessMemory(globals::gameHandle, (void*)globals::pWeapon3Ready, &full, sizeof(full), nullptr);
		WriteProcessMemory(globals::gameHandle, (void*)globals::pWeapon4Ready, &full, sizeof(full), nullptr);
		WriteProcessMemory(globals::gameHandle, (void*)globals::pWeapon5Ready, &full, sizeof(full), nullptr);
		WriteProcessMemory(globals::gameHandle, (void*)globals::pWeapon6Ready, &full, sizeof(full), nullptr);
		WriteProcessMemory(globals::gameHandle, (void*)globals::pWeapon7Ready, &full, sizeof(full), nullptr);
		WriteProcessMemory(globals::gameHandle, (void*)globals::pWeapon8Ready, &full, sizeof(full), nullptr);
	}
	WriteProcessMemory(globals::gameHandle, (void*)globals::pShipInvis, &invisShip, sizeof(BYTE), nullptr);
}
void PrintValues()
{
	setCursorPosition(0, 0);
	int scrapValue = 0;
	int warpValue = 0;
	int rocketValue = 0;
	int dronePartsValue = 0;
	int hullValue = 0;
	int sectorValue = 0;
	BOOL weapon1Ready = 0;
	BOOL weapon2Ready = 0;
	BOOL weapon3Ready = 0;
	BOOL weapon4Ready = 0;
	BOOL weapon5Ready = 0;
	BOOL weapon6Ready = 0;
	BOOL weapon7Ready = 0;
	BOOL weapon8Ready = 0;
	BOOL inFight = 0;
	BYTE shipInvis = 0;
	BOOL isAE_Enabled = 0;
	ReadProcessMemory(globals::gameHandle, (void*)globals::pScrap, &scrapValue, sizeof(scrapValue), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pWarp, &warpValue, sizeof(warpValue), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pRockets, &rocketValue, sizeof(rocketValue), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pDroneParts, &dronePartsValue, sizeof(dronePartsValue), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pHull, &hullValue, sizeof(hullValue), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pWeapon1Ready, &weapon1Ready, sizeof(weapon1Ready), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pWeapon2Ready, &weapon2Ready, sizeof(weapon2Ready), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pWeapon3Ready, &weapon3Ready, sizeof(weapon3Ready), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pWeapon4Ready, &weapon4Ready, sizeof(weapon4Ready), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pWeapon5Ready, &weapon5Ready, sizeof(weapon5Ready), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pWeapon6Ready, &weapon6Ready, sizeof(weapon6Ready), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pWeapon7Ready, &weapon7Ready, sizeof(weapon7Ready), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pWeapon8Ready, &weapon8Ready, sizeof(weapon8Ready), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::pShipInvis, &shipInvis, sizeof(shipInvis), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::inDanger, &inFight, sizeof(inFight), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::inSector, &sectorValue, sizeof(sectorValue), nullptr);
	ReadProcessMemory(globals::gameHandle, (void*)globals::isAE_Enabled, &isAE_Enabled, sizeof(isAE_Enabled), nullptr);
	printf("Game handle: 0x%p\nBase address: 0x%p\nPointer to scrap: 0x%lX\nPointer to warps: 0x%lX\nPointer to rockets: 0x%lX\nPointer to drone parts: 0x%lX\nPointer to hull: 0x%lX\nPointer to weapon 1 ready: 0x%lX\nPointer to weapon 2 ready: 0x%lX\nPointer to weapon 3 ready: 0x%lX\nPointer to weapon 4 ready: 0x%lX\nPointer to weapon 5 ready: 0x%lX\nPointer to weapon 6 ready: 0x%lX\nPointer to weapon 7 ready: 0x%lX\nPointer to weapon 8 ready: 0x%lX\nPointer to ship invis: 0x%lX\nStatic address to in danger: 0x%lX\nStatic address to in sector: 0x%lX\nStatic address to AE Enabled: 0x%lX\nCurrent amount of scrap: %d          \nCurrent amount of warps: %d          \nCurrent amount of rockets: %d          \nCurrent amount of drone parts: %d          \nCurrent HP (hull): %d          \nWeapon 1 ready: %d          \nWeapon 2 ready: %d          \nWeapon 3 ready: %d          \nWeapon 4 ready: %d          \nWeapon 5 ready: %d          \nWeapon 6 ready: %d          \nWeapon 7 ready: %d          \nWeapon 8 ready: %d          \nShip invis: %d          \nIn danger: %d          \nIn sector: %d          \nIs advanced content enabled: %d          \n", globals::gameHandle, globals::gameMod, globals::pScrap, globals::pWarp, globals::pRockets, globals::pDroneParts, globals::pHull, globals::pWeapon1Ready, globals::pWeapon2Ready, globals::pWeapon3Ready, globals::pWeapon4Ready, globals::pWeapon5Ready, globals::pWeapon6Ready, globals::pWeapon7Ready, globals::pWeapon8Ready, globals::pShipInvis, globals::inDanger,globals::inSector, globals::isAE_Enabled, scrapValue, warpValue, rocketValue, dronePartsValue, hullValue, weapon1Ready, weapon2Ready, weapon3Ready, weapon4Ready, weapon5Ready, weapon6Ready, weapon7Ready, weapon8Ready, shipInvis, inFight, sectorValue, isAE_Enabled);
}
DWORD WINAPI Hihi(LPVOID param)
{
	int number = 100000;
	while(true)
	{
		PrintValues();
	    setValues();
		if (GetLastError() == 5) break;
		Sleep(10);
	}
	system("cls");
	printf("Game exited or unknown error. GetLastError: %d\n",GetLastError());
	ExitProcess(GetLastError());
}
DWORD WINAPI refreshPointers(LPVOID param) {
	DWORD pValClass = (DWORD)globals::gameMod + offsets::saveClass;
	while (true) {
		globals::pWeapon1Ready = GetValuePointers((DWORD)pValClass, pointers::pointersToWeapon1Ready, 5);
		globals::pWeapon2Ready = GetValuePointers((DWORD)pValClass, pointers::pointersToWeapon2Ready, 5);
		globals::pWeapon3Ready = GetValuePointers((DWORD)pValClass, pointers::pointersToWeapon3Ready, 5);
		globals::pWeapon4Ready = GetValuePointers((DWORD)pValClass, pointers::pointersToWeapon4Ready, 5);
		globals::pWeapon5Ready = GetValuePointers((DWORD)pValClass, pointers::pointersToWeapon5Ready, 5);
		globals::pWeapon6Ready = GetValuePointers((DWORD)pValClass, pointers::pointersToWeapon6Ready, 5);
		globals::pWeapon7Ready = GetValuePointers((DWORD)pValClass, pointers::pointersToWeapon7Ready, 5);
		globals::pWeapon8Ready = GetValuePointers((DWORD)pValClass, pointers::pointersToWeapon8Ready, 5);
		globals::pShipInvis = GetValuePointers((DWORD)pValClass, pointers::pointersToShipInvis, 2);
		globals::pRockets = GetValuePointers((DWORD)pValClass, pointers::pointersToRockets, 2);
		//globals::pDroneParts = GetValuePointers((DWORD)pValClass, pointers::pointersToDroneParts,4);
		globals::pDroneParts = GetValuePointer((DWORD)pValClass, 0x800);
		globals::pScrap = GetValuePointer((DWORD)pValClass, pointers::pointerToScrap);
		globals::pWarp = GetValuePointer((DWORD)pValClass, pointers::pointerToWarp);
		globals::pHull = GetValuePointer((DWORD)pValClass, pointers::pointerToHull);
		globals::inDanger = (DWORD)globals::gameMod + offsets::inDanger;
		globals::inSector = (DWORD)globals::gameMod + offsets::inSector;
		globals::isAE_Enabled = (DWORD)globals::gameMod + offsets::isAE_Enabled;
		Sleep(30000);
	}
}
int main()
{
#if VERSION == 1
	offsets::inDanger += 0x1000;
	offsets::inSector += 0x1000;
	offsets::isAE_Enabled += 0x1000;
	offsets::saveClass += 0x1000;
#endif
	SetConsoleTitle(L"BlackOfWorld's super elite haxx 4 FTL: Faster Than Light");
	SetConsoleCtrlHandler(CTRL_C_Handler, true);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(hOut, &cursorInfo);
	globals::gameWindow = FindWindowA(nullptr,"FTL: Faster Than Light");
	if (globals::gameWindow == nullptr)
	{
		puts("Game is not running! Please launch FTL and then this program. Exiting...");
		return 1;
	}
	DWORD gameId;
	GetWindowThreadProcessId((HWND)globals::gameWindow, &gameId);
	globals::gameHandle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, gameId);
	if(globals::gameHandle == nullptr)
	{
		puts("Could not open handle to the game!");
		return 2;
	}
	globals::gameMod = GetGameModHandle(globals::gameHandle);
	CreateThread(nullptr, 0, refreshPointers, nullptr, 0, nullptr);
	CreateThread(nullptr, 0, Hihi, nullptr, 0, nullptr);
	getchar();
	return 0;
}