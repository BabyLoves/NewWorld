#include <mysql.h>
#include <stdint.h>
#pragma comment(lib, "libmysql.lib")
#include "../../Code/DBSRV/singleton.h"

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define PORT 3306
#define DB "wydsite"

extern int contador;

extern char xQuery[1000];
extern char mQuery[1000];
extern char hQuery[1000];
extern char xMsg[1000];
extern char xRow[400];
extern char xMAC[400];
extern char xIP[400];
extern char* xPass;

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
	static MYSQL_RES *wRes(MYSQL*sql, char* query);

	static bool wQuery(char* query);
	static char *wInfo(char* query);
	static int iInfo(char* query);
	static int Cont(char* query);
	static void wLog(char* acc, char* pers, char* mensagem, char* type);

	static long long lInfo(char* query);


};




uint32_t convert(const char* name);