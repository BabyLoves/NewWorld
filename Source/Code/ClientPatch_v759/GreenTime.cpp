#include "main.h"

// Definir a área X e Y, return 1 para toda kersef.
INT32 HKD_GreenTime_NewArea(INT32 posX, INT32 posY)
{
#pragma region definiçoes originais
	//if (posX == 2 && posY == 4)
	//	return TRUE;

	//if (posX == 1 && posY == 31)
	//	return TRUE;

	//if (posX == 20 && posY == 13)
	//	return TRUE;

	//if (posX == 13 && posY == 16)
	//	return TRUE;

	//if (posX == 8 && posY == 13)
	//	return TRUE;

	//if (posX == 13 && posY == 15)
	//	return TRUE;

	//if (posX == 27 && posY == 11)
	//	return TRUE;

	////Quests Mortais
	//if (posX == 18 && posY == 16)
	//	return TRUE;

	//if (posX == 17 && posY == 13)
	//	return TRUE;

	//if (posX == 3 && posY == 30)
	//	return TRUE;

	//if (posX == 5 && posY == 29)
	//	return TRUE;

	//if (posX == 10 && posY == 31)
	//	return TRUE;
#pragma endregion

	auto mob = GetChar();

	static short coords[][2] =
	{
		/*    Deve ser colocado a posição inicial onde o player irá nascer    */

		//Quests
		{ 2398 , 2105 },//coveiro
		{ 2234 , 1714 },//jardim
		{ 464 , 3902 },//kaizen
		{ 668 , 3756 },//hidra
		{ 1322 , 4041 },//elfo
		//Casino
		{4000,4000},
		//Zonas Lan			
		{ 3639, 3639 },//N
		{ 3782, 3527 },//M
		{ 3911, 3655 },//A
		//RvR	 
		{1075, 2126},
		{1224, 1969 },
		//ZONA BATALHA REAL
		{3522 , 1471 },
		//Zona evento 1
		{2654, 1988 },
		//Gelo
		{3649, 3115 },
		//Erion
		{2459, 2014 },
		//Azran
		{2482, 1724 },
		//Noatun
		{1050, 1725 },
		//Armia
		{2100, 2100 },
		//EntradaCampo
		{2112, 2059 }

	};

	for (int i = 0; i < (sizeof(coords) / 4); i++)
	{
		if (posX == (coords[i][0] / 128) && posY == (coords[i][1] / 128))
			return TRUE;
	}
	return FALSE;
}