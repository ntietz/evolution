//file:     datagentest.cpp
//author:   ntietz
//date:     2011.6.26
// Tests the datagen class.
#include "../../src/datagen/datagen.hpp"
#include <iostream>

int main() {

    DataGenerator gen;

    std::cout << "Random unsigned int: " << gen.getUnsignedInt() << std::endl;

    std::cout << "Random vector of unsigned ints:" << std::endl;
    std::vector<unsigned int> results = gen.getUnsignedIntVector(10);
    for (int index = 0; index < results.size() - 1; index++) {
        std::cout << results[index] << ", ";
    }
    std::cout << results[results.size() - 1] << std::endl;

}

