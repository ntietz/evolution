//file:     converter.hpp
//author:   ntietz
//date:     2011.6.15
// Specification of a converter class used to convert between chromosomes and sorting algorithms

#ifndef _CONVERTER_HPP_
#define _CONVERTER_HPP_

#include <climits>

#include "../chromosome/chromosome.hpp"
#include "../sort.h"
#include "../all_sorts.h"

template <typename T>
class converter {
public:
    enum sortType { BUBBLE, MERGE, QUICK };

    chromosome toChromosome(sorter<T>, sortType);

private:

};

#endif

