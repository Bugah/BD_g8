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