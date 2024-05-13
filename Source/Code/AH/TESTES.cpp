
#include "StdAfx.h"


void Main(){
	cout << "Test cpp active!" << endl;
}

void Mainx(){
again:
	Sleep(5000);
	Main();
	goto again;
}


void TESTES(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Mainx), NULL, 0, 0);
}

