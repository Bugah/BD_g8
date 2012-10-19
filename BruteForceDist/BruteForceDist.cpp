/* Standard C++ headers */
#include <iostream>
#include <cppconn/exception.h>
#include "mysql_header.h"
#include <iomanip>
#include <fstream>
#include <time.h>


#define K_HASH_A 22
// 21 pra arrumar o indice.
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
    void Heapfy();
    void Heapfy(int last);
    double valores[K_HASH_A];
public:
    int index [K_HASH_A];
    KMaxHash();
    void Attempt(double dist, int indice);
    void OrderHash();
    void PrintHash();
};

KMaxHash::KMaxHash() {
    int i;
    for(i=0;i<K_HASH_B;i=i+1) {
        valores[i]=10;                   // nesse contexto, 10 = inf
        index[i]=-1;                     // nesse contexto, -1 = invalido
    }
    
    // Adiciono um com distancia negativa ( - inf )
    // index -1 inválido
    valores[K_HASH_B]=-1;
    index[K_HASH_B]=-1;
}

void KMaxHash::Attempt(double dist, int indice) {
    if(valores[1]>dist) {
        valores[1]=dist;
        index[1]=indice;
        Heapfy();
        // HEAPFY : mudou, precisa heapfy!
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
        
        if(valores[l]>valores[f]) {
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


void KMaxHash::Heapfy(int last) {
    int l,r;            // left, righ
    int f=1;            // darth vader
    
    double d_swap;
    int i_swap;
    
    l=2;
    r=3;
    
    // Aqui, tendo um -inf, nao importa a possível comparaçao com o ultimo termo
    while (l<last) {
        if(r<last)
            if(valores[r]>valores[l])       // se o [r] é maior que [l]
                l=r;                        // substitui
        
        if(valores[l]>valores[f]) {
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
    int end = K_HASH_C;
    int i;
    
    double d_swap;
    int i_swap;
    
    for(i=1; i<K_HASH_C; i=i+1) {
        d_swap=valores[end];
        valores[end]=valores[1];
        valores[1]=d_swap;
        i_swap=index[end];
        index[end]=index[1];
        index[1]=i_swap;
        end=end-1;
        Heapfy(end);
    }
}


void KMaxHash::PrintHash() {
    int i;
    
    cout << endl;
    
        for(i=1; i<K_HASH_B; i=i+1)
            cout << index[i] << " : " << valores[i] << " " << endl;
    
    cout << endl;
    
}


class Vetorzao {
	public:
            void reset(string Coord);
            double coordenadas[1000];
            //Vetorzao(string Coord);
            double compararDistancia(Vetorzao Outro);
};

void Vetorzao::reset(string Coord) {
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

/*Vetorzao::Vetorzao (string Coord) {
    reset(Coord);
}*/	


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
	

double diffclock(clock_t clock1,clock_t clock2)
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