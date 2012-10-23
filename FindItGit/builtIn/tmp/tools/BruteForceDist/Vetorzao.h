/* 
 * File:   Vetorzao.h
 * Author: alexandre
 *
 * Created on October 19, 2012, 8:15 PM
 */

#ifndef VETORZAO_H
#define	VETORZAO_H
	
#include <string>
#include <stdlib.h>
using std::string;

class Vetorzao {
	public:
            void reset(string Coord);
            double coordenadas[1000];
            //Vetorzao(string Coord);
            double compararDistancia(Vetorzao Outro);
            Vetorzao();
};

#endif	/* VETORZAO_H */

