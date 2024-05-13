#pragma once

#include "ProcessClientMessage.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <ctime>
#include "SendFunc.h"
#include "Functions.h"
#include "wMySQL.h"

void ReadServerConfigs()
{
	auto& pc = cSQL::instance();

	sprintf(hQuery, "SELECT * FROM `serverconfig` WHERE `id` = '%d'", 1);
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		EventStatus = atoi(row[1]);
		DOUBLEMODE = atoi(row[2]);
		AUTODOUBLE = atoi(row[3]);
		GlobalExp = atoi(row[4]);
		GTorreHour = atoi(row[5]);
		GTorreStatus = atoi(row[6]);
		RvRHour = atoi(row[7]);
		RvRStatus = atoi(row[8]);
		RvRBonus = atoi(row[9]);
		BatalhaRealStatus = atoi(row[10]);
		BatalhaRealHour = atoi(row[11]);
		PistaStatus = atoi(row[12]);
		EvolutionStatus = atoi(row[13]);
		PesaStatus = atoi(row[14]);
		PergaStatus = atoi(row[15]);
	}
}

void ReadExpTableN() {
	auto& pc = cSQL::instance();

	sprintf(hQuery, "SELECT * FROM `expbase` WHERE `id` = '%d'", 1);
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;
		
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		ExpBaseN[0] = atoi(row[1]);
		ExpBaseN[1] = atoi(row[2]);
		ExpBaseN[2] = atoi(row[3]);
		ExpBaseN[3] = atoi(row[4]);
		ExpBaseN[4] = atoi(row[5]);
		ExpBaseN[5] = atoi(row[6]);
		ExpBaseN[6] = atoi(row[7]);
		ExpBaseN[7] = atoi(row[8]);
		ExpBaseN[8] = atoi(row[9]);
		ExpBaseN[9] = atoi(row[10]);
		ExpBaseN[10] = atoi(row[11]);
		ExpBaseN[11] = atoi(row[12]);
	}
}
void ReadExpTableM() {
	auto& pc = cSQL::instance();

	sprintf(hQuery, "SELECT * FROM `expbase` WHERE `id` = '%d'", 2);
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		ExpBaseM[0] = atoi(row[1]);
		ExpBaseM[1] = atoi(row[2]);
		ExpBaseM[2] = atoi(row[3]);
		ExpBaseM[3] = atoi(row[4]);
		ExpBaseM[4] = atoi(row[5]);
		ExpBaseM[5] = atoi(row[6]);
		ExpBaseM[6] = atoi(row[7]);
		ExpBaseM[7] = atoi(row[8]);
		ExpBaseM[8] = atoi(row[9]);
		ExpBaseM[9] = atoi(row[10]);
		ExpBaseM[10] = atoi(row[11]);
		ExpBaseM[11] = atoi(row[12]);
	}
}