//file:     common.h
//author:   ntietz
//date:     2011.5.26
// Implements helper functions for the sorting algorithms.

#ifndef _COMMON_H_
#define _COMMON_H_

#include <random>
#include <iostream>

const int null = 0;

template<typename T>
void swap(T& left, T& right) {
    T temp = left;
    left = right;
    right = temp;
}

#endif
