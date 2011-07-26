//file:     gatest.cpp
//author:   ntietz
//date:     2011.7.20

#include "../../src/ga/ga.h"
#include <iostream>

class Fitness {
public:
    Fitness() { }
    Fitness(const Fitness& actual) { }

    int operator()(const Chromosome& candidate) const {
        int result = 0;
        
        for (int index = 0; index < candidate.size(); ++index) {
            if (candidate[index] == true) {
                ++result;
            }
        }

        return result;
    }

};

class FooSurvival {
public:
    FooSurvival() { }

    Population operator()(const Population& population, const Population& children) { return children; }

} foo;

int main() {

    int tournamentSize = 10;
    int populationSize = 100;
    int childPopulationSize = 100;

    DataGenerator* random = new DataGenerator(1532, 943912);

    Fitness fitness;
    KTournamentSelection<Fitness> selection(tournamentSize, childPopulationSize, random, fitness);
    BitFlipMutate mutate(0.01, random);
    SinglePointCrossover crossover(random);


    GeneticAlgorithm<Fitness, KTournamentSelection<Fitness>, FooSurvival, BitFlipMutate, SinglePointCrossover>
        ga(fitness, selection, foo, mutate, crossover);
    
    ga.setChromosomeSize(10)
      .setPopulationSize(populationSize)
      .setChildrenPopulationSize(childPopulationSize)
      .setMutationRate(0.01)
      .setRecombinationRate(0.9);

    ga.init();

    for (int index = 0; index < 100; ++index) {
        std::cout << "Round " << index << "..." << std::endl;
        ga.step();
        std::cout << "...finished.\n";
    }
}

