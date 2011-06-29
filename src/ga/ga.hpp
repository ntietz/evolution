//file:     ga.hpp
//author:   ntietz
//date:     20111.6.27
// Specification of a genetic algorithm class.

#ifndef _GA_HPP_
#define _GA_HPP_

#include "../chromosome/chromosome.hpp"
#include "../../lib/SimpleRNG.h"
#include <vector>

typedef std::vector<Chromosome> Population;

class GeneticAlgorithm {
public:
    GeneticAlgorithm();

    GeneticAlgorithm* setChromosomeSize(int);
    GeneticAlgorithm* setPopulationSize(int);
    GeneticAlgorithm* setSelectionMechanism(Population (*)(Population*));


private:
    int chromosomeSize;
    int populationSize;

    Population population;

    Population* (*select)(Population*);
};

// pre-defined selection functions
Population* tournamentSelection(Population*);
Population* rouletteWheelSelection(Population*);
Population* stochasticUniversalSampling(Population*);


#endif
