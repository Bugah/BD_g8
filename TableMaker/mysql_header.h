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
#define LAST_TABLE 2

/* Raio a ser determinado */

#define RAIOMAX 0.033
#define RAIOMAX2 0.001089

// Coloquei um valor privisório.

#endif

/* Dados das tabelas */

const char* TABLE_NAME[] = {"VECTORS", "TABIMG"};

// const int NUMCOLS[] = {6,3};
const int NUMCOLS[] = {3,3};

const int ISTHEREKEY[] = {1,1};
const int WHOIS[] = {0,0};

const char  *tcol[][3] = 
{
{"int", "varchar (18000)","double"},
{"int","varchar(15)", "varchar(511)"}
};	

const char* tcol_ins[][3]  = {
{"int", "varchar","double"},    // Primeira Tabela : VECTORS
{"int", "varchar", "varchar"}                                   // Segunda Tabela : TABIMG
};

const char* ncol[][3] = {
{"Id", "Coord", "H1"},                          // Primeira Tabela : VECTORS
{"Id", "Nome", "Tags"}                                          // Segunda Tabela : TABIMG
};

/* Formato dos arquivos esperados */
const char* tags = ".tags";