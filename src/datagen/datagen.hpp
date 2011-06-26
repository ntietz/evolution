//file:     datagen.hpp
//author:   ntietz
//date:     2011.6.25
// Specification of a random data generator.

#ifndef _DATAGEN_HPP_
#define _DATAGEN_HPP_

#include "../../lib/SimpleRNG.h"
#include <fstream>

class DataGenerator {
public:
    DataGenerator();
    DataGenerator(unsigned int, unsigned int);

    unsigned int getUint() { return rng->GetUint(); }

private:
    SimpleRNG* rng;

};


#endif

