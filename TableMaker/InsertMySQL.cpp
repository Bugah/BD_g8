/* Standard C++ headers */
#include <iostream>
#include <fstream>
#include <sstream>
#include <cppconn/exception.h>
#include "mysql_header.h"

/* Namespaces necessarios */
using namespace std;
using namespace sql::mysql;

int isTag (string text);

int isNor (string text);

int main(int argc, const char *argv[]) {
	int i;								// auxiliar de iteracoes
	int norSize;						// auxiliar de .Nor (usado para obter o tamanho)
	stringstream ValorString;			// auxiliar de conversao
	int table_index;					// index da table desejada
	
	ifstream file_tags;					// descritor do arquivo
	string output;						// auxiliar de leitura
	
	/* Strings para criacao da insercao */
	string command="INSERT INTO ";		// guarda o comando
	string text;						// auxiliar para o caso de .tags

	/* Variaveis de coneccao */
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement *pstmt;
	
	try {
		ValorString << argv[1];			// conversao de char* para int
		ValorString >> table_index;
		table_index = table_index-1;
	
		/* Conecta com o DB */
		driver =sql::mysql::get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);
		/* Fim da coneccao ao schema definido no header */
		
		command.append(TABLE_NAME[table_index]);	
		command.append(" VALUES (");
		
		if(argc<3) {
			cout << "Erro, poucos parametros, formato esperado: ./InsertMySQL NumTable Arg1 Arg2 Arg3 ..." << endl;
			return -1;
		}

	
		/* Conversao para o formato MySql */
		if(argc>2) {
				if(!strcmp(tcol_ins[table_index][0],"int"))
						command.append(argv[2]);
				else if(!strcmp(tcol_ins[table_index][0],"varchar")) {
					 	command.append("'");
						command.append(argv[2]);
						command.append("'");
				}
		}
	
		
		// ignora a chamada, o numero da tabela e o primeiro argumento
		for(i=3;i<argc; i++) {
	
					if(!strcmp(tcol[table_index][i-2],"int")) {
							command.append(", ");
							command.append(argv[i]);
						}
					else if(!strcmp(tcol_ins[table_index][i-2],"varchar")) {
							text = argv[i];
							if(isTag(text)) {	// testa pra ver se é um arquivo
								file_tags.open(argv[i], ios::out);
								/* Se for, abri o arquivo e le as linhas */
								command.append(", ");
						 		command.append("'");
						
								file_tags >> output;
								
								while (!file_tags.eof()) {
									
									command.append(" ");
									command.append(output); 
									file_tags >> output;
								}
								
								command.append(" ");
								command.append("'");
								
							}	
							
							else if(isNor(text)) {	// verifica se eh um arquivo do tipo .nor

								file_tags.open(argv[i], ios::out);
								/* Se for, abri o arquivo e le a linha*/
								command.append(", ");
						 		command.append("'");
						
								file_tags >> output;
								
								while (!file_tags.eof()) {
									command.append(output);
									command.append(" "); 
									file_tags >> output;
								} 
								
								norSize = command.size();
								command.erase(norSize-3);	// remove 1 e espaco final
								command.append(" '");		// recoloca o espaco, pois facilita desmembrar em vetor
								
							}
							
							else {	// se nao for, coloca como parametro
								
								command.append(", ");
						 		command.append("'");
								command.append(argv[i]);
								command.append("'");
						}
					}
					
					else if(!strcmp(tcol_ins[table_index][i-2],"double")) {
						command.append(", ");
						command.append(argv[i]);
					}
		}
		
		command.append(")");
		/* Fim da conversao */
		
		/* Debug */
		//cout << command << endl;

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

/* 	Testa pra ver se um parametro do tipo varchar é um arquivo .tags 
 	Retorna 0 se nao for .tags e 1 se for */
int isTag (string text) {
	int i;
	int end;
	int j=4;
	
	if(text.size()<6)
		return 0;
	
	end =(int) text.size();
	
	for(i=end-1;i>end-5;i=i-1) {
		if(text[i]!=tags[j])
			return 0;
		j=j-1;
	}
	
	return 1;	// é um arquivo
}


/* 	Testa pra ver se um parametro do tipo varchar é um arquivo .nor
 	Retorna 0 se nao for .nor e 1 se for */
int isNor (string text) {
	
	int i;
	int end;
	int j=3;
	
	if(text.size()<5)
		return 0;
	
	end =(int) text.size();
	
	for(i=end-1;i>end-4;i=i-1) {
		if(text[i]!=nor[j])
			return 0;
		j=j-1;
	}
	
	return 1;	// é um arquivo
}