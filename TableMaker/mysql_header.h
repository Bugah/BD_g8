#ifndef MYSQL_DEFINITIONS
#define MYSQL_DEFINITIONS

/* String */
#include <string.h>

/* MySQL Connector/C++ specific headers */
#include <mysql_driver.h> 
#include "mysql_connection.h"

/* cppconn/ */
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
 
#endif

#ifndef DATABASE_DEFINES
#define DATABASE_DEFINES

/* Dados do DB */	
#define DBHOST "tcp://127.0.0.1:3306"
#define USER "root"
#define PASSWORD ""
#define DATABASE "test"
#define LAST_TABLE 3

#endif

/* Dados das tabelas */

const char* TABLE_NAME[] = {"VECTORS", "TABIMG", "SEARCHTABLE"};
const int NUMCOLS[] = {2,3,4};
const int ISTHEREKEY[] = {1,1,1};
const int WHOIS[] = {0,0,0};

const char  *tcol[][4] = 
{
{"int", "varchar (20000)"},					// Primeira Tabela : VECTORS
{"int","varchar(15)", "varchar(511)"},		// Segunda Tabela : TABIMG
{"int", "double", "double", "double"}
}	;	

const char* tcol_ins[][4]  = {
{"int", "varchar"},							// Primeira Tabela : VECTORS
{"int", "varchar", "varchar"},				// Segunda Tabela : TABIMG
{"int", "double", "double", "double"}
};

const char* ncol[][4] = {
{"Id", "Coord"},							// Primeira Tabela : VECTORS
{"Id", "Nome", "Tags"},						// Segunda Tabela : TABIMG
{"Id", "D1", "D2", "D3"}
};

/* Formato dos arquivos esperados */
const char* tags = ".tags";
const char* nor = ".nor";