//file:     chromosomeTest.cpp
//author:   ntietz
//date:     2011.7.27
// Unit test for Chromosome class

#include "gtest/gtest.h"
#include "chromosome/chromosome.hpp"

TEST(SizeTest, Default) {
    Chromosome chr;

    EXPECT_EQ(0, chr.size());
}

TEST(SizeTest, SetBits) {
    const int size = 10;
    Chromosome chr = Chromosome(std::vector<bool>(size));

    EXPECT_EQ(size, chr.size());
}

