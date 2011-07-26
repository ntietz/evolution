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

    Population operator()(const Population& foo, const Population& bar) { return foo; }

} foo;

int main() {

    int tournamentSize = 10;
    int populationSize = 100;
    int childPopulationSize = 100;

    DataGenerator* random = new DataGenerator(1532, 943912);

    Fitness fitness;
    KTournamentSelection<Fitness> selection(tournamentSize, childPopulationSize, random, fitness);
    //KTournamentSelection<Fitness> selection(10, 100, new DataGenerator(1532, 943912), fitness);
    BitFlipMutate mutate(0.01, random);
    SinglePointCrossover crossover(random);


    GeneticAlgorithm<Fitness, KTournamentSelection<Fitness>, FooSurvival, BitFlipMutate, SinglePointCrossover>
        ga(fitness, selection, foo, mutate, crossover);
    
    ga.setChromosomeSize(10)
      .setPopulationSize(populationSize)
      .setChromosomeSize(childPopulationSize)
      .setMutationRate(0.01)
      .setRecombinationRate(0.9);

    ga.init();
    ga.step();
}

