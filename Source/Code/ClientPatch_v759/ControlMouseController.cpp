#include "main.h"


void GameInterface::ControlMouseController(UIControl* Control, int mouseStatus, int posX, int posY)
{
	if (!Control)
		return;

	if (!Control->Handle)
		return;
	/*
	printf("Element: %d MouseMode:%d PosX:%d PosY:%d ",Control->Handle,mouseStatus,posX, posY);*/
}
