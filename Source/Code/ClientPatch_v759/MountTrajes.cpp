#include "main.h"

void ProcessViewMount_Skins(SkinId skinId, InternalMob* mob)
{
	if (skinId == SkinId::Arvak_Vermelho) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 8; // hs010112 -1 = 11
		mob->MountFrontMeshId = 8; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Arvak_Azul) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 9; // hs010112 -1 = 11
		mob->MountFrontMeshId = 9; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Arvak_Flamejante) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 13; // hs010112 -1 = 11
		mob->MountFrontMeshId = 13; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Arvak_Roxo) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 21; // hs010112 -1 = 11
		mob->MountFrontMeshId = 21; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Arvak_Metalico) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 22; // hs010112 -1 = 11
		mob->MountFrontMeshId = 22; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Deer) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 11; // hs010112 -1 = 11
		mob->MountFrontMeshId = 11; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Deer_Azul) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 12; // hs010112 -1 = 11
		mob->MountFrontMeshId = 12; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Asvid_Vermelho) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 23; // hs010112 -1 = 11
		mob->MountFrontMeshId = 23; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Asvid_Azul) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 24; // hs010112 -1 = 11
		mob->MountFrontMeshId = 24; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Asvid_Metalico) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 25; // hs010112 -1 = 11
		mob->MountFrontMeshId = 25; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Bode_Branco) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 26; // hs010112 -1 = 11
		mob->MountFrontMeshId = 26; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Big_Horns) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 17; // hs010112 -1 = 11
		mob->MountFrontMeshId = 17; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Small_Horns) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 27; // hs010112 -1 = 11
		mob->MountFrontMeshId = 27; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::White_Hair) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::hs01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 20; // hs010112 -1 = 11
		mob->MountFrontMeshId = 20; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Raposa_Amarela) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 2; // hs010112 -1 = 11
		mob->MountFrontMeshId = 2; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Raposa_Roxo) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 4; // hs010112 -1 = 11
		mob->MountFrontMeshId = 4; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Quimera_Flamejante) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 5; // hs010112 -1 = 11
		mob->MountFrontMeshId = 5; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Quimera_de_Madeira) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 6; // hs010112 -1 = 11
		mob->MountFrontMeshId = 6; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Quimera_Roxa) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 7; // hs010112 -1 = 11
		mob->MountFrontMeshId = 7; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Quimera_Verde) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 8; // hs010112 -1 = 11
		mob->MountFrontMeshId = 8; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Goat_Azul) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 9; // hs010112 -1 = 11
		mob->MountFrontMeshId = 9; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Goat_Vermelho) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 10; // hs010112 -1 = 11
		mob->MountFrontMeshId = 10; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Tigre_Negro) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 11; // hs010112 -1 = 11
		mob->MountFrontMeshId = 11; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Tigre_de_Gelo) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 12; // hs010112 -1 = 11
		mob->MountFrontMeshId = 12; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Tigre_Metalico) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::tg01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 13; // hs010112 -1 = 11
		mob->MountFrontMeshId = 13; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Bola_de_Futebol) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::kk01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 3; // hs010112 -1 = 11
		mob->MountFrontMeshId = 3; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 0; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 0; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 0; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Surkur) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::kk01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 4; // hs010112 -1 = 11
		mob->MountFrontMeshId = 4; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Coelho_Macabro) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::kk01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 5; // hs010112 -1 = 11
		mob->MountFrontMeshId = 5; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Pacman) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::kk01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 6; // hs010112 -1 = 11
		mob->MountFrontMeshId = 6; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 0; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 0; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 0; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Dragão_Negro) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 9; // hs010112 -1 = 11
		mob->MountFrontMeshId = 9; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Dragão_Flamejante) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 10; // hs010112 -1 = 11
		mob->MountFrontMeshId = 10; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Dragão_de_Madeira) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 11; // hs010112 -1 = 11
		mob->MountFrontMeshId = 11; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Dragão_Metalico) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr01); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 12; // hs010112 -1 = 11
		mob->MountFrontMeshId = 12; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::DV_Vermelho) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 4; // hs010112 -1 = 11
		mob->MountFrontMeshId = 4; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::DV_Azul) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 5; // hs010112 -1 = 11
		mob->MountFrontMeshId = 5; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::DV_Flamejante) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 6; // hs010112 -1 = 11
		mob->MountFrontMeshId = 6; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::DV_Metalico) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 7; // hs010112 -1 = 11
		mob->MountFrontMeshId = 7; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Fire_Dragon) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 8; // hs010112 -1 = 11
		mob->MountFrontMeshId = 8; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Diamond_Dragon) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 9; // hs010112 -1 = 11
		mob->MountFrontMeshId = 9; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Metal_Dragon) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 10; // hs010112 -1 = 11
		mob->MountFrontMeshId = 10; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}


	if (skinId == SkinId::Fire_Elemental_Dragon) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 11; // hs010112 -1 = 11
		mob->MountFrontMeshId = 11; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Ice_Elemental_Dragon) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 12; // hs010112 -1 = 11
		mob->MountFrontMeshId = 12; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Metal_Elemental_Dragon) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::dr02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 13; // hs010112 -1 = 11
		mob->MountFrontMeshId = 13; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Grifo_Negro) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::bd02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 1; // hs010112 -1 = 11
		mob->MountFrontMeshId = 1; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Grifo_Verde) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::bd02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 2; // hs010112 -1 = 11
		mob->MountFrontMeshId = 2; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Gargula_Vermelho) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::bd02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 3; // hs010112 -1 = 11
		mob->MountFrontMeshId = 3; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Gargula_Bege) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::bd02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 4; // hs010112 -1 = 11
		mob->MountFrontMeshId = 4; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Gargula_Flamejante) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::bd02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 5; // hs010112 -1 = 11
		mob->MountFrontMeshId = 5; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Gargula_Negro) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::bd02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 6; // hs010112 -1 = 11
		mob->MountFrontMeshId = 6; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}

	if (skinId == SkinId::Hipogrifo_Clestial) //index 22
	{
		// inicial do arquivo
		mob->MountInitialId = static_cast<short>(SkinInitialId::bd02); //tipo da montaria se é hs ou bg ..
		mob->MountBackMeshId = 7; // hs010112 -1 = 11
		mob->MountFrontMeshId = 7; // hs010112 - 1 = 11
		mob->MountSaddleMeshId = 0;

		mob->MountBackSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc = 12; //refinação equivalente a 120. (max 12)

		mob->MountBackSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountFrontSanc2 = 12; //refinação equivalente a 120. (max 12)
		mob->MountSaddleSanc2 = 12; //refinação equivalente a 120. (max 12)

		mob->fMountSize = 1.0f; //aqui é tamanho, .. 1.0f é padrão.
	}
}

