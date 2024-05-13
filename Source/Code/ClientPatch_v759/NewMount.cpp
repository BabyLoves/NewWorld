#include "main.h"

enum MountFace
{
	LoboGelado = 389,
	TESTE = 346,
	CavRed = 347,
	CavBlue = 348,
	CavReinoRed = 349,
	CavReinoBlue = 350

};

void NewMount(int32_t index, int32_t* value)
{
	switch (index)
	{
	case 3990: *value = CavRed;
		break;

	case 3991: *value = CavBlue;
		break;

	case 3992: *value = LoboGelado;
		break;

	case 3995: *value = CavReinoRed;
		break;

	case 3996: *value = CavReinoBlue;
		break;
		
	case 5705: *value = TESTE;
		break;

	default:
		break;
	}
}