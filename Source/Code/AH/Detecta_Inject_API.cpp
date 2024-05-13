#include "stdafx.h"

//Delete API Detector
void DeleteAPI(){
	cout << "api";
	DWORD OldProtect = 0;
	// Get base address of module
	char *pBaseAddr = (char*)GetModuleHandle(NULL);
	// Change memory protection
	VirtualProtect(pBaseAddr, 4096, // Assume x86 page size
		PAGE_READWRITE, &OldProtect);
	// Erase the header
	ZeroMemory(pBaseAddr, 4096);
}





BOOLEAN BlockAPI(HANDLE, CHAR *, CHAR *);
void AntiInject()
{
	HANDLE hProc = GetCurrentProcess();
	while (TRUE) {
		DAntiInject(); // Antikill
		BlockAPI(hProc, "NTDLL.DLL", "LdrLoadDll");
		Sleep(carrega.DAPIInject_occours);
	}
}

BOOLEAN BlockAPI(HANDLE hProcess, CHAR *libName, CHAR *apiName)
{
	CHAR pRet[] = { 0xC3 };
	HINSTANCE hLib = NULL;
	VOID *pAddr = NULL;
	BOOL bRet = FALSE;
	DWORD dwRet = 0;

	hLib = LoadLibrary(libName);
	if (hLib) {
		pAddr = (VOID*)GetProcAddress(hLib, apiName);
		if (pAddr) {
			if (WriteProcessMemory(hProcess,
				(LPVOID)pAddr,
				(LPCVOID)pRet,
				sizeof(pRet),
				&dwRet)) {
				if (dwRet) {
					bRet = TRUE;
				}
			}
		}
		FreeLibrary(hLib);
	}
	return bRet;
}


void API_Inject(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(AntiInject), NULL, 0, 0);
}
