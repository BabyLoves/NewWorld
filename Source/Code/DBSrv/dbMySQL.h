#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <tchar.h>
#include <stdint.h>
#include <mysql.h>

#define CONSOLE 1

char *rcIP(unsigned int mIP);

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define PORT 3306
#define DB "wydsite"


#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "libmysql.lib")

#pragma warning (disable: 4514 4786 4996)
#include "../../Code/DBSrv/singleton.h"


#define DB_CREATE_ACCOUNT ""
#define DB_CREATE_CHAR "INSERT INTO `char` (`ID`, `Account`, `Slot`, `Nome`, `Online`, `Class`, `Evo`, `Reino`, `Level`, `Guild`, `gLevel`, `Fama`, `Moeda`, `Kill`, `Dead`, `AV`, `AD`, `AP`, `AK`, `MisCnt`, `MisPt`, `brV`, `brP`, `dOff`, `Contador`) VALUES	(NULL, '%s', '%d', '%s', '0' , '%d', '%d', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0')"
#define DB_UPDATE_CHAR "UPDATE `char` SET `Evo` = %d, `Level` = %d, `Guild` = %d, `Fama` = %d, `Online` = '0', `Reino` = %d, `gLevel` = %d, `Online` = %d WHERE `char`.`Nome` = '%s' AND `Slot` = %d"

extern int contador;

class cSQL : public Singleton<cSQL>
{
protected:
	friend class Singleton<cSQL>;
	cSQL() {}
	virtual ~cSQL() {}
	cSQL(const cSQL&) = delete;
	cSQL& operator=(const cSQL&) = delete;
public:
	static MYSQL *wStart();
	static MYSQL_RES *cSQL::wRes(MYSQL*sql, char* query);

	static bool wQuery(char* query);
	static char *wInfo(char* query);
	static void wLog(char* acc, char* pers, char* mensagem, char* type);

	static int cSQL::Cont(char* query);
	static int cSQL::iInfo(char* query);

};

extern	char xQuery[1000];
extern	char mQuery[1000];
extern	char hQuery[1000];
extern	char xMsg[1000];
extern	char xRow[400];
extern	char xMAC[400];
extern	char xIP[400];
extern	char *xPass;

class sql_s
{
public:
	MYSQL *wSQL;
	MYSQL_RES *result;
	MYSQL_ROW row;
};



uint32_t convert(const char* name);