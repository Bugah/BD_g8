/* Standard C++ headers */
#include <iostream>
#include <cppconn/exception.h>
#include "mysql_header.h"
#include <iomanip>
#include <fstream>

/* Namespaces necessarios */
using namespace std;
using namespace sql::mysql;

int isNor (string text);	

class Vetorzao {
	public:
		double coordenadas[1000];
		Vetorzao(string Coord);
		double compararDistancia(Vetorzao Outro);
};

Vetorzao::Vetorzao (string Coord) {
	int w;
	int vi=0;
	int term_a=0;
	char term[20];
	
	for(w=0; w<1000; w=w+1) {
		
		while(Coord[vi]==' ')
			vi=vi+1;
			
		while(Coord[vi]!=' ') {
			vi=vi+1;
			term[term_a]=Coord[vi];
			term_a=term_a+1;
		}
		
		term[term_a] = ' ';
		
		coordenadas[w] = atof(term);
		term_a=0;
		
		//cout << "Termo" << w << ": " << coordenadas[w] << endl;
	}
}	

double Vetorzao::compararDistancia(Vetorzao Outro) {
	int w;
	double sum=0;
	double aux=0;
	
	for(w=0; w<1000; w=w+1) {
		aux=coordenadas[w]-Outro.coordenadas[w];
		aux=aux*aux;
		sum=sum+aux;
	}
	
	return sum;
}
	

int main(int argc, const char *argv[]) {
/* 	Sintaxe ./CalcDist Arg1 Arg2	
	Se tratar-se de um arquivo.nor, carrega o arquivo.
	Se tratar-se de um inteiro, pega essa entrada no banco. 
*/
	
	int i;				// iterador
	int arg1_t;			// indica se arg1 for NOR
	int arg2_t;			// indica se arg2 for NOR
	string command="SELECT Coord FROM Vectors WHERE id =";
	string find_type;	// auxiliar para verificar .NOR ou nao
	
	ifstream file_nor;					// descritor do arquivo
	ifstream file_nor2;					// descritor do arquivo
	string output;						// auxiliar de leitura
	string initial;						// usado pra inicializar vetores .nor
	
	
	/* Variaveis de coneccao */
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	
	try {
		if(argc!=3) {
			cout << "Argumentos errados" << endl;
			return -1;
		}
		
		/* Aumenta precisão de impressão */
		cout << setprecision (15);
		
		find_type.clear();
		find_type.append(argv[1]);
		arg1_t=isNor(find_type);
		
		find_type.clear();
		find_type.append(argv[2]);
		arg2_t=isNor(find_type);
		
		// Se ambos nao forem .NOR
		if(!((arg1_t==1)&&(arg2_t==1))) {
			/* Conecta com o DB */
			driver =sql::mysql::get_driver_instance();
			con = driver->connect(DBHOST, USER, PASSWORD);
			con->setSchema(DATABASE);
			/* Fim da coneccao ao schema definido no header */
		}
		
		// Se arg1 for .NOR
		if(arg1_t==1) {
			initial.clear();
			file_nor.open(argv[1], ios::out);
			file_nor >> output;
			
			while (!file_nor.eof()) {
				initial.append(output);
				initial.append(" "); 
				file_nor >> output;
			}
		}
		
		// Se arg1 nao for .NOR
		else {
			command.append(argv[1]);
			
			//cout << "1 " << command << endl;
			
			pstmt = con->prepareStatement(command);
			res = pstmt->executeQuery();

			if (!(res->next())) {
				cout << "Id nao esta na tabela VECTOR" << endl;
				return -1;
			}
		
	    	//cout << "String Coord: " << res->getString("Coord") << endl;
		
			initial.clear();
			initial.append(res->getString("Coord"));
		}
		
		Vetorzao Vet1(initial);
		
		// Se arg2 for .NOR
		if(arg2_t==1) {
			initial.clear();
			file_nor2.open(argv[2], ios::out);
			file_nor2 >> output;
			
			while (!file_nor2.eof()) {
				initial.append(output);
				initial.append(" "); 
				file_nor2 >> output;
			}
		}
		
		// Se arg2 nao for .NOR
		else {
			command.clear();
			command.append("SELECT Coord FROM Vectors WHERE id =");
			command.append(argv[2]);
			
			//cout << command << endl;
			
			pstmt = con->prepareStatement(command);
			res = pstmt->executeQuery();

			if (!(res->next())) {
				cout << "Id nao esta na tabela VECTOR" << endl;
				return -1;
			}
		
	    	//cout << "String Coord: " << res->getString("Coord") << endl;
		
			initial.clear();
			initial.append(res->getString("Coord"));
		}
		
		// cout << "Testing initial :" << endl << initial << endl;
		Vetorzao Vet2(initial);
		
		double Distancia = Vet2.compararDistancia(Vet1);
		
		cout << "Distancia: " << Distancia << endl;

		if(!((arg1_t==1)&&(arg2_t==1))) {
	  		delete res;
	  		delete pstmt;
	  		delete con;
		}	
		
	} catch (sql::SQLException &e) {	// Para encontrar erros!
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;	
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	return 0;
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















