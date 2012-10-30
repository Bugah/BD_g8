/* 
 * File:   Relogio.h
 * Author: alexandre
 *
 * Created on October 25, 2012, 8:59 PM
 */

#ifndef RELOGIO_H
#define	RELOGIO_H

#include <time.h>

class Relogio {
    clock_t clock1;
    clock_t clock2;
public:
    Relogio();
    virtual ~Relogio();
    double diffclock();
    void reset();
private:

};

#endif	/* RELOGIO_H */

