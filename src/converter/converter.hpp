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
    
    chromosome toChromosome(sorter<T>);
    sorter<T> fromChromosome(chromosome);

private:

    std::vector<bool> toBits(int);
    std::vector<bool> appendBits(int, std::vector<bool>);

    int fromBits(std::vector<bool>, int, int);

};

#endif

