
#include "stdafx.h"
#include "Splash.h"


void Spla(){
	CSplash splash1(TEXT(".\\NUI/Protect.bmp"), RGB(128, 128, 128));
	splash1.ShowSplash();
	Sleep(8000);
	splash1.CloseSplash();
}

void SplashShow()
{
	if (carrega.LA_Detecta_byPipe || carrega.LA_Detecta_ByFileSize == 1){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Spla), NULL, 0, 0);
	}
	else
	{
		Spla();
	}
}



