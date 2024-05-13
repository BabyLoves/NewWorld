#include "main.h"

void HKD_ItemPrice_FormatDecimal_AutoTrade(char* gold, int value)
{
	char st[32];
	char result[32];
	memset(result, 0, sizeof result);

	_itoa(value, st, 10);

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

	sprintf(gold, "Preço: %s", result);

}

void HKD_ItemPrice_FormatDecimal_02(char* pointer, int gold)
{
	char st[32];
	char result[32];
	memset(result, 0, sizeof result);

	_itoa(gold, st, 10);

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

	sprintf(pointer, "Preço: %s", result);

}

void HKD_ItemPrice_FormatDecimal_03(char* pointer, int gold)
{
	char st[32];
	char result[32];
	memset(result, 0, sizeof result);

	_itoa(gold, st, 10);

	int len = strlen(st);
	int sum = ((len - 1) / 3);

	for (int i = (len - 1), count = 0, index = (len - 1) + sum; i >= 0; i--, count++)
	{
		if (!(count % 3) && count != 0)
		{
			result[index] = ',';
			index--;
		}

		result[index] = st[index];

		count++;
		index--;
	}
	int Value = gold;

	if (Value < 1000)
		sprintf(pointer, "Preço de venda: %s Uni", result);
	else if (Value >= 1000 && Value < 1000000)
		sprintf(pointer, "Preço de venda: %s0 Uni", result);
	else if (Value >= 1000000)
		sprintf(pointer, "Preço de venda: %s00 Uni", result);
}

