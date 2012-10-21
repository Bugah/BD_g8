/* Standard C++ headers */
#include <iostream>
#include <cppconn/exception.h>
#include "mysql_header.h"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <time.h>
#include <math.h>
#include "Vetorzao.h"
#include "KMaxHash.h"

/* Namespaces necessarios */
using namespace std;
using namespace sql::mysql;	

double diffclock(clock_t clock1,clock_t clock2) // Calcular diferenca de tempo
{
	double diffticks=clock1-clock2;
	double diffms=(diffticks*1000)/CLOCKS_PER_SEC;
	return diffms;
} 


int main(int argc, const char *argv[]) {
// Sintaxe : ./App /folder/file.nor    
        
        clock_t begin=clock();
    
        int counter=0;
    
        int i;				// iterador
	string command="SELECT * FROM Vectors WHERE";
	
	ifstream file_nor;					// descritor do arquivo
	string output;						// auxiliar de leitura
	string initial;						// usado pra inicializar vetores .nor

	/* Variaveis de coneccao */
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
        
        double Distancia;
        int indice;
        
        Vetorzao Vet1;
        Vetorzao Vet2;
        Vetorzao Vet_Hash;
        
        KMaxHash MyHash;
        
        double d_hash;
        double min;
        double max;
	
	try {
		if(argc!=12) {
			cout << "Argumentos errados" << endl;
			return -1;
		}
		
		/* Aumenta precisão de impressão */
		cout << setprecision (15);

		/* Conecta com o DB */
		driver =sql::mysql::get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);
		/* Fim da coneccao ao schema definido no header */
		
                /* Abre o que se deseja comparar e inicializa */
		initial.clear();
		file_nor.open(argv[1], ios::out);
		file_nor >> output;
			
		while (!file_nor.eof()) {
			initial.append(output);
			initial.append(" "); 
			file_nor >> output;
		}
		
                Vet1.reset(initial);		
                /* Fim do Primeiro */
                
                for(i=2; i<argc; i=i+1) {
                    
                    //cout << endl << "argv[i]: " << argv[i] << endl;
                    
                    std::ostringstream os_min; 
                    std::ostringstream os_max; 
                    
                    string min_s;
                    string max_s;
                    
                    file_nor.close();
                    
                    initial.clear();
                    file_nor.open(argv[i], ios::out);
                    file_nor >> output;
                    
                    //cout << "abriu!" << endl;

                    while (!file_nor.eof()) {
                            initial.append(output);
                            initial.append(" "); 
                            file_nor >> output;
                    }

                    //cout << endl << initial << endl;
                    
                    Vet_Hash.reset(initial);
                    d_hash=sqrt(Vet_Hash.compararDistancia(Vet1));
                    
                    if(d_hash>RAIOMAX)
                        min=d_hash-RAIOMAX;
                    else 
                        min=RAIOMAX-d_hash;
                    
                    max=d_hash+RAIOMAX;
                    
                    //cout << endl <<      "Min e Max : " << min << max << endl;
                    
                    os_min << fixed << setprecision(15) << min;
                    min_s = os_min.str();
                                            
                    os_max << fixed << setprecision(15) << max;
                    max_s = os_max.str();
                    
                    //cout << endl << "Converteu! i:" << i << endl;
                    //cout << "ncol[0][i]" << ncol[1][i] << endl;
                    
                    command.append(" ");
                    command.append(ncol[0][i]);
                    command.append(">");
                    command.append(min_s);
                    command.append(" AND ");
                    command.append(ncol[0][i]);
                    command.append("<");
                    command.append(max_s);
                    
                    if(i!=(argc-1))
                        command.append(" AND");
                            // AND CONDICIONAL
                }  
                
                cout << endl << "command: " << command << endl;

		pstmt = con->prepareStatement(command);
		res = pstmt->executeQuery();

		while (res->next()) {
                    indice = res->getInt("Id");
                    initial = res->getString("Coord");
                    Vet2.reset(initial);
                    Distancia=Vet2.compararDistancia(Vet1);
                    //cout << "Index: " << indice << " -> " << Distancia << endl;
                    MyHash.Attempt(Distancia, indice);
                    counter = counter + 1;
		}
		
                MyHash.OrderHash();
                MyHash.PrintHash();
                
                //cout << endl << "Counter: " << counter << endl;
                
		//Vetorzao Vet2(initial);
		
		//Distancia = Vet2.compararDistancia(Vet1); 
		
	  	delete res;
	  	delete pstmt;
	  	delete con; 
                
                /* Calculo de tempo */
                clock_t end=clock();
                
                cout << endl << "counter: " << counter << endl;
                cout << "Time elapsedd: " << double(diffclock(end,begin)) << " ms"<< endl;
                
		
	} catch (sql::SQLException &e) {	// Para encontrar erros!
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;	
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
        
        
	return 0;
}