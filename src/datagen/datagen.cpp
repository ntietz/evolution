//file:     datagen.cpp
//author:   ntietz
//date:     2011.6.25
// Implementation of a random data generator.

#include "datagen.hpp"

DataGenerator::DataGenerator() {
    rng = new SimpleRNG();
    
    unsigned int seedA = 0;
    unsigned int seedB = 0;

    rng->SetState(seedA, seedB);

}

