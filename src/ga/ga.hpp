//file:     ga.hpp
//author:   ntietz
//date:     20111.6.27
// Specification of a genetic algorithm class.

#ifndef _GA_HPP_
#define _GA_HPP_

#include "../chromosome/chromosome.hpp"
#include <vector>

class GeneticAlgorithm {
public:
    GeneticAlgorithm();

    GeneticAlgorithm* setChromosomeSize(int);
    GeneticAlgorithm* setPopulationSize(int);

private:
    int chromosomeSize;
    int populationSize;
    

};

#endif
