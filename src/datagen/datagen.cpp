//file:     datagen.cpp
//author:   ntietz
//date:     2011.6.25
// Implementation of a random data generator.

#include "datagen.hpp"

DataGenerator::DataGenerator() {
    rng = new SimpleRNG();
    
    std::ifstream seeder("/dev/urandom", std::ios::in | std::ios::binary);

    unsigned int seedA = 0;
    unsigned int seedB = 0;
    seeder.read((char*) &seedA, sizeof seedA);
    seeder.read((char*) &seedB, sizeof seedB);

    rng->SetState(seedA, seedB);

}

DataGenerator::DataGenerator(unsigned int seedA, unsigned int seedB) {
    rng = new SimpleRNG();
    rng->SetState(seedA, seedB);
}

unsigned int DataGenerator::getUnsignedInt() {
    return rng->GetUint();
}

std::vector<unsigned int> DataGenerator::getUnsignedIntVector(int size) {
    std::vector<unsigned int> results;

    for (int index = 0; index < size; index++) {
        results.push_back(rng->GetUint());
    }

    return results;
}

