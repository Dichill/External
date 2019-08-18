#include "pch.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"

int main()
{
	// Design
	std::cout << "=================================================" << std::endl;
	std::cout << "         Dichill's Assualt Cube Trainer" << std::endl;
	std::cout << "=================================================" << std::endl;
	std::cout << "                                                 " << std::endl;
	std::cout << "             >> github.com/Dichill <<" << std::endl;

    // Get ProcID of the target process
	DWORD procId = GetProcId(L"ac_client.exe");

	// GetModuleBaseAddress
	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

	// Get Handle To Process
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	// Reslove base address fo the pointer Chain
	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x10F4F4;
	std::cout << "                                                 " << std::endl;
	std::cout << "=================================================" << std::endl;
	std::cout << "          DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;	
	std::cout << "=================================================" << std::endl;
	std::cout << "                                                 " << std::endl;
	// Resolve our ammo pointer chain
	std::vector<unsigned int> ammoOffsets = {0x374, 0x14, 0x0};
	uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);

	// Read Ammo value
	int ammoValue = 0;

	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
	std::cout << "Current Ammo = " << std::dec << ammoValue << std::endl;

	// Write to it
	int newAmmo = 1337;
	WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

	// Read out Again
	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
	std::cout << "New Ammo = " << std::dec << ammoValue << std::endl;	
	getchar();
	return 0;
}

