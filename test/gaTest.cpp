//file:     gaTest.cpp
//author:   ntietz
//date:     2011.8.6
// Unit test for GeneticAlgorithm class

#include "gtest/gtest.h"
#include "ga/ga.h"

TEST(GeneticAlgorithm, GetRandomChromosome) {
    int size = 20;
    Chromosome chr = getRandomChromosome(size);

    EXPECT_EQ(size, chr.size());
}

