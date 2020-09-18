#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "mainHeader.h"

class Random {
public:
    Random() {
        srand(time(NULL));
    }
    int next(int a, int b) {
        int delta = b - a + 1;
        return a + rand() % delta;
    }
};

#endif