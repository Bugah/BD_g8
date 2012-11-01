/* 
 * File:   KMaxHash.h
 * Author: alexandre
 *
 * Created on October 20, 2012, 12:35 AM
 */

#ifndef KMAXHASH_H
#define	KMAXHASH_H



#define K_HASH_A 22
// 22 pra arrumar o indice.
#define K_HASH_B 21
// evita uma comparação dentro do heapfy
// K_HASH_B = K_HASH_A - 1
#define K_HASH_C 20
// K_HASH_C = K_HASH_B - 1 = K_HASH_A - 2 = numero de termos

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Heap Magico de Max
class KMaxHeap {
private:
    void Heapfy();                              // Heapfy a partir do 1 ate o 20          
    void Heapfy(int last);                      // Heapfy a partir do 1 ate o Last
public:
    double valores[K_HASH_A];                   // Valores de cada indice
    int index [K_HASH_A];                       // Indice das entradas do hash
    KMaxHeap();                                 // Construtor do Hash, com entradas invalidas
    void Attempt(double dist, int indice);      // Tenta inserir um termo no hash
    void OrderHash();                           // Ordena o hash : Heapsort
    void PrintHash();                           // Imprimi do 1 ate o 20
    double GetHigher();
    void Make_Answer(char answer[] );
    void Clear();
};

#endif	/* KMAXHASH_H */

