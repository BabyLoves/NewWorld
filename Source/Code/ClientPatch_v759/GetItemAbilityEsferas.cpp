#include "main.h"

INT32 HKD_GetItemAbility_Esferas(STRUCT_ITEM* item, INT32 effectId)
{
	if (item->sIndex == 3980 || item->sIndex == 3983 || item->sIndex == 3986)
	{
		switch (effectId)
		{
		case 2:
			return 35;

		case 60:
			return 7;
		}
	}
	else if (item->sIndex == 3982 || item->sIndex == 3985 || item->sIndex == 3988)
	{
		switch (effectId)
		{
		case 2:
			return 450;

		case 60:
			return 72;
		}
	}
	else if (item->sIndex == 3981 || item->sIndex == 3984 || item->sIndex == 3987)
	{
		switch (effectId)
		{
		case 2:
			return 450;

		case 60:
			return 72;

		case 54:
			return 28;
		}
	}
	else if (item->sIndex == 3993 || item->sIndex == 3994)
	{
		switch (effectId)
		{
		case 2:
			return 1050;
		case 60:
			return 145;
		case 54:
			return 20;
		}
	}
	else if (item->sIndex == 3995)
	{
		switch (effectId)
		{
		case 2:
			return 300;
		case 60:
			return 60;
		case 54:
			return 31;
		}
	}
	else if (item->sIndex == 3997)
	{
		switch (effectId)
		{
		case 2:
			return 400;
		case 60:
			return 70;
		case 54:
			return 31;
		}
	}
	else if (item->sIndex == 3998 || item->sIndex == 3991 || item->sIndex == 3992)
	{
		switch (effectId)
		{
		case 2:
			return 250;

		case 60:
			return 50;

		case 54:
			return 28;
		}
	}
	else if (item->sIndex == 3996 || item->sIndex == 3990)
	{
		switch (effectId)
		{
		case 2:
			return 450;
		case 60:
			return 70;
		case 54:
			return 31;
		}
	}
	return 0;
}