/* 
 * File:   KMaxHash.cpp
 * Author: alexandre
 * 
 * Created on October 20, 2012, 12:35 AM
 */

#include "KMaxHeap.h"

KMaxHeap::KMaxHeap() {
    int i;
    for(i=0;i<K_HASH_B;i=i+1) {
        valores[i]=10;                   // nesse contexto, 10 = inf
        index[i]=-1;                     // nesse contexto, -1 = invalido
    }
    
    // Adiciono um com distancia negativa ( - inf )
    // index -1 inválido, isso faz sobrar um termo no final do heap
    valores[K_HASH_B]=-1;
    index[K_HASH_B]=-1;
}

void KMaxHeap::Attempt(double dist, int indice) {
    if(valores[1]>dist) {               // Se for menor que o maximo
        valores[1]=dist;                // ponto de interesse, trocar
        index[1]=indice;
        Heapfy();                       // e Heapfy
    }
}

void KMaxHeap::Heapfy() {
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
        
        if(valores[l]>valores[f]) {     // ve se o maior filho eh maior que o pai
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


void KMaxHeap::Heapfy(int last) {
    int l,r;            // left, righ
    int f=1;            // darth vader
    
    double d_swap;
    int i_swap;
    
    l=2;
    r=3;
    
    // Aqui, tendo um -inf, nao importa a possível comparaçao com o ultimo termo
    while (l<=last) {
        if(r<=last)                          // verifica-se se o filho direito estoura
            if(valores[r]>valores[l])       // se o [r] é maior que [l]
                l=r;                        // substitui
        
        if(valores[l]>valores[f]) {         // se o filho for maior, troca
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


void KMaxHeap::OrderHash() {
    int end = K_HASH_C;                 // Heapsort
    int i;
    
    double d_swap;
    int i_swap;
    
    for(i=1; i<K_HASH_C; i=i+1) {      // Pega 20 termos e ordena (O(n)
        
        d_swap=valores[end];           // Troca o primeiro e o ultimo
        valores[end]=valores[1];
        valores[1]=d_swap;
        i_swap=index[end];
        index[end]=index[1];
        index[1]=i_swap;
        end=end-1;                      // Atualiza contador e heapfy
        
        Heapfy(end);                    // O(log n)
    }
}


void KMaxHeap::PrintHash() {            // Apenas imprimi os indices e valores 
    int i;
    cout << endl;
    cout.fill('0');
        for(i=1; i<K_HASH_B; i=i+1) {
            cout << setw(6) << index[i] << " : " << valores[i] << " " << endl;
        }   
    cout << endl;
    
}


double KMaxHeap::GetHigher() {
    return valores[1];
}
