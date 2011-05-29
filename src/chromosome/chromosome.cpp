//file:     chromosome.cpp
//author:   ntietz
//date:     2011.5.26
// Implementation of a chromosome

#include "chromosome.hpp"

chromosome::chromosome() {
    bits = null;
}

chromosome::chromosome(std::vector<bool> newBits) {
    bits = new std::vector<bool>(newBits);
}

