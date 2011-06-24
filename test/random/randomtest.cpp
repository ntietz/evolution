//file:     randomtest.cpp
//author:   ntietz
//date:     2011.6.23

#include "../../lib/SimpleRNG.h"
#include <iostream>

int main() {

    SimpleRNG rng;
    unsigned long int counts[100];
    for (int index = 0; index < 100; index++) {
        counts[index] = 0;
    }

    for (int index = 0; index < 10000; index++) {
        ++(counts[rng.GetUint() % 100]);
    }
    for (int index = 0; index < 100; index++) {
        std::cout << index << ": " << counts[index] << std::endl;
    }

}

