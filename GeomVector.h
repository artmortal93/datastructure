//
// Created by steafan on 2020/2/27.
//

#ifndef DATASTRUCTURE_GEOMVECTOR_H
#define DATASTRUCTURE_GEOMVECTOR_H
#include "utils.h"
#include "array.hpp"

/*
class GeomVector {
protected:
    array<int> x;

public:
    unsigned hashCode() {
        long p = (1L<<32)-5;   // prime: 2^32 - 5
        long z = 0x64b6055aL;  // 32 bits from random.org
        int z2 = 0x5067d19d;   // random odd 32 bit number
        long s = 0;
        long zi = 1;
        for (int i = 0; i < x.length; i++) {
            // reduce to 31 bits
            long long xi = (hashCode(x[i]) * z2) >> 1;
            s = (s + zi * xi) % p;
            zi = (zi * z) % p;
        }
        s = (s + zi * (p-1)) % p;
        return (int)s;
    }
};
*/

#endif //DATASTRUCTURE_GEOMVECTOR_H
