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

/*
    if (type == BUBBLE) {
         bubblesort<T> instance = (bubblesort<T>) algorithm;
         
        //no attributes to set

    } else if (type == MERGE) {
        mergesort<T> instance = (mergesort<T>) algorithm;

        std::vector<bool> bits;
        unsigned int max = UINT_MAX;
        int threshold = instance.getThreshold();

        while (max > 0) {
            bits.push_back(threshold % 2); // get the last bit
            max >>= 1;
        }

        //add secondary sort

    } else if (type == QUICK) {
        quicksort<T> instance = (quicksort<T>) algorithm;

        std::vector<bool> bits;
        unsigned int max = UINT_MAX;
        int threshold = instance.getThreshold();

        while (max > 0) {
            bits.push_back(threshold % 2); // get the last bit
            max >>= 1;
        }

        //add secondary sort
    } else {
        
        //add general case
        //should probably throw an error since this can never be legitimately entered

    }
*/
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

