#pragma once

#include "ProcessClientMessage.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <ctime>
#include "SendFunc.h"
#include "Functions.h"
#include "wMySQL.h"

using namespace std;

string gerar_senha() {
    const string caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int TAMANHO_SENHA = 5;
    string senha;

    // Inicializa o gerador de números aleatórios
    //srand(time(nullptr));

    // Gera a senha com caracteres aleatórios
    for (int i = 0; i < TAMANHO_SENHA; i++) {
        int indice_aleatorio = rand() % caracteres.length();
        senha += caracteres[indice_aleatorio];
    }

    return senha;
}

void GerarPix(int conn) {

    if (conn < 0 || conn > MAX_USER)
        return;

    auto& pc = cSQL::instance();
    std::string Senha = gerar_senha();
    std::string Pix;

    sprintf(hQuery, "SELECT * FROM `accounts` WHERE `pix` = '%s'", Senha.c_str());
    MYSQL_ROW row;
    MYSQL* wSQL = pc.wStart();
    MYSQL_RES* result = pc.wRes(wSQL, hQuery);

    if (result == NULL)
        return;

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        Pix = row[20];
    }

    if (Pix == "") {
        sprintf(xQuery, "UPDATE `accounts` SET pix = '%s' WHERE `username` = '%s' ", Senha.c_str(), pUser[conn].AccountName);
        pc.wQuery(xQuery);
    }
    else {
        SendClientMessage(conn, "Um erro ocorreu ao gerar sua chave pix");
        CloseUser(conn);
    }
}

