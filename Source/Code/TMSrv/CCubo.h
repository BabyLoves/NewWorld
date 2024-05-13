/*
*   Copyright (C) {2015}  {Victor Klafke, Charles TheHouse}
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see [http://www.gnu.org/licenses/].
*
*   Contact at: victor.klafke@ecomp.ufsm.br
*/
#pragma once

#include <stdio.h>
#include "..\Basedef.h"

extern STRUCT_CUBOFILE CuboN;
extern STRUCT_CUBOFILE CuboM;
extern STRUCT_CUBOFILE CuboA;

class CCubo
{
private:
	static const char* const CUBO_QUEST_PATH;
	static const char* const CUBON_QUEST_PATH;
	static const char* const CUBOM_QUEST_PATH;
	static const char* const CUBOA_QUEST_PATH;
public:
	static void Initialize();

	static void MobKilled(int target, int conn, int PosX, int PosY);
	static void ProcessSecTimer();

	static bool LoadCubo();
	static bool LoadCuboCoordN();
	static bool LoadCuboCoordM();
	static bool LoadCuboCoordA();
};