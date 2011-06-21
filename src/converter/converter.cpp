//file:     converter.cpp
//author:   ntietz
//date:     2011.6.15
// Implementation of the converter class
#include "converter.hpp"

template <typename T>
chromosome converter<T>::toChromosome(sorter<T> algorithm) {
    chromosome result;

    std::vector<bool> bits;

    bits = toBits(algorithm.getType());
    bits = appendBits(algorithm.getThreshold(), bits);
    bits = appendBits(algorithm.getSecondary().getType(), bits); //make sure this is tested

    if (algorithm.getType() == QUICK) {
        bits = appendBits(algorithm.getPivotMethod(), bits);
        bits = appendBits(algorithm.getNumAverage(), bits);
    } else {
        bits = appendBits(0, bits);
        bits = appendBits(0, bits);
    }

    if (algorithm.getType() == MERGE) {
        //attributes for mergesort...
    } else {

    }

    if (algorithm.getType() == BUBBLE) {
        //attributes for bubblesort...
    } else {

    }


    return result;
}

template<typename T>
sorter<T> converter<T>::fromChromosome(chromosome dna) {
    // TODO: implement function

    //..................


    return mergesort<T>();
};

template<typename T>
std::vector<bool> converter<T>::toBits(int number) {
    return appendBits(number, std::vector<bool>());
}

template<typename T>
std::vector<bool> converter<T>::appendBits(int number, std::vector<bool> original) {
    unsigned int max = UINT_MAX;

    while (max > 0) {
        original.push_back(number % 2);
        max = max / 2;
    }

    return original;
}

template<typename T>
int converter<T>::fromBits(std::vector<bool> bits, int start, int length) {

    int number = 0;

    for (int index = start + length - 1; index >= start; index++) {

        if (bits[index] == true) {
            number += 1;
        }

        number *= 2;
    }

    return number;
}

