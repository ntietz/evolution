//file:     gaTest.cpp
//author:   ntietz
//date:     2011.8.6
// Unit test for GeneticAlgorithm class

#include "gtest/gtest.h"
#include "ga/ga.h"

class Fitness {
public:
    int operator()(const Chromosome& candidate) const {
        int score = 0;

        for (int index = 0; index < candidate.size(); ++index) {
            if (candidate[index] == 0) {
                ++score;
            }
        }

        return score;
    }
};

TEST(GeneticAlgorithm, GetRandomChromosome) {
    // set the size sufficiently large to make the distribution apparent
    int size = 5000;
    DataGenerator* rng = new DataGenerator(1024, 1024);
    Chromosome chr = getRandomChromosome(size, rng);

    ASSERT_EQ(size, chr.size());

    int zeroCount = 0;
    int onesCount = 0;

    for (int index = 0; index < size; ++index) {
        if (chr[index] == true) {
            ++onesCount;
        } else {
            ++zeroCount;
        }
    }

    EXPECT_LT(zeroCount, (size / 2) + (size / 100));
    EXPECT_LT(onesCount, (size / 2) + (size / 100));
}

TEST(GeneticAlgorithm, KTournamentSelection) {
    Fitness fitness;
    int populationSize = 100;
    int childrenPopulationSize = 100;
    int chromosomeSize = 25;
    int tournamentSize = 10;
    DataGenerator* rng = new DataGenerator(1024, 1024);

    KTournamentSelection<Fitness> selection(tournamentSize, childrenPopulationSize, rng, fitness);

    Population population(populationSize);
    for (int index = 0; index < populationSize; ++index) {
        population[index] = getRandomChromosome(chromosomeSize);
    }

    Population children = selection(population);

    ASSERT_EQ(childrenPopulationSize, children.size());

}

