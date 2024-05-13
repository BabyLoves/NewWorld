#ifndef ANTI_RE_H
#define ANTI_RE_H

bool ReadConfig(const char* FileName);

void WINAPI AntiHack();

void CloseGame();
void BackupWinsockData();
unsigned long __stdcall AntiWPEPro(void* pVoid);
void I_loop();
void I_Scan();
void Injetado();
void Msg_I_Br();
void Dll_Inject();
void AntiInject();
BOOLEAN BlockAPI(HANDLE hProcess, CHAR* libName, CHAR* apiName);

// checa se tem algum aplicativo aberto
void TitleCheckWindow();
void Msg_W_Br();
bool TitleWindow(LPCSTR WindowTitle);
void W_Scan();
void YProtectionMain();






// Mais Proteções
bool GetFileName(char* text);

#endif // !ANTI_RE_H
