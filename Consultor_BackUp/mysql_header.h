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
#include <cppconn/exception.h>
 
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

/*  Mococa Hash V2	*/

//#define limite1 0.028
//#define limite2 0.061	// limite1 + RAIOMAX
 
// Coloquei um valor privisório.

#endif

/* Dados das tabelas */

const char* TABLE_NAME[] = {"VECTORS", "TABIMG"};

// const int NUMCOLS[] = {6,3};
const int NUMCOLS[] = {23,3};

const int ISTHEREKEY[] = {1,1};
const int WHOIS[] = {0,0};

const char  *tcol[][23] = 
{
{"int", "varchar (18000)","double","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int"},
{"int","varchar(15)", "varchar(511)"}
};	

const char* tcol_ins[][23]  = {
{"int", "varchar","double", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta", "inta"},    // Primeira Tabela : VECTORS
{"int", "varchar", "varchar"}                                   // Segunda Tabela : TABIMG
};

const char* ncol[][23] = {
{"Id", "Coord","H1", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10"},                          // Primeira Tabela : VECTORS
{"Id", "Nome", "Tags"}                                          // Segunda Tabela : TABIMG
};

/* Formato dos arquivos esperados */
const char* tags = ".tags";

const double limite1 = 0.053;
const double limite2 = 0.086;
