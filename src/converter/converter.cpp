//file:     converter.cpp
//author:   ntietz
//date:     2011.6.15
// Implementation of the converter class
#include "converter.hpp"

template <typename T>
chromosome converter<T>::toChromosome(sorter<T> algorithm) {
    chromosome result;
    sortType type = algorithm.getType();

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

    return result;
}

