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
//typedef int(*scorer)(Chromosome*);

class GeneticAlgorithm {
public:
    GeneticAlgorithm();

    GeneticAlgorithm* setChromosomeSize(unsigned int);
    GeneticAlgorithm* setPopulationSize(unsigned int);
    GeneticAlgorithm* setChildrenPopulationSize(unsigned int);
    GeneticAlgorithm* setSelectionMechanism(Population* (*)(Population*));
    GeneticAlgorithm* setFitnessFunction(int (*)(Chromosome*));
    GeneticAlgorithm* setGenerationFunction(Population* (*)(Population*, Population*));

    unsigned int getGenerationNumber();
    Population* getGeneration();
    
    void runGeneration();

protected:
    virtual Population* select(Population*) = 0;
    virtual Population* generate(Population*, Population*) = 0;
    virtual int fitness(Chromosome*) = 0;

    unsigned int generationNumber;

    unsigned int chromosomeSize;
    unsigned int populationSize;
    unsigned int childrenPopulationSize;

    Population population;

    DataGenerator* rng;
};

class TournamentSelection : virtual public GeneticAlgorithm {
protected:
    virtual Population* select(Population*);
};

class RouletteWheelSelection : virtual public GeneticAlgorithm {
protected:
    virtual Population* select(Population*);
};

// pre-defined selection functions
//Population* tournamentSelection(Population*, scorer);
//Population* rouletteWheelSelection(Population*, scorer);
//Population* stochasticUniversalSampling(Population*, scorer);

// pre-defined generation functions
Population* noElitism(Population*, Population*); //parents, children
Population* fullElitism(Population*, Population*);

#endif
