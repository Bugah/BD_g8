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
 
#endif /* MYSQL_DEFINITIONS */

#ifndef DATABASE_DEFINES
#define DATABASE_DEFINES

/* Dados do DB */	
#define DBHOST "tcp://127.0.0.1:3306"
#define USER "findIt"
#define PASSWORD "bd"
#define DATABASE "test"
#define LAST_TABLE 3

/* Raio a ser determinado */

#define RAIOMAX 0.033
#define RAIOMAX2 0.001089

// Coloquei um valor privisório.

#endif /* DATABASE_DEFINES */


/* Dados das tabelas */
const char* TABLE_NAME[] = {"VECTORS", "TABIMG", "IMG_TREINADA"};

const int NUMCOLS[] = {3,3,3};

const int ISTHEREKEY[] = {1,1,1};		// Tem chave
const int WHOIS[] = {0,0,0};			// Quais sao as Chaves

const char  *tcol[][3] = 
{
{"int", "varchar (18000)","double"},
{"int","varchar(15)", "varchar(511)"},
{"int","varchar(511)","int"}
};	

const char* tcol_ins[][3]  = {
{"int", "varchar","double"},  			// Primeira Tabela : VECTORS
{"int", "varchar", "varchar"},          // Segunda Tabela  : TABIMG
{"int", "varchar", "int"}				// Terceira Tabela : TAG_TREINADA
};

const char* ncol[][3] = {
{"Id", "Coord", "H1"},     			    // Primeira Tabela : VECTORS
{"Id", "Nome", "Tags"},     	        // Segunda Tabela  : TABIMG
{"Id", "Tag", "Contador"}				// Terceira Tabela : TAG_TREINADA
};

/* Formato dos arquivos esperados */
const char* tags = ".tags";