bool SGrid_OnMouseMove_SkinName(char* pItemName, const STRUCT_ITEM* pItem)
{
	char trajesName[][50] = { "Arvak_Vermelho +DROP:10./'", "Arvak_Azul +DROP:10./'", "Arvak_Flamejante +DROP:10./'", "Arvak_Roxo +DROP:10./'", "Arvak_Metalico +DROP:10./'",
		"Deer +DROP:10./'", "Deer_Azul +DROP:10./'",  "Asvid_Vermelho +DROP:10./'", "Asvid_Azul +DROP:10./'", "Asvid_Metalico +DROP:10./'", "Bode_Branco +DROP:10./'", "Big_Horns +DROP:10./'",
		"Small_Horns +DROP:10./'", "White_Hair +DROP:10./'", "Raposa_Amarela +DROP:10./'","Raposa_Roxo +DROP:10./'", "Quimera_Flamejante +DROP:10./'", "Quimera_de_Madeira +DROP:10./'", "Quimera_Roxa +DROP:10./'",
		"Quimera_Verde +DROP:10./'", "Goat_Azul +DROP:10./'", "Goat_Vermelho +DROP:10./'", "Tigre_Negro +DROP:10./'", "Tigre_de_Gelo +DROP:10./'", "Tigre_Metalico +DROP:10./'", "Bola_de_Futebol +DROP:10./'",
		"Surkur +DROP:10./'" , "Coelho_Macabro +DROP:10./'" , "Pacman +DROP:10./'", "Dragão_Negro +DROP:10./'", "Dragão_Flamejante +DROP:10./'", "Dragão_de_Madeira +DROP:10./'", "Dragão_Metalico +DROP:10./'",
		"DV_Vermelho +DROP:10./'" , "DV_Azul +DROP:10./'" , "DV_Flamejante +DROP:10./'", "DV_Metalico +DROP:10./'", "Fire_Dragon +DROP:10./'", "Diamond_Dragon +DROP:10./'", "Metal_Dragon +DROP:10./'",
		"Fire_Elemental_Dragon +DROP:10./'", "Ice_Elemental_Dragon +DROP:10./'", "Metal_Elemental_Dragon +DROP:10./'",
		"Grifo_Negro +DROP:10./'" , "Grifo_Verde +DROP:10./'" , "Gargula_Vermelho +DROP:10./'", "Gargula_Bege +DROP:10./'", "Gargula_Flamejante +DROP:10./'", "Gargula_Negro +DROP:10./'", "Hipogrifo_Clestial +DROP:10./'" };

	size_t efv3 = pItem->stEffect[2].cValue - 11;
	int32_t index = efv3 - 11;

	if (efv3 >= 11 && efv3 < 12 + 50)
	{
		sprintf_s(pItemName, 64, "%s (Traje: %s)", (char*)(0x0FB9608 + 0x8C * pItem->sIndex), trajesName[index]);
		return true;
	}

	return false;
}