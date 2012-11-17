/* 
 * File:   KMinHeap.cpp
 * Author: alexandre
 * 
 * Created on October 27, 2012, 11:04 PM
 */

#include "KMinHeap.h"


KMinHeap::KMinHeap() {
    int i;
    for(i=0;i<K_HASH_B;i=i+1) {
        valores[i]=-1;                   // nesse contexto, -1 = -inf
        index[i]=-1;                     // nesse contexto, -1 = invalido
    }
    
    // Adiciono um com distancia negativa ( + inf )
    // index -1 inválido, isso faz sobrar um termo no final do heap
    valores[K_HASH_B]=9999;
    index[K_HASH_B]=-1;
}

void KMinHeap::Attempt(double dist, int indice) {
    if(valores[1]<dist) {               // Se for menor que o maximo
        valores[1]=dist;                // ponto de interesse, trocar
        index[1]=indice;
        Heapfy();                       // e Heapfy
    }
}

void KMinHeap::Heapfy() {
    int l,r;            // left, righ
    int f=1;            // darth vader
    
    double d_swap;
    int i_swap;
    
    l=2;
    r=3;
    
    // Aqui, tendo um -inf, nao importa a possível comparaçao com o ultimo termo
    while (l<K_HASH_B) {
        if(valores[r]<valores[l])       // se o [r] é maior que [l]
            l=r;                        // substitui
        
        if(valores[l]<valores[f]) {     // ve se o maior filho eh maior que o pai
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


void KMinHeap::OrderHash() {    // Insertion Sort
    int i;
    int j;
    
    double d_swap;
    int i_swap;
    
    for(i=2; i<K_HASH_B; i=i+1) {
        for(j=i; j>1; j=j-1) {
            if(valores[j]<valores[j-1]) {
                i_swap=index[j];
                index[j]=index[j-1];
                index[j-1]=i_swap;
                d_swap=valores[j];
                valores[j]=valores[j-1];
                valores[j-1]=d_swap;
            }
            else {
                break;
            } 
        }
    }
}


void KMinHeap::PrintHash() {            // Apenas imprimi os indices e valores 
    int i;
    cout << endl;
    cout.fill('0');
        for(i=1; i<K_HASH_B; i=i+1) {
		if(index[i]!=-1)
			cout << setw(6) << index[i] << " : " << valores[i] << " " << endl;
        }   
    cout << endl;
    
}

void KMinHeap::PrintHashDebug() {            // Apenas imprimi os indices e valores 
    int i;
    cout << endl;
    cout.fill('0');
        for(i=1; i<K_HASH_B; i=i+1) {
			cout << setw(6) << index[i] << " : " << valores[i] << " " << endl;
        }   
    cout << endl;
    
}


double KMinHeap::GetHigher() {
    return valores[1];
}