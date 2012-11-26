//file:     ga.h
//author:   ntietz
//date:     2011.6.27
// Specification and implementation of a generic genetic algorithm class.

#ifndef _GA_HPP_
#define _GA_HPP_

#include "chromosome/chromosome.hpp"
#include "datagen/datagen.hpp"
#include "SimpleRNG.h"
#include "pair/pair.h"
#include <vector>
#include <iostream>
#include <functional>

static auto gaRNG = new DataGenerator();

typedef std::vector<Chromosome> Population;

Chromosome getRandomChromosome(int);
Chromosome getRandomChromosome(int, DataGenerator*);

Chromosome getRandomChromosome(int length) {
    DataGenerator* rng = new DataGenerator();
    return getRandomChromosome(length, rng);
}

Chromosome getRandomChromosome(int length, DataGenerator* rng) {
    std::vector<bool> bits(length);

    for (int index = 0; index < length; ++index) {
        if (rng->getUnsignedInt() % 2 == 0) {
            bits[index] = true;
        } else {
            bits[index] = false;
        }
    }

    return Chromosome(bits);
}

typedef std::function<float(const Chromosome&)> FitnessFunction;
typedef std::function<Population(const Population&)> SelectionFunction;
typedef std::function<Population(const Population&, const Population&)> SurvivalFunction;
typedef std::function<Chromosome(const Chromosome&)> MutationFunction;
typedef std::function<Pair<Chromosome>(const Chromosome&, const Chromosome&)> RecombinationFunction;

class GeneticAlgorithm
{
  public:
    GeneticAlgorithm( const FitnessFunction& f
                    , const SelectionFunction& se
                    , const SurvivalFunction& su
                    , const MutationFunction& m
                    , const RecombinationFunction& r
                    )
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
    GeneticAlgorithm& setRng(DataGenerator* random) { rng = random; return *this; }

    unsigned int getGenerationNumber() { return generationNumber; }
    
    void init();
    void step();
    Population get() const { return population; }

  protected:
    FitnessFunction fitness;
    SelectionFunction selection;
    SurvivalFunction survival;
    MutationFunction mutation;
    RecombinationFunction recombination;

    unsigned int generationNumber;

    unsigned int chromosomeSize;
    unsigned int populationSize;
    unsigned int childrenPopulationSize;

    double mutationRate;
    double recombinationRate;

    Population population;

    DataGenerator* rng;
};

