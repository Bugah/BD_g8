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
        	
	for(w=0; w<1000; w=w+1) {
            
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
	
	for(w=0; w<1000; w=w+1) {
		aux=coordenadas[w]-Outro.coordenadas[w];
		aux=aux*aux;
		sum=sum+aux;
	}
	
	return sum;
}


double Vetorzao::compararDistancia(Vetorzao Outro, double Max) {
	int w;
        int y;
        
	double sum=0;
	double aux=0;
        
        for(w=0; w<1000; w=w+1) {
                aux=coordenadas[w]-Outro.coordenadas[w];
		aux=aux*aux;
		sum=sum+aux;
                
            if(sum>Max) 
                w=1000;
            
	} 

	return sum;
}


void Vetorzao::distribution() {
    int dominios=10;
    int space = 1000/dominios;
    int it;
    double sum=0;
    
    cout << endl;
   
    for(it=0; it<1000; it=it+1) {
        sum=sum+coordenadas[it];
        
        if(((it+1)%space)==0) {
            sum=sum*100; // sum=(sum/1)*100;
            
            cout << "De " << ((it+1)/space)-1 << " Até " << (it+1)/space << " : " << sum << endl;
            sum=sum=0;
        }       
    }
}