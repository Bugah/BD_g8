/* 
 * File:   Relogio.cpp
 * Author: alexandre
 * 
 * Created on October 25, 2012, 8:59 PM
 */

#include "Relogio.h"

Relogio::Relogio() {
    clock1=clock();
}

Relogio::~Relogio() {
}

void Relogio::reset(){
    clock1=clock();
}

double Relogio::diffclock() // Calcular diferenca de tempo
{
    clock2=clock();
    double diffticks=clock2-clock1;
    double diffms=(diffticks*1000)/CLOCKS_PER_SEC;
    return diffms;
}