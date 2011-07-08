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

// BASE CLASS

class GeneticAlgorithm {
public:
    GeneticAlgorithm();

    GeneticAlgorithm* setChromosomeSize(unsigned int);
    GeneticAlgorithm* setPopulationSize(unsigned int);
    GeneticAlgorithm* setChildrenPopulationSize(unsigned int);

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

// SELECTION CLASSES

class KTournamentSelection : virtual public GeneticAlgorithm {
protected:
    virtual Population* select(Population*);

    int tournamentSize = 2;

    virtual int getTournamentSize();
    virtual int setTournamentSize();

};

class RouletteWheelSelection : virtual public GeneticAlgorithm {
protected:
    virtual Population* select(Population*);
};

class StochasticUniversalSampling : virtual public GeneticAlgorithm {
protected:
    virtual Population* select(Population*);
};

// GENERATION CLASSES
class NoElitism : virtual public GeneticAlgorithm {
protected:
    virtual Population* generate(Population*, Population*);
};

class FullElitism : virtual public GeneticAlgorithm {
protected:
    virtual Population* generate(Population*, Population*);
};

class Aging : virtual public GeneticAlgorithm {
protected:
    virtual Population* generate(Population*, Population*);
};

#endif

