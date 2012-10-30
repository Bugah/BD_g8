/* 
 * File:   KMinHeap.h
 * Author: alexandre
 *
 * Created on October 27, 2012, 11:04 PM
 */

#ifndef KMINHEAP_H
#define	KMINHEAP_H

#define K_HASH_A 22
// 22 pra arrumar o indice.
#define K_HASH_B 21
// evita uma comparação dentro do heapfy
// K_HASH_B = K_HASH_A - 1
#define K_HASH_C 20
// K_HASH_C = K_HASH_B - 1 = K_HASH_A - 2 = numero de termos

#include <iostream>
#include <iomanip>

using namespace std;

// Heap Magico de Max
class KMinHeap {
private:
    void Heapfy();                              // Heapfy a partir do 1 ate o 20
public:
    double valores[K_HASH_A];                   // Valores de cada indice
    int index [K_HASH_A];                       // Indice das entradas do hash
    KMinHeap();                                 // Construtor do Hash, com entradas invalidas
    void Attempt(double dist, int indice);      // Tenta inserir um termo no hash
    void OrderHash();                           // Ordena o hash : Heapsort
    void PrintHash();                           // Imprimi do 1 ate o 20
    void PrintHashDebug();
    double GetHigher();
};

#endif	/* KMINHEAP_H */

