/* 
 * File:   Vetorzao.h
 * Author: alexandre
 *
 * Created on October 19, 2012, 8:15 PM
 */

#ifndef VETORZAO_H
#define	VETORZAO_H
	
#define SIZE 1000

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "KMaxHeap.h"

using namespace std;

class Vetorzao {
	public:
            int indice;
            double coordenadas[SIZE];
            void reset(string Coord);
            void reset(string Coord, int ind);
            void resetNor(const char * myfile);
            double compararDistancia(Vetorzao Outro);
            double compararDistancia(Vetorzao Outro, double Max);
            Vetorzao();
            double normalized_Euclidean_distance(vector <Vetorzao> Outros, KMaxHeap * heapzim);
            void distribution();
};

#endif	/* VETORZAO_H */