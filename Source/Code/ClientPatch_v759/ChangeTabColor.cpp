#include "main.h"

int HKD_ChangeTabColor(char* msg)
{
	int color = 0xFFCCCCCC;
		
	if (!strcmp(msg, "Torne-se Cidadão"))
		color = TNColor::Default;
	else if (!strcmp(msg, "Ajudante Mágico"))
		color = TNColor::Default;
	else if (!strcmp(msg, "Informações da Guild"))
		color = TNColor::NewYellow;
	else if (!strcmp(msg, "Compositor + 10"))
		color = TNColor::DarkOrange;
	else if (!strcmp(msg, "Passar Add Armadura Arch"))
		color = TNColor::DeepPink;
	else if (!strcmp(msg, "Compositor Anct"))
		color = TNColor::CornBlue;
	else if (!strcmp(msg, "Compor Poeiras e Círculos"))
		color = TNColor::CornBlue;
	else if (!strcmp(msg, "Fale comigo para entrar!"))
		color = TNColor::CornBlue;
	else if (!strcmp(msg, "Esfera M"))
		color = TNColor::Default;
	else if (!strcmp(msg, "Esfera A"))
		color = TNColor::Default;
	else if (!strcmp(msg, "Esfera N"))
		color = TNColor::Default;
	else if (!strcmp(msg, "Baú"))
		color = TNColor::CornBlue;
	else if (!strcmp(msg, "Entrada Coliseu"))
		color = TNColor::CornBlue;
	else if (!strcmp(msg, "Reset Skill"))
		color = TNColor::CornBlue;
	else if (!strcmp(msg, "Teleport"))
		color = TNColor::Speak;
	else if (!strcmp(msg, "Comerciante"))
		color = TNColor::CornBlue;
	else if (!strcmp(msg, "Add Arma Arch"))
		color = TNColor::DarkOrange;
	else if (!strcmp(msg, "Compositor Diverso"))
		color = TNColor::Default;
	else if (!strcmp(msg, "Reviver Montarias"))
		color = TNColor::Default;
	else if (!strcmp(msg, "Quest Amuleto"))
		color = TNColor::Default;
	else if (!strcmp(msg, "Aprender Skill"))
		color = TNColor::CornBlue;

	return color;
}
