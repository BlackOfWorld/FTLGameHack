#pragma once
#include <Windows.h>
namespace pointers {
	uintptr_t pointerToScrap = 0x4D4; // sig could be "5E 00 00 00 00 40 00 ?? ?? ?? 00 00 00 00 00 00 01 ?? 00 00 00 00 00 00 80 BF 00 00 00 00 00 00 00 00 00 00 00 00 ?? ?? ?? 0D ?? ?? ?? 0D ?? ?? ?? 0D"
	uintptr_t pointerToWarp = 0x494;
	uintptr_t pointersToDroneParts[4] = {0x4C,0x20,0x11C,0x80}; // sig could be "00 00 ?? ?? ?? ?? 00 00 00 00 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 01 ?? ?? ?? 01 01 01 ?? 00 00 00 00 ?? ?? 66 1A ?? ?? 66 1A ?? ?? 66 1A"
	uintptr_t pointerToHull = 0xCC;
	uintptr_t pointersToRockets[2] = { 0x48,0x1E8 };
	//found info at FTLGame.exe+20F827 (GOG version)
	uintptr_t pointersToWeapon1Ready[5] = { 0x48, 0x144, 0x88, 0x0, 0x62C }; //0x61 for how many shots fired ,0x62 for ready status, 08 for energy status (0 min - 10 max)
	uintptr_t pointersToWeapon2Ready[5] = { 0x48, 0x144, 0x88, 0x4, 0x62C };
	uintptr_t pointersToWeapon3Ready[5] = { 0x48, 0x144, 0x88, 0x8, 0x62C };
	uintptr_t pointersToWeapon4Ready[5] = { 0x48, 0x144, 0x88, 0xC, 0x62C };
	uintptr_t pointersToWeapon5Ready[5] = { 0x48, 0x144, 0x7C, 0x0, 0x62C };
	uintptr_t pointersToWeapon6Ready[5] = { 0x48, 0x144, 0x7C, 0x4, 0x62C };
	uintptr_t pointersToWeapon7Ready[5] = { 0x48, 0x144, 0x7C, 0x8, 0x62C };
	uintptr_t pointersToWeapon8Ready[5] = { 0x48, 0x144, 0x7C, 0xC, 0x62C };
	uintptr_t pointersToShipInvis[2] = { 0x2C,0x1C0 };
	uintptr_t pointersToInstaJump[5] = { 0x3B8, 0x8, 0x18, 0x64, 0x48C };
	uintptr_t pointersToShowMap[10] = { 0x20,0x10,0xB8,0xD0,0xD0,0x20,0x4,0x8,0x0,0x37C };
	uintptr_t pointersToEnemyHealth[3] = { 0x8, 0x468, 0xC4 };
}