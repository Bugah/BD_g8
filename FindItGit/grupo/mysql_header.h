#ifndef MYSQL_DEFINITIONS
#define MYSQL_DEFINITIONS

/* String */
#include <string>

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

/* Dados da tabela persons */
#define TABLE_IMG "persons"
#define NUMCOLS 5

#endif

const char* tcol[] = {"int", "varchar", "varchar", "varchar", "varchar"};