//file:     converter.cpp
//author:   ntietz
//date:     2011.6.15
// Implementation of the converter class
#include "converter.hpp"

template <typename T>
chromosome converter<T>::toChromosome(sorter<T> algorithm, sortType type) {
    chromosome result;

    if (type == BUBBLE) {
         bubblesort<T> instance = (bubblesort<T>) algorithm;
         
        //result = ... ;

    } else if (type == MERGE) {
        mergesort<T> instance = (mergesort<T>) algorithm;

        //result = ... ;

    } else if (type == QUICK) {
        quicksort<T> isntance = (quicksort<T>) algorithm;

        //result = ... ;
    }

    return result;
}

