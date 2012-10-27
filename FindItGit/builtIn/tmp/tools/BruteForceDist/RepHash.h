/* 
 * File:   RepHash.h
 * Author: alexandre
 *
 * Created on October 26, 2012, 1:33 AM
 */

#ifndef REPHASH_H
#define	REPHASH_H

#include <iostream>
#include <iomanip>

using namespace std;

class RepHash {
public:
    RepHash();
    virtual ~RepHash();
    bool Check(int term);
    void AddTerm(int term, int limite);
    void PrintHash();
private:
    int indice[2000];
};

#endif	/* REPHASH_H */

