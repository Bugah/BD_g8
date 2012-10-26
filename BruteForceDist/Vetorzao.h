/* 
 * File:   Vetorzao.h
 * Author: alexandre
 *
 * Created on October 19, 2012, 8:15 PM
 */

#ifndef VETORZAO_H
#define	VETORZAO_H
	
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Vetorzao {
	public:
            double coordenadas[1000];
            void reset(string Coord);
            void resetNor(const char * myfile);
            double compararDistancia(Vetorzao Outro);
            double compararDistancia(Vetorzao Outro, double Max);
            Vetorzao();
            void distribution();
};

#endif	/* VETORZAO_H */