/* Standard C++ headers */
#include <iostream>
#include <cppconn/exception.h>
#include "mysql_header.h"
#include <vector>
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
    
	string command="SELECT * FROM Vectors"; // WHERE";

	/* Variaveis de coneccao */
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement *pstmt;
        sql::ResultSet *res;
       
        
        KMaxHeap MyHash;        // Hash que guarda os 20 melhores

        Vetorzao Vet1;          // Vetor1, guarda o .nor passado.
        Vetorzao Vet2;          // Auxiliar
        
        //double Distancia;       // Auxiliar pra calcular a distância
        int indice;             // Auxiliar pra ver qual indice do mysql        
        string initial;         // auxiliar pra carregar no mysql	
        int counter=0;          // contador de carregamentos
        
        std::vector <Vetorzao> vetores;
        
	try {
		/* Conecta com o DB */
		driver =sql::mysql::get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);
		/* Fim da coneccao ao schema definido no header */
                		
                Vet1.resetNor(argv[1]);            

		pstmt = con->prepareStatement(command);
		res = pstmt->executeQuery();
              
                
   		while (res->next()) {
                    initial = res->getString("Coord");  
                    indice = res->getInt("Id");
                
                    Vet2.reset(initial, indice);
                    vetores.push_back(Vet2);
		} 
                
                Vet1.normalized_Euclidean_distance(vetores, & MyHash);

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