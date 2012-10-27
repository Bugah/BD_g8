/* 
 * File:   RepHash.cpp
 * Author: alexandre
 * 
 * Created on October 26, 2012, 1:33 AM
 */

#include "RepHash.h"

RepHash::RepHash() {
    int i=0;
    
    for(i=0;i<2000; i=i+1)
        indice[i]=0;
}


RepHash::~RepHash() {
}


// Adiciona se for possível ou se o valor que estiver lá já nao importar
void RepHash::AddTerm(int term, int limite) {
    int pos;
    int aux;
    
    aux=term%1000;
    pos=term/1000;
    pos=(pos%2)*1000;
    pos=pos+aux;
        
    if((indice[pos]==0)||(indice[pos]>=limite))
            indice[pos]=term;
}

// Devolve      TRUE se estiver lá.
//              FALSE se nao tiver.
bool RepHash::Check(int term) {
    int pos;
    int aux;
    
    aux=term%1000;
    pos=term/1000;
    pos=(pos%2)*1000;
    pos=pos+aux;
    
    if(indice[pos]==term)
        return true;
    
    return false;
}

void RepHash::PrintHash() {
    int j;
    
//    cout.fill('0');
    for(j=0;j<2000;j=j+1) {
        cout <<  indice[j] << " ";
        if(j%10==0)
            cout << endl;
    }
}
