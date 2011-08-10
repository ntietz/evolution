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
        population[index] = getRandomChromosome(chromosomeSize, rng);
    }

    Population children = selection(population);

    ASSERT_EQ(childrenPopulationSize, children.size());
}

TEST(GeneticAlgorithm, RouletteWheelSelection) {
    Fitness fitness;
    int populationSize = 100;
    int childrenPopulationSize = 100;
    int chromosomeSize = 25;
    DataGenerator* rng = new DataGenerator(1024, 1024);

    RouletteWheelSelection<Fitness> selection(childrenPopulationSize, rng, fitness);

    Population population(populationSize);
    for (int index = 0; index < populationSize; ++index) {
        population[index] = getRandomChromosome(chromosomeSize, rng);
    }

    Population children = selection(population);

    ASSERT_EQ(childrenPopulationSize, children.size());
}

TEST(GeneticAlgorithm, BitFlipMutate) {
    double mutationRate = 0.5;
    int chromosomeSize = 100000;
    DataGenerator* rng = new DataGenerator(1024, 1024);
    Chromosome chromosome = getRandomChromosome(chromosomeSize, rng);

    BitFlipMutate mutate(mutationRate, rng);

    Chromosome mutatedChromosome = mutate(chromosome);

    ASSERT_EQ(chromosomeSize, mutatedChromosome.size());

    int changedCount = 0;
    for (int index = 0; index < chromosomeSize; ++index) {
        if (chromosome[index] != mutatedChromosome[index]) {
            ++changedCount;
        }
    }

    EXPECT_LT((chromosomeSize/2) - (chromosomeSize/100), changedCount);
    EXPECT_LT(changedCount, (chromosomeSize/2) + (chromosomeSize/100));
}

TEST(GeneticAlgorithm, BitSwapMutate) {
    double mutationRate = 0.1;
    int chromosomeSize = 100000;
    DataGenerator* rng = new DataGenerator(1024, 1024);
    Chromosome chromosome = getRandomChromosome(chromosomeSize, rng);

    BitSwapMutate mutate(mutationRate, rng);

    Chromosome mutatedChromosome = mutate(chromosome);

    ASSERT_EQ(chromosomeSize, mutatedChromosome.size());

    int changedCount = 0;
    for (int index = 0; index < chromosomeSize; ++index) {
        if (chromosome[index] != mutatedChromosome[index]) {
            ++changedCount;
        }
    }


    EXPECT_LT((chromosomeSize/10) - (chromosomeSize/100), changedCount);
    EXPECT_LT(changedCount, (chromosomeSize/10) + (chromosomeSize/100));
}

TEST(GeneticAlgorithm, SinglePointCrossover) {
    int chromosomeSize = 50;
    DataGenerator* rng = new DataGenerator(1024, 1024);
    Chromosome first = getRandomChromosome(chromosomeSize, rng);
    Chromosome second = getRandomChromosome(chromosomeSize, rng);

    SinglePointCrossover crossover(rng);

    Pair<Chromosome> result = crossover(first, second);

    ASSERT_NE(first, second);
    ASSERT_EQ(chromosomeSize, result.first.size());
    ASSERT_EQ(chromosomeSize, result.second.size());

    int switchpoint = -1;
    for (int index = 0; index < chromosomeSize; ++index) {
        if (switchpoint < 0) {
            if (first[index] == result.second[index]
              && second[index] == result.first[index]
              && first[index] != second[index]) {
                switchpoint = index;
            } else {
                EXPECT_EQ(first[index], result.first[index]);
                EXPECT_EQ(second[index], result.second[index]);
            }
        } else {
            EXPECT_EQ(first[index], result.second[index]);
            EXPECT_EQ(second[index], result.first[index]);
        }
    }

    EXPECT_GT(switchpoint, 0);
}

TEST(GeneticAlgorithm, KPointCrossover) {



    ASSERT_STREQ("TEST_WRITTEN", "NO");

}

TEST(GeneticAlgorithm, UniformCrossover) {

    ASSERT_STREQ("TEST_WRITTEN", "NO");
}

