//file:     ga.hpp
//author:   ntietz
//date:     20111.6.27
// Specification of a genetic algorithm class.

#ifndef _GA_HPP_
#define _GA_HPP_

#include "../chromosome/chromosome.hpp"
#include "../datagen/datagen.hpp"
#include "../../lib/SimpleRNG.h"
#include <vector>

typedef std::vector<Chromosome> Population;
typedef int(*scorer)(Chromosome*);

class GeneticAlgorithm {
public:
    GeneticAlgorithm();

    GeneticAlgorithm* setChromosomeSize(unsigned int);
    GeneticAlgorithm* setPopulationSize(unsigned int);
    GeneticAlgorithm* setChildrenPopulationSize(unsigned int);
    GeneticAlgorithm* setSelectionMechanism(Population* (*)(Population*, scorer));
    GeneticAlgorithm* setFitnessFunction(int (*)(Chromosome*));
    GeneticAlgorithm* setGenerationFunction(Population* (*)(Population*, Population*, scorer));

    unsigned int getGenerationNumber();
    Population* getGeneration();
    
    void runGeneration();

private:
    // helper functions
    Population* (*selector)(Population*, scorer);
    Population* (*generator)(Population*, Population*, scorer);
    scorer fitness;

    unsigned int generationNumber;

    unsigned int chromosomeSize;
    unsigned int populationSize;
    unsigned int childrenPopulationSize;

    Population population;

    DataGenerator* rng;
};

// pre-defined selection functions
Population* tournamentSelection(Population*, scorer);
Population* rouletteWheelSelection(Population*, scorer);
Population* stochasticUniversalSampling(Population*, scorer);

// pre-defined generation functions
Population* noElitism(Population*, Population*); //parents, children
Population* fullElitism(Population*, Population*);

#endif
