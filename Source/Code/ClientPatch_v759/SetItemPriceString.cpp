#include "main.h"

bool SetItemPriceString(STRUCT_ITEM* item, char* str)
{
	for (int a = 0; a <= 2; a++)
	{
		if (item->stEffect[a].cEffect == 91)
		{
			sprintf(str, "Donate: %d", item->stEffect[a].cValue);
			return TRUE;
		}
		else if (item->stEffect[a].cEffect == 92)
		{
			sprintf(str, "Honra: %d", item->stEffect[a].cValue);
			return TRUE;
		}

		else if (item->stEffect[0].cEffect == 61 && item->stEffect[0].cValue >= 1)
		{
			int valor = item->stEffect[0].cValue * GetItemPrice(item->sIndex);
			valor *= 1.10;

			char st[32];
			char result[32];
			memset(result, 0, sizeof result);

			_itoa(valor, st, 10);

			int len = strlen(st);
			int sum = ((len - 1) / 3);

			for (int i = (len - 1), count = 0, index = (len - 1) + sum; i >= 0; i--, count++)
			{
				if (!(count % 3) && count != 0)
				{
					result[index] = ',';
					index--;
				}

				result[index] = st[i];

				count++;
				index--;
			}

			char Porcentagem[2] = "%";
			sprintf(str, "Preço: %s (Taxa de Imposto:10%s)", result, Porcentagem);
			return TRUE;
		}
	}

	//fada verde 3 dias
	if (item->sIndex == 3900) {
		sprintf(str, "Donate: 3");
		return TRUE;
	}
	//fada azul 3 dias
	if (item->sIndex == 3901) {
		sprintf(str, "Donate: 3");
		return TRUE;
	}
	//fada vermelha 3 dias
	if (item->sIndex == 3902) {
		sprintf(str, "Donate: 5");
		return TRUE;
	}

	if (item->sIndex == 4434 || item->sIndex == 4435 || item->sIndex == 4436) {
		sprintf(str, "+10% EXP | +10% DROP | Donate: 20");
		return TRUE;
	}

	if (item->sIndex >= 4150 && item->sIndex <= 4467) {
		sprintf(str, "Donate: 15");
		return TRUE;
	}

	int valor = GetItemPrice(item->sIndex);
	valor *= 1.10;

	char st[32];
	char result[32];
	memset(result, 0, sizeof result);

	_itoa(valor, st, 10);

	int len = strlen(st);
	int sum = ((len - 1) / 3);

	for (int i = (len - 1), count = 0, index = (len - 1) + sum; i >= 0; i--, count++)
	{
		if (!(count % 3) && count != 0)
		{
			result[index] = ',';
			index--;
		}

		result[index] = st[i];

		count++;
		index--;
	}

	char Porcentagem[2] = "%";
	sprintf(str, "Preço: %s (Taxa de Imposto:10%s)", result, Porcentagem);
	return TRUE;

	return FALSE;
}