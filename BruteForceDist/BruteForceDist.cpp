/* Standard C++ headers */
#include <iostream>
#include <cppconn/exception.h>
#include "mysql_header.h"
#include <iomanip>
#include <sstream>
#include <math.h>
#include "Vetorzao.h"
#include "KMaxHeap.h"
#include "Relogio.h"

/* Namespaces necessarios */
using namespace std;
using namespace sql::mysql;	

int main(int argc, const char *argv[]) {
// Sintaxe : ./App /folder/file.nor    
    
        Relogio relogio;                // Relogio
        relogio.reset();
    
        int i;				// iterador
	string command="SELECT * FROM Vectors WHERE";

	/* Variaveis de coneccao */
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement *pstmt;
        sql::ResultSet *res;
       
        double max;             // Marcam pontos de interesse em relacao ao hash  
        double minimo;  
        
        double d_hash;      
        KMaxHeap MyHash;        // Hash que guarda os 20 melhores

        Vetorzao Vet1;          // Vetor1, guarda o .nor passado.
        Vetorzao Vet2;          // Auxiliar
        
        double Distancia;       // Auxiliar pra calcular a distância
        int indice;             // Auxiliar pra ver qual indice do mysql        
        string initial;         // auxiliar pra carregar no mysql	
        int counter=0;          // contador de carregamentos
        
        
	try {
            
		//if(argc!=12) {
//			cout << "Argumentos errados" << endl;
//			return -1;
//		} 
		
		/* Aumenta precisão de impressão */
		cout << setprecision (15);

		/* Conecta com o DB */
		driver =sql::mysql::get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);
		/* Fim da coneccao ao schema definido no header */
                
		
                Vet1.resetNor(argv[1]);
                
 
                std::ostringstream os_min; 
                std::ostringstream os_max; 
                string min_s;
                string max_s;

                Vet2.resetNor(argv[2]);
                    
                d_hash=sqrt(Vet2.compararDistancia(Vet1));
                    
                if(d_hash>RAIOMAX)
                    minimo=d_hash-RAIOMAX;
                else 
                    minimo=RAIOMAX-d_hash;
                    
                max=d_hash+RAIOMAX;

                os_min << fixed << setprecision(15) << minimo;
                min_s = os_min.str();
                    
                os_max << fixed << setprecision(15) << max;
                max_s = os_max.str();
                   
                command.append(" ");
                command.append(ncol[0][2]);
                command.append(">");
                command.append(min_s);
                command.append(" AND ");
                command.append(ncol[0][2]);
                command.append("<");
                command.append(max_s);
                
                //cout << command << endl;

		pstmt = con->prepareStatement(command);
		res = pstmt->executeQuery();

                
   		while (res->next()) {
                    initial = res->getString("Coord");  

                    Vet2.reset(initial);
                    Distancia=sqrt(Vet2.compararDistancia(Vet1, MyHash.GetHigher()));

                    if(Distancia<=RAIOMAX) {
                        indice = res->getInt("Id");
                        MyHash.Attempt(Distancia, indice);
                    }
                        
                        counter = counter + 1;    
                    
		} 
                
                MyHash.OrderHash();
                MyHash.PrintHash();
                
                cout << endl << "counter_main: " << counter << endl;
                cout << "Time elapsedd: " << double(relogio.diffclock()) << " ms" << endl;
                
	  	delete res;
	  	delete pstmt;
	  	delete con; 
  
                
	} catch (sql::SQLException &e) {	// Para encontrar erros!
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;	
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
        
	return 0;
}