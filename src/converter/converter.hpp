//file:     converter.hpp
//author:   ntietz
//date:     2011.6.15
// Specification of a Converter class used to convert between Chromosomes and sorting algorithms

#ifndef _CONVERTER_HPP_
#define _CONVERTER_HPP_

#include <climits>

#include "chromosome/chromosome.hpp"
#include "sort.h"
#include "all_sorts.h"

template <typename T>
class Converter {
public:
    
    Chromosome toChromosome(sorter<T>*);
    sorter<T> fromChromosome(Chromosome);

private:

    std::vector<bool> toBits(int);
    std::vector<bool> appendBits(int, std::vector<bool>);

    int fromBits(std::vector<bool>, int, int);

};

#include "converter.cpp"

#endif

