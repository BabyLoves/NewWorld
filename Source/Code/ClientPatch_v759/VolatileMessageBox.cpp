#include "main.h"
// e0 sd2 12* n da esse err6
bool SetVolatileMessageBoxText(int itemID, char* text)
{
	if (itemID == 3314) //Frango Assado
	{
		sprintf(text, "Deseja comer esse delicioso Frango Assado?");
		return true;
	}
	if (itemID == 3363) //Poção Sephira (30dias)
	{
		sprintf(text, "Deseja ativar a Poção Sephira (30d)?");
		return true;
	}
	if (itemID == 3366) //Poção de Saúde (30dias)
	{
		sprintf(text, "Deseja ativar a Poção de Saúde (30d)?");
		return true;
	}
	if (itemID == 3381) //Poção Divina (30dias)
	{
		sprintf(text, "Deseja ativar a Poção Divina (30d)?");
		return true;
	}
	if (itemID == 4140) //Baú de XP
	{
		sprintf(text, "Deseja ativar o Baú de Experiência?");
		return true;
	}
	if (itemID == 3394) //Barra de Donate (1)
	{
		sprintf(text, "Deseja ativar Barra de Donate(01 Donate)?");
		return true;
	}
	if (itemID == 3395) //Barra de Donate (10)
	{
		sprintf(text, "Deseja ativar Barra de Donate(10 Donate)?");
		return true;
	}
	if (itemID == 3396) //Barra de Donate (20)
	{
		sprintf(text, "Deseja ativar Barra de Donate(20 Donate)?");
		return true;
	}

	return false;
}

int AddVolatileMessageItem(int itemID)
{
	switch (itemID)
	{
	case 3314:
		return 1;
	}
	return 0;
}