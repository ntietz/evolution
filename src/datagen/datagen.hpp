//file:     datagen.hpp
//author:   ntietz
//date:     2011.6.25
// Specification of a random data generator.

#ifndef _DATAGEN_HPP_
#define _DATAGEN_HPP_

#include "../../lib/SimpleRNG.h"

class DataGenerator {
public:
    DataGenerator();

private:
    SimpleRNG* rng;

};


#endif

