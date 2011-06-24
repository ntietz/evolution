//file:     randomtest.cpp
//author:   ntietz
//date:     2011.6.23

#include "../../src/random/random.hpp"
#include <iostream>

int main() {

    Random rng = new Random(0, 100);
    Random fng = new Random(0.0f, 100.0f);

    for (int index = 0; index < 20; index++) {
        std::cout << rng.nextInt() << "\t" << fng.nextFloat() << std::endl;
    }

}

