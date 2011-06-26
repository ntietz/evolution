//file:     datagen.cpp
//author:   ntietz
//date:     2011.6.25
// Implementation of a random data generator.

#include "datagen.hpp"

DataGenerator::DataGenerator() {
    rng = new SimpleRNG();
    
    std::ifstream seeder("/dev/urandom", std::ios::in | std::ios::binary);

    unsigned int seedA = 0;
    seeder.read((char*) &seedA, 4);
    unsigned int seedB = 0;

    rng->SetState(seedA, seedB);

}

DataGenerator::DataGenerator(unsigned int seedA, unsigned int seedB) {

}

