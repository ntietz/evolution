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

template < typename Fitness
         , typename Selection
         , template Survival
         , template Mutation
         , template Recombination
         >
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
    virtual Population* survive(Population*, Population*) = 0;

    virtual Chromosome* mutate(Chromosome*) = 0;
    virtual std::vector<Chromosome> recombine(std::vector<Chromosome>) = 0;

    virtual int fitness(Chromosome*) = 0;

    unsigned int generationNumber;

    unsigned int chromosomeSize;
    unsigned int populationSize;
    unsigned int childrenPopulationSize;

    Population population;

    DataGenerator* rng;
};

template <typename Fitness>
class KTournamentSelection {
public:
    KTournamentSelection(int tSize, int cpSize, DataGenerator* rng)
        : tournamentSize(tSize)
        , childrenPopulationSize(cpSize)
        , random(rng) {}

    Population operator()(const Population&) const;
private:
    int tournamentSize;
    int childrenPopulationSize;
    DataGenerator* random;
};
/*
class KTournamentSelection : virtual public GeneticAlgorithm {
protected:
    virtual Population* select(Population*);

    int tournamentSize;

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
*/
#endif

