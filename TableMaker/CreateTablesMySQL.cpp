/* Standard C++ headers */
#include <iostream>
#include <cppconn/exception.h>
#include <sstream>
#include "mysql_header.h"

/* Namespaces necessarios */
using namespace std;
using namespace sql::mysql;

	
int main(int argc, const char *argv[]) {
	int i;							// iterador
	stringstream ValorString;		// auxiliar de conversao
	int table_index;				// index da table desejada
	
	try {
		
		ValorString << argv[1];		// conversao de char* para int
		ValorString >> table_index;
		
		if((table_index>LAST_TABLE)||(table_index<1)) {
			cout << "Tabela invalida, valor deve estar entre 1 e " << LAST_TABLE << endl;
			return -1;
		}
		
		table_index = table_index-1;	// Como o primeiro esta na posicao zero, corrige.
	
		/* Variaveis de coneccao */
		sql::mysql::MySQL_Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		
		/* Conecta com o DB */
		driver =sql::mysql::get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);
		/* Fim da coneccao ao schema definido no header */
		
		if(argc!=2) {
			cout << "Numero de parametros errado, formato esperado: ./CreateTablesMySQL k" << endl;
			cout << "Sendo k um natural diferente de zero que representa a tabela desejada" << endl;
			return -1;
		}
		
		/* Falta deletar a tabela */
		string delete_table = ("DROP TABLE IF EXISTS ");
		delete_table.append(TABLE_NAME[table_index]);
		stmt = con->createStatement();
		stmt->execute(delete_table);
		
		/* Degug */
		// cout << delete_table << endl;
		/* Fim Debug */
		
		/* String para criacao do databese */
		string command="CREATE TABLE ";
		command.append(TABLE_NAME[table_index]);
		command.append(" (");
	
		/* Conversao para o formato MySql */
		for(i=0;i<NUMCOLS[table_index]; i++) {
			command.append(ncol[table_index][i]);
			command.append(" ");
			command.append(tcol[table_index][i]);
			
			if ((ISTHEREKEY[table_index]==1)&&(WHOIS[table_index]==i)) 
				command.append(" NOT NULL");
				
			if(i!=(NUMCOLS[table_index]-1))
				command.append(", ");
		}
		
		if(ISTHEREKEY[table_index]==1) {
			command.append(", PRIMARY KEY (");
			command.append(ncol[table_index][WHOIS[table_index]]);
			command.append(") ");
		}
		
		
		
		command.append(")");
		/* Fim da conversao */
		
		/* Debug */
		 cout << command << endl;

		/* Finalmente cria tabela */
		stmt = con->createStatement();
		stmt->execute(command);
		delete stmt;
		/* Fim da criacao da tabela */
		
		
	} catch (sql::SQLException &e) {	// Para encontrar erros!
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;	
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	return 0;
}