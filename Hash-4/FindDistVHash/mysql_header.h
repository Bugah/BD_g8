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
//#define RAIOMAX 0.025495

#define RAIOMAX 0.03
// Coloquei um valor privisório.

#endif

const double Raio2 = RAIOMAX * RAIOMAX;

/* Dados das tabelas */

const char* TABLE_NAME[] = {"VECTORS", "TABIMG"};

// const int NUMCOLS[] = {6,3};
const int NUMCOLS[] = {6,3};

const int ISTHEREKEY[] = {1,1};
const int WHOIS[] = {0,0};

const char  *tcol[][6] = 
{
    
{"int", "varchar (20000)","double","double","double","double"},
//{"int", "varchar (20000)"},                                     // Primeira Tabela : VECTORS
{"int","varchar(15)", "varchar(511)"}
};	

const char* tcol_ins[][6]  = {
{"int", "varchar","double", "double", "double", "double"},    // Primeira Tabela : VECTORS
//{"int", "varchar"},
{"int", "varchar", "varchar"}                                   // Segunda Tabela : TABIMG
};

const char* ncol[][7] = {
{"Id", "Coord","H1", "H2", "H3","H4"},                          // Primeira Tabela : VECTORS
//{"Id", "Coord"},
{"Id", "Nome", "Tags"}                                          // Segunda Tabela : TABIMG
};

/* Formato dos arquivos esperados */
const char* tags = ".tags";