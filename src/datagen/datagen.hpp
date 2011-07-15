//file:     datagen.hpp
//author:   ntietz
//date:     2011.6.25
// Specification of a random data generator.

#ifndef _DATAGEN_HPP_
#define _DATAGEN_HPP_

#include "../../lib/SimpleRNG.h"
#include <fstream>
#include <vector>

class DataGenerator {
public:
    DataGenerator();
    DataGenerator(unsigned int, unsigned int);

    unsigned int getUnsignedInt();
    double getDouble();

    std::vector<unsigned int> getUnsignedIntVector(int);

private:
    SimpleRNG* rng;

};


#endif

