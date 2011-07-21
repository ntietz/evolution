//file:     gatest.cpp
//author:   ntietz
//date:     2011.7.20

#include "../../src/ga/ga.h"
#include <iostream>

class Fitness {
public:
    Fitness() { }

    int operator()(const Chromosome& candidate) {
        int result = 0;

        for (int index = 0; index < candidate.size(); ++index) {
            if (candidate[index] == true) {
                ++result;
            }
        }

        return result;
    }

};

int main() {

    int tournamentSize = 10;
    int populationSize = 100;
    int childPopulationSize = 100;

    DataGenerator* random = new DataGenerator(1532, 943912);

    Fitness fitness();
    KTournamentSelection<Fitness> selection(tournamentSize, childPopulationSize, random, fitness);
    //KTournamentSelection<Fitness> selection(10, 100, new DataGenerator(1532, 943912), fitness);
    BitFlipMutate mutate(0.01, random);
    SinglePointCrossover crossover(random);

}

