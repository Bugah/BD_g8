/* Standard C++ headers */
#include <iostream>
#include <string.h>
//#include <vector>
#include <cppconn/exception.h>
#include "mysql_header.h"

/* Namespaces necessarios */
using namespace std;
using namespace sql::mysql;
using namespace sql;

int main(int argc, const char *argv[]) {
	int i;
	
	try {
	
		/* Variaveis de coneccao */
		sql::mysql::MySQL_Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		
		/* Conecta com o DB */
		driver =sql::mysql::get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);
		/* Fim da coneccao ao schema definido no header */
		
		/* String para criacao da insercao */
		string command="INSERT INTO ";
		command.append(TABLE_IMG);
		command.append(" VALUES (");
	
		/* Conversao para o formato MySql */
		if(argc>1) {
				if(!strcmp(tcol[0],"int"))
						command.append(argv[1]);
				else if(!strcmp(tcol[0],"varchar")) {
					 	command.append("'");
						command.append(argv[1]);
						command.append("'");
				}
		}
		
		for(i=2;i<argc; i++) {
	
					if(!strcmp(tcol[i-1],"int")) {
							command.append(", ");
							command.append(argv[i]);
						}
					else if(!strcmp(tcol[i-1],"varchar")) {
							command.append(", ");
						 	command.append("'");
							command.append(argv[i]);
							command.append("'");
					}
		}
		
		command.append(")");
		/* Fim da conversao */
		
		/* Debug */
		cout << command << endl;

		/* Finalmente insere */
		pstmt = con->prepareStatement(command);
		pstmt->executeUpdate();
		delete pstmt;
		
	} catch (sql::SQLException &e) {	// Para encontrar erros!
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;	
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	return 0;
}
