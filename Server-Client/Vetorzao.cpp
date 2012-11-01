/* 
 * File:   Vetorzao.cpp
 * Author: alexandre
 * 
 * Created on October 19, 2012, 8:15 PM
 */

#include "Vetorzao.h"

Vetorzao::Vetorzao() {
}
 

void Vetorzao::reset(string Coord) {
    	int w;
	int vi=0;
	int term_a=0;
	char term[20];
        	
	for(w=0; w<SIZE; w=w+1) {
            
		while(Coord[vi]==' ') 
                    vi=vi+1;
			
		while(Coord[vi]!=' ') {
			term[term_a]=Coord[vi];
			term_a=term_a+1;
                        vi=vi+1;
		}
		
		term[term_a] = ' ';

		
		coordenadas[w] = atof(term);
		term_a=0;
	}
}


void Vetorzao::reset(string Coord, int ind) {
    indice=ind;
    reset(Coord);
}


void Vetorzao::resetNor(const char * myfile) {
    string initial;
    ifstream file_nor;				// descritor do arquivo
    string output;				// auxiliar de leitura
    
        
    file_nor.open(myfile, ios::out);
    file_nor >> output;
                    
    while (!file_nor.eof()) {
        initial.append(output);
        initial.append(" "); 
        file_nor >> output;
    }
    
    reset(initial);   
}


double Vetorzao::compararDistancia(Vetorzao Outro) {
	int w;
	double sum=0;
	double aux=0;
	
	for(w=0; w<SIZE; w=w+1) {
		aux=coordenadas[w]-Outro.coordenadas[w];
		aux=aux*aux;
		sum=sum+aux;
	}
	
	return sum;
}


// Calcula usando a euclidiana
double Vetorzao::compararDistancia(Vetorzao Outro, double Max) {
	int w;
        int y;
        
	double sum=0;
	double aux=0;
        
        for(w=0; w<SIZE; w=w+1) {
                aux=coordenadas[w]-Outro.coordenadas[w];
		aux=aux*aux;
		sum=sum+aux;
                
            if(sum>Max) 
                w=SIZE;
            
	} 

	return sum;
}


void Vetorzao::distribution() {
    int dominios=10;
    int space = 1000/dominios;
    int it;
    double sum=0;
    
    cout << endl;
   
    for(it=0; it<SIZE; it=it+1) {
        sum=sum+coordenadas[it];
        
        if(((it+1)%space)==0) {
            sum=sum*100; // sum=(sum/1)*100;
            
            cout << "De " << ((it+1)/space)-1 << " Até " << (it+1)/space << " : " << sum << endl;
            sum=sum=0;
        }       
    }
}


// Calcula todas as Distancias Euclidianas Normalizadas, devolve resultado no heap
double Vetorzao::normalized_Euclidean_distance(vector <Vetorzao> Outros, KMaxHeap * heapzim) {
    double x_barra_j[SIZE];
    double s_barra_j[SIZE];
    double zij;
    double zkj;
    double sum=0;
    
    int i;
    int j;
    
    for(i=0; i<SIZE; i=i+1) {
        x_barra_j[i]=0;
        s_barra_j[i]=0;
    }   
    
    // Obtem a media
    
    for(i=0; i<Outros.size(); i=i+1) {
        for(j=0; j<SIZE; j=j+1) 
            x_barra_j[j]=x_barra_j[j]+Outros[i].coordenadas[j];               
    }
    
    for(i=0; i<SIZE; i=i+1)
        x_barra_j[i]=x_barra_j[i]/1000;
    
        
    // Obtem o desvio padrao
   
    for(i=0; i<Outros.size(); i=i+1) {
        for(j=0; j<SIZE; j=j+1) 
            s_barra_j[j]=s_barra_j[j]+((Outros[i].coordenadas[j]-x_barra_j[j])*(Outros[i].coordenadas[j]-x_barra_j[j]));               
    }
    
    for(i=0; i<SIZE; i=i+1)
        s_barra_j[j]=sqrt(s_barra_j[j]/(Outros.size()-1));
    
    
    // Faz a soma de todos e armazena os melhores no Heap
    
    for(i=0; i<Outros.size(); i=i+1) {
        sum=0;
        for(j=0; j<SIZE; j=j+1) {
            zij=(coordenadas[j]-x_barra_j[j])/s_barra_j[j];
            zkj=(Outros[i].coordenadas[j]-x_barra_j[j])/s_barra_j[j];
            sum=sum+((zij-zkj)*(zij-zkj));
        }   
        sum=sqrt(sum);
        //cout << "Distance(id=" << Outros[i].indice << ") -> " << sum << endl;
        //heapzim.Attempt(sum, Outros[i].indice);
        (* heapzim).Attempt(sum, Outros[i].indice);
    }
    
    (* heapzim).OrderHash();
    (* heapzim).PrintHash();
}