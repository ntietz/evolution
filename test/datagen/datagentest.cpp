//file:     datagentest.cpp
//author:   ntietz
//date:     2011.6.26
// Tests the datagen class.
#include "../../src/datagen/datagen.hpp"
#include <iostream>

int main() {

    DataGenerator gen;
    std::cout << gen.getUnsignedInt() << std::endl;

}