/*
template < typename Fitness
         , typename Selection
         , typename Survival
         , typename Mutation
         , typename Recombination
         >
void GeneticAlgorithm<Fitness, Selection, Survival, Mutation, Recombination>::init()
{
    population.resize(populationSize);

    for (int index = 0; index < populationSize; ++index)
    {
        population[index] = getRandomChromosome(chromosomeSize);
    }
}

template < typename Fitness
         , typename Selection
         , typename Survival
         , typename Mutation
         , typename Recombination
         >
void GeneticAlgorithm<Fitness, Selection, Survival, Mutation, Recombination>::step()
{
    Population parents = selection(population);
    
    Population children;
    for (int index = 0; children.size() < childrenPopulationSize; ++index)
    {
        double value = rng->getDouble();
        
        if (value < recombinationRate)
        {
            Pair<Chromosome> twins = recombination(parents[index], parents[index + 1]);
            children.push_back(twins.first);
            children.push_back(twins.second);
        }
        else
        {
            children.push_back(parents[index]);
            children.push_back(parents[index+1]);
        }
    }

    for (int index = 0; index < childrenPopulationSize; ++index)
    {
        children[index] = mutation(children[index]);
    }

    population = survival(population, children);
}


template < typename ReturnType
         , typename FitnessT
         >
class KTournamentSelection {
public:
    KTournamentSelection() { }
    KTournamentSelection( int const& tSize
                        , int const& cpSize
                        , DataGenerator* rng
                        , FitnessT const& fit
                        )
        : tournamentSize(tSize)
        , childrenPopulationSize(cpSize)
        , random(rng)
        , fitness(fit)
    {
    }

    Population operator()(const Population& parentPopulation) const
    {
        int size = parentPopulation.size();
        ReturnType* scores = new ReturnType[size];

        for (int index = 0; index < size; ++index)
        {
            scores[index] = fitness(parentPopulation.at(index));
        }

        Population parents;
        while (parents.size() < childrenPopulationSize)
        {

            Population candidates;
            for (int index = 0; index < tournamentSize; ++index)
            {
                candidates.push_back(parentPopulation.at(
                    random->getUnsignedInt() % parentPopulation.size() ));
            }
            
            ReturnType max = fitness(candidates.at(0));
            int best = 0;
            
            for (int index = 1; index < candidates.size(); ++index)
            {
                if (fitness(candidates.at(index)) > max)
                {
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
    int tournamentSize;
    int childrenPopulationSize;
    DataGenerator* random;
    FitnessT fitness;
};

template < typename ReturnType
         , typename Fitness
         > 
class RouletteWheelSelection {
public:
    RouletteWheelSelection() { }
    RouletteWheelSelection( int cpSize
                          , DataGenerator* rng
                          , Fitness fit
                          )
        : childrenPopulationSize(cpSize)
        , random(rng)
        , fitness(fit)
    {
    }

    Population operator()(const Population& parentPopulation) const
    {
        int size = parentPopulation.size();
        ReturnType* scores = new int[size];

        ReturnType total = 0;
        for (int index = 0; index < size; ++index)
        {
            total += fitness(parentPopulation.at(index));
            scores[index] = total;
        }

        Population parents;

        while (parents.size() < childrenPopulationSize)
        {
            double score = random->getDouble() * total;

            int index = 0;
            while (scores[index] < score)
            {
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

class BitFlipMutate
{
public:
    BitFlipMutate()
    {
        mutationRate = 0.01;
        random = new DataGenerator();
    }

    BitFlipMutate( double rate
                 , DataGenerator* rng
                 )
        : mutationRate(rate)
        , random(rng)
    {
    }

    Chromosome operator()(const Chromosome& actual) const
    {
        Chromosome result = actual;

        for (int loc = 0; loc < result.size(); ++loc)
        {
            if (random->getDouble() < mutationRate)
            {
                result.set(loc, ! actual[loc]);
            }
            else
            {
                result.set(loc, actual[loc]);
            }
        }

        return result;
    }

private:
    double mutationRate;
    DataGenerator* random;
};

class BitSwapMutate
{
public:
    BitSwapMutate()
    {
        mutationRate = 0.01;
        random = new DataGenerator();
    }

    BitSwapMutate( double rate
                 , DataGenerator* rng
                 )
        : mutationRate(rate)
        , random(rng)
    {
    }

    Chromosome operator()(const Chromosome& actual)
    {
        Chromosome result = actual;

        for (int loc = 0; loc < result.size(); ++loc)
        {
            if (random->getDouble() < mutationRate)
            {
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

class SinglePointCrossover
{
public:
    SinglePointCrossover()
    {
        random = new DataGenerator();
    }
    SinglePointCrossover(DataGenerator* rng)
        : random(rng)
    {
    }

    Pair<Chromosome> operator()(const Chromosome& first, const Chromosome& second)
    {
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

class KPointCrossover
{
public:
    KPointCrossover()
    {
        splitPoints = 3;
        random = new DataGenerator();
    }

    KPointCrossover( int points
                   , DataGenerator* rng
                   )
        : splitPoints(points)
        , random(rng)
    {
    }

    Pair<Chromosome> operator()( const Chromosome& first
                               , const Chromosome& second
                               )
    {
        Pair<Chromosome> result;
        result.first = first;
        result.second = second;
        SinglePointCrossover crossover(random);

        for (unsigned int index = 0; index < splitPoints; index++)
        {
            result = crossover(result.first, result.second);
        }

        return result;
    }

private:
    int splitPoints;
    DataGenerator* random;

    // this relies on side effects to work but only within this class
    void recombineOnePoint( Chromosome& first
                          , Chromosome& second
                          , int point
                          )
    {
        std::vector<Chromosome> firstParts = first.split(point);
        std::vector<Chromosome> secondParts = second.split(point);

        first = Chromosome().merge(firstParts[0], secondParts[1]);
        second = Chromosome().merge(secondParts[0], secondParts[1]);
    }
};

// FIXME DEPRECATED CLASS
class UniformCrossover
{
public:
    UniformCrossover()
    {
    }

    UniformCrossover(DataGenerator* rng)
        : random(rng)
    {
    }

    Pair<Chromosome> operator()( const Chromosome& first
                               , const Chromosome& second
                               )
    {
        Pair<Chromosome> result;
        result.first = first;
        result.second = second;

        for (int loc = 0; loc < first.size(); loc++)
        {
            double value = random->getDouble();

            if (value < 0.5)
            {
                result.first.set(loc, second[loc]);
                result.second.set(loc, first[loc]);
            }
        }

        return result;
    }

private:
    DataGenerator* random;
};

auto uniformCrossover = [&gaRNG] (const Chromosome& first, const Chromosome& second) {
        Pair<Chromosome> result;
        result.first = first;
        result.second = second;

        for (int loc = 0; loc < first.size(); loc++)
        {
            double value = gaRNG->getDouble();

            if (value < 0.5)
            {
                result.first.set(loc, second[loc]);
                result.second.set(loc, first[loc]);
            }
        }

        return result;
    };

// FIXME DEPRECATED CLASS
class GenerationalSurvival
{
public:
    GenerationalSurvival()
    {
    }

    Population operator()( Population population
                         , Population children
                         )
    {
        return children;
    }

};

auto generationalSurvival = [] (Population population, Population children) {
        return children;
    };

*/
#endif

