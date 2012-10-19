/* Standard C++ headers */
#include <iostream>
#include <cppconn/exception.h>
#include "mysql_header.h"
#include <iomanip>
#include <fstream>
#include <time.h>


#define K_HASH_A 22
// 22 pra arrumar o indice.
#define K_HASH_B 21
// evita uma comparação dentro do heapfy
// K_HASH_B = K_HASH_A - 1
#define K_HASH_C 20
// K_HASH_C = K_HASH_B - 1 = K_HASH_A - 2 = numero de termos

/* Namespaces necessarios */
using namespace std;
using namespace sql::mysql;

int isNor (string text);	

// Heap Magico de Max
class KMaxHash {
private:
    void Heapfy();                              // Heapfy a partir do 1 ate o 20          
    void Heapfy(int last);                      // Heapfy a partir do 1 ate o Last
    double valores[K_HASH_A];                   // Valores de cada indice
public:
    int index [K_HASH_A];                       // Indice das entradas do hash
    KMaxHash();                                 // Construtor do Hash, com entradas invalidas
    void Attempt(double dist, int indice);      // Tenta inserir um termo no hash
    void OrderHash();                           // Ordena o hash : Heapsort
    void PrintHash();                           // Imprimi do 1 ate o 20
};

KMaxHash::KMaxHash() {
    int i;
    for(i=0;i<K_HASH_B;i=i+1) {
        valores[i]=10;                   // nesse contexto, 10 = inf
        index[i]=-1;                     // nesse contexto, -1 = invalido
    }
    
    // Adiciono um com distancia negativa ( - inf )
    // index -1 inválido, isso faz sobrar um termo no final do heap
    valores[K_HASH_B]=-1;
    index[K_HASH_B]=-1;
}

void KMaxHash::Attempt(double dist, int indice) {
    if(valores[1]>dist) {               // Se for menor que o maximo
        valores[1]=dist;                // ponto de interesse, trocar
        index[1]=indice;
        Heapfy();                       // e Heapfy
    }
}

void KMaxHash::Heapfy() {
    int l,r;            // left, righ
    int f=1;            // darth vader
    
    double d_swap;
    int i_swap;
    
    l=2;
    r=3;
    
    // Aqui, tendo um -inf, nao importa a possível comparaçao com o ultimo termo
    while (l<K_HASH_B) {
        if(valores[r]>valores[l])       // se o [r] é maior que [l]
            l=r;                        // substitui
        
        if(valores[l]>valores[f]) {     // ve se o maior filho eh maior que o pai
            d_swap=valores[f];          // se for troca
            valores[f]=valores[l];
            valores[l]=d_swap;
            i_swap=index[f];
            index[f]=index[l];
            index[l]=i_swap;
            f=l;                        // e troca o pai
        }
        else                            // se nao for para
            break;
        
        l=2*f;          // calcula filhos
        r=l+1;
    }   
}


void KMaxHash::Heapfy(int last) {
    int l,r;            // left, righ
    int f=1;            // darth vader
    
    double d_swap;
    int i_swap;
    
    l=2;
    r=3;
    
    // Aqui, tendo um -inf, nao importa a possível comparaçao com o ultimo termo
    while (l<last) {
        if(r<last)                          // verifica-se se o filho direito estoura
            if(valores[r]>valores[l])       // se o [r] é maior que [l]
                l=r;                        // substitui
        
        if(valores[l]>valores[f]) {         // se o filho for maior, troca
            d_swap=valores[f];
            valores[f]=valores[l];
            valores[l]=d_swap;
            i_swap=index[f];
            index[f]=index[l];
            index[l]=i_swap;
            f=l;
        }
        else
            break;
        
        l=2*f;          // calcula filhos
        r=l+1;
    }   
}


void KMaxHash::OrderHash() {
    int end = K_HASH_C;                 // Heapsort
    int i;
    
    double d_swap;
    int i_swap;
    
    for(i=1; i<K_HASH_C; i=i+1) {      // Pega 20 termos e ordena (O(n))
        d_swap=valores[end];           // Troca o primeiro e o ultimo
        valores[end]=valores[1];
        valores[1]=d_swap;
        i_swap=index[end];
        index[end]=index[1];
        index[1]=i_swap;
        end=end-1;                      // Atualiza contador e heapfy
        Heapfy(end);                    // O(log n)
    }
}


void KMaxHash::PrintHash() {            // Apenas imprimi os indices e valores 
    int i;
    
    cout << endl;
    
        for(i=1; i<K_HASH_B; i=i+1)
            cout << index[i] << " : " << valores[i] << " " << endl;
    
    cout << endl;
    
}


class Vetorzao {                                        // Vetor que representa as 1000 dimensoes
	public:
            void reset(string Coord);                   // Reseta o vetor (ou cria)
            double coordenadas[1000];                   // Coordenadas
            double compararDistancia(Vetorzao Outro);   // Compara a distancia com outro vetor
};

void Vetorzao::reset(string Coord) {                    // Inicializa o vetor Coordenadas
    	int w;                                          // A partir de uma string
	int vi=0;
	int term_a=0;
	char term[20];
	
	for(w=0; w<1000; w=w+1) {
		
		while(Coord[vi]==' ')                   // Pula espacos
			vi=vi+1;
			
		while(Coord[vi]!=' ') {                 // Pega o termo double
			vi=vi+1;
			term[term_a]=Coord[vi];
			term_a=term_a+1;
		}
		
		term[term_a] = ' ';
		
		coordenadas[w] = atof(term);            // Convenrte para double
		term_a=0;
		
	}
}


double Vetorzao::compararDistancia(Vetorzao Outro) {
	int w;
	double sum=0;
	double aux=0;
	
	for(w=0; w<1000; w=w+1) {       // Para cada dimensao
		aux=coordenadas[w]-Outro.coordenadas[w];       
		aux=aux*aux;            // Subtrai uma da outra, eleva ao quadrado
		sum=sum+aux;            // E soma no total
	}
	
	return sum;                     // Note a falta de sqrt()
}
	

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
	string command="SELECT * FROM Vectors";
	
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
        
        KMaxHash MyHash;
	
	try {
		if(argc!=2) {
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
		
		initial.clear();
		file_nor.open(argv[1], ios::out);
		file_nor >> output;
			
		while (!file_nor.eof()) {
			initial.append(output);
			initial.append(" "); 
			file_nor >> output;
		}
		
                Vet1.reset(initial);		

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
                //MyHash.PrintHash();
                
                //cout << endl << "Counter: " << counter << endl;
                
		//Vetorzao Vet2(initial);
		
		//Distancia = Vet2.compararDistancia(Vet1);
		
	  	delete res;
	  	delete pstmt;
	  	delete con;
                delete &Vet1;
                delete &Vet2;
                delete &MyHash;
                
                /* Calculo de tempo */
                clock_t end=clock();
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