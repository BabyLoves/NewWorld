#include "main.h"

bool NewItensDay(INT32 Item)
{
	if (Item >= 4200 && Item <= 4499)
		return TRUE;
	else
	{
		switch (Item)
		{
		case 4214:
			return TRUE;
		case 4213:
			return TRUE;
		case 4212:
			return TRUE;
		case 4211:
			return TRUE;
		case 4210:
			return TRUE;
		case 4209:
			return TRUE;
		case 4208:
			return TRUE;
		case 4207:
			return TRUE;
		case 4206:
			return TRUE;
		case 4205:
			return TRUE;
		case 4204:
			return TRUE;
		case 4203:
			return TRUE;
		case 4202:
			return TRUE;
		case 4201:
			return TRUE;
		case 4200:
			return TRUE;
		case 5682:
			return TRUE;
		}
	}
	return FALSE;
}

void FormataValidadeEsferas(char* msg, STRUCT_ITEM* item)
{
	int dia, ano, mes;
	memset(&dia, 0x0, sizeof(int));
	memset(&ano, 0x0, sizeof(int));
	memset(&mes, 0x0, sizeof(int));

	for (int i = 0; i < 3; ++i)
	{
		switch (item->stEffect[i].cEffect)
		{
		case EF_WDAY:
			dia = item->stEffect[i].cValue;
			break;
		case EF_YEAR:
			ano = item->stEffect[i].cValue;
			break;
		case EF_WMONTH:
			mes = item->stEffect[i].cValue;
			break;
		}
	}

	char msgtes[100];

	if (item->sIndex >= 4331 && item->sIndex <= 4499)
	{

		for (int i = 0; i < 3; ++i)
		{
			switch (item->stEffect[i].cEffect)
			{
			case 110:
				dia = item->stEffect[i].cValue;
				break;
			case 109:
				ano = item->stEffect[i].cValue;
				break;
			case 106:
				mes = item->stEffect[i].cValue;
				break;
			}
		}
		sprintf(msg, "Válido até: [%02d:%02d:20%02d]", dia, mes, ano);
	}
	else
	{
		if (dia)
			sprintf(msg, "Válido por %02d dia(s)", dia);
		else
			sprintf(msg, "Válido até: [%02d:%02d:20%02d]", dia, mes, ano);

		if (mes)
			sprintf(msg, "Válido até: [%02d:%02d:20%02d]", dia, mes, ano);
		else
			sprintf(msg, "Válido até: [%02d:%02d:20%02d]", dia, mes, ano);

		if (ano)
			sprintf(msg, "Válido até: [%02d:%02d:20%02d]", dia, mes, ano);
		else
			sprintf(msg, "___");
	}


}

void FormataValidadeFada(char* msg, STRUCT_ITEM* item)
{
	int dia, hora, min;
	memset(&dia, 0x0, sizeof(int));
	memset(&hora, 0x0, sizeof(int));
	memset(&min, 0x0, sizeof(int));

	for (int i = 0; i < 3; ++i)
	{
		//ta errado aq .. nao entra na condição?
		switch (item->stEffect[i].cEffect)
		{
		case EF_WDAY:
			dia = item->stEffect[i].cValue;
			break;
		case EF_HOUR:
			hora = item->stEffect[i].cValue;
			break;
		case EF_MIN:
			min = item->stEffect[i].cValue;
			break;
		}
	}
	if (dia && !min && !hora)
		sprintf(msg, "Válido por %d dia(s)", dia);

	else
		sprintf(msg, "Válido até: %d / %0d / %s", dia, hora, min);

}

void FormataValidadeTraje(char* msg, STRUCT_ITEM* item)
{
	int dia, ano, mes;
	memset(&dia, 0x0, sizeof(int));
	memset(&ano, 0x0, sizeof(int));
	memset(&mes, 0x0, sizeof(int));

	for (int i = 0; i < 3; ++i)
	{
		//ta errado aq .. nao entra na condição?
		switch (item->stEffect[i].cEffect)
		{
		case EF_WDAY:
			dia = item->stEffect[i].cValue;
			break;
		case EF_YEAR:
			ano = item->stEffect[i].cValue;
			break;
		case EF_WMONTH:
			mes = item->stEffect[i].cValue;
			break;
		}
	}

	if (dia)
		sprintf(msg, "Válido por %02d dia(s)", dia);
	else
		sprintf(msg, "Válido até: [%02d:%02d:%02d]", dia, mes, ano);

	if (mes)
		sprintf(msg, "Válido até: [%02d:%02d:%02d]", dia, mes, ano);
	else
		sprintf(msg, "Válido até: [%02d:%02d:%02d]", dia, mes, ano);

	if (ano)
		sprintf(msg, "Válido até: [%02d:%02d:%02d]", dia, mes, ano);
	else
		sprintf(msg, "Aguardando ativação.");

	/*if (dia && !mes && !ano)
		sprintf(msg, "Válido por %02d dia(s)", dia);

	else
		sprintf(msg, "Válido até: [%02d:%02d:%02d]", dia, mes, ano);*/
}