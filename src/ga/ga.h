//file:     ga.h
//author:   ntietz
//date:     20111.6.27
// Specification and immplementaiton of a generic genetic algorithm class.

#ifndef _GA_HPP_
#define _GA_HPP_

#include "../chromosome/chromosome.hpp"
#include "../datagen/datagen.hpp"
#include "../../lib/SimpleRNG.h"
#include "../pair/pair.h"
#include <vector>

typedef std::vector<Chromosome> Population;

// BASE CLASS

template < typename Fitness
         , typename Selection
         , typename Survival
         , typename Mutation
         , typename Recombination
         >
class GeneticAlgorithm {
public:
    GeneticAlgorithm(Fitness f, Selection se, Survival su, Mutation m, Recombination r)
    {
        // this seeds the rng from /dev/urandom
        rng = new DataGenerator();

        fitness = f;
        selection = se;
        survival = su;
        mutation = m;
        recombination = r;
    }

    GeneticAlgorithm& setChromosomeSize(unsigned int size) { chromosomeSize = size; return *this; }
    GeneticAlgorithm& setPopulationSize(unsigned int size) { populationSize = size; return *this; }
    GeneticAlgorithm& setChildrenPopulationSize(unsigned int size) { childrenPopulationSize = size; return *this; }
    GeneticAlgorithm& setMutationRate(double rate) { mutationRate = rate; return *this; }
    GeneticAlgorithm& setRecombinationRate(double rate) { recombinationRate = rate; return *this; }

    unsigned int getGenerationNumber() { return generationNumber; }
    
    void step();
    Population get();

protected:
    Fitness fitness;                //return: int,                    param: none
    Selection selection;            //return: population,             param: population
    Survival survival;              //return: population,             param: population, population
    Mutation mutation;              //return: chromosome,             param: chromosome
    Recombination recombination;    //return: chromosome, chromosome  param: pair<chromosome>

    unsigned int generationNumber;

    unsigned int chromosomeSize;
    unsigned int populationSize;
    unsigned int childrenPopulationSize;

    double mutationRate;
    double recombinationRate;

    Population population;

    DataGenerator* rng;
};



template < typename Fitness >
class KTournamentSelection {
public:
    KTournamentSelection(int tSize, int cpSize, DataGenerator* rng, Fitness fit)
        : tournamentSize(tSize)
        , childrenPopulationSize(cpSize)
        , random(rng)
        , fitness(fit) {}

    Population operator()(const Population& parentPopulation) const {
        int size = parentPopulation.size();
        int* scores = new int[size];

        for (int index = 0; index < size; ++index) {
            scores[index] = fitness(parentPopulation.at(index));
        }

        Population parents;

        while (parents.size() < childrenPopulationSize)  {

            Population candidates;
            for (int index = 0; index < tournamentSize; ++index) {
                candidates.push_back(parentPopulation.at(
                    random->getUnsignedInt() % parentPopulation.size() ));
            }

            int max = fitness(parents.at(0));
            int best = 0;
            
            for (int index = 1; index < parents.size(); ++index) {
                if (fitness(candidates.at(index)) > max) {
                    max = fitness(candidates.at(index));
                    best = index;
                }
            }

            parents.push_back(candidates.at(best));
        }

        delete [] scores;
        return parents;
    }

private:
    Fitness fitness;
    int tournamentSize;
    int childrenPopulationSize;
    DataGenerator* random;
};

template < typename Fitness > 
class RouletteWheelSelection {
public:
    RouletteWheelSelection(int cpSize, DataGenerator* rng, Fitness fit)
        : childrenPopulationSize(cpSize)
        , random(rng)
        , fitness(fit) {}

    Population operator()(const Population& parentPopulation) const {
        int size = parentPopulation.size();
        int* scores = new int[size];

        int total = 0;
        for (int index = 0; index < size; ++index) {
            total += fitness(parentPopulation.at(index));
            scores[index] = total;
        }

        Population parents;

        while (parents.size() < childrenPopulationSize) {
            unsigned int score = random->getUnsignedInt() % total;

            int index = 0;
            while (scores[index] < score) {
                ++index;
            }

            parents.push_back(parentPopulation.at(index));
        }

        delete [] scores;
        return parents;
    }

private:
    int childrenPopulationSize;
    DataGenerator* random;
    Fitness fitness;
};

class BitFlipMutate {
public:
    BitFlipMutate(double rate, DataGenerator* rng)
        : mutationRate(rate)
        , random(rng)
        { }

    Chromosome mutate(const Chromosome& actual) {
        Chromosome result = actual;

        for (int loc = 0; loc < result.size(); ++loc) {
            if (random->getDouble() < mutationRate) {
                result.set(loc, ! actual[loc]);
            } else {
                result.set(loc, actual[loc]);
            }
        }

        return result;
    }

private:
    double mutationRate;
    DataGenerator* random;
};

class BitSwapMutate {
public:
    BitSwapMutate(double rate, DataGenerator* rng)
        : mutationRate(rate)
        , random(rng)
        { }

    Chromosome mutate(const Chromosome& actual) {
        Chromosome result = actual;

        for (int loc = 0; loc < result.size(); ++loc) {
            if (random->getDouble() < mutationRate) {
                int other = random->getUnsignedInt() % (actual.size() - 2);
                if (other >= loc) ++other;
                
                result.set(loc, actual[other]);
                result.set(other, actual[loc]);
            }
        }

        return result;
    }

private:
    double mutationRate;
    DataGenerator* random;
};

class SinglePointCrossover {
public:
    SinglePointCrossover(DataGenerator* rng)
        : random(rng)
        { }

    Pair<Chromosome> recombine(const Chromosome& first, const Chromosome& second) {
        int splitPoint = random->getUnsignedInt() % (first.size() - 1);
        
        Pair<Chromosome> result;

        std::vector<Chromosome> firstParts = first.split(splitPoint);
        std::vector<Chromosome> secondParts = second.split(splitPoint);

        result.first = Chromosome().merge(firstParts[0], secondParts[1]);
        result.second = Chromosome().merge(secondParts[0], firstParts[1]);

        return result;
    }

private:
    DataGenerator* random;
};

class KPointCrossover {
public:
    KPointCrossover(std::vector<int> points, DataGenerator* rng)
        : splitPoints(points)
        , random(rng)
        { }

    Pair<Chromosome> recombine(const Chromosome& first, const Chromosome& second) {
        Pair<Chromosome> result;
        result.first = first;
        result.second = second;

        for (unsigned int index = 0; index < splitPoints.size(); index++) {
            recombineOnePoint(result.first, result.second, splitPoints[index]);
        }

        return result;
    }

private:
    std::vector<int> splitPoints;
    DataGenerator* random;

    // this relies on side effects to work but only within this class
    void recombineOnePoint(Chromosome& first, Chromosome& second, int point) {
        std::vector<Chromosome> firstParts = first.split(point);
        std::vector<Chromosome> secondParts = second.split(point);

        first = Chromosome().merge(firstParts[0], secondParts[1]);
        second = Chromosome().merge(secondParts[0], secondParts[1]);
    }
};

class UniformCrossover {
public:
    UniformCrossover(DataGenerator* rng)
        : random(rng)
        { }

    Pair<Chromosome> recombine(const Chromosome& first, const Chromosome& second) {
        Pair<Chromosome> result;
        result.first = first;
        result.second = second;

        for (int loc = 0; loc < first.size(); loc++) {
            double value = random->getDouble();

            if (value < 0.5) {
                result.first.set(loc, second[loc]);
                result.second.set(loc, first[loc]);
            }
        }

        return result;
    }

private:
    DataGenerator* random;
};

/*
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

