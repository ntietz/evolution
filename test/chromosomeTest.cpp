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

TEST(SizeTest, Assignment) {
    const int size = 10;
    Chromosome first = Chromosome(std::vector<bool>(size));
    Chromosome second = first;

    EXPECT_EQ(size, first.size());
    EXPECT_EQ(first.size(), second.size());
}

TEST(Accessors, SetBits) {
    std::vector<bool> bits;
    bits.push_back(false);
    bits.push_back(true);
    bits.push_back(false);
    bits.push_back(false);
    bits.push_back(true);

    Chromosome first = Chromosome(bits);

    EXPECT_EQ(false, first.get(0));
    EXPECT_EQ(true, first.get(1));
    EXPECT_EQ(false, first.get(2));
    EXPECT_EQ(false, first.get(3));
    EXPECT_EQ(true, first.get(4));

}

TEST(Accessors, Set) {
    const int size = 10;
    std::vector<bool> bits(size);
    
    Chromosome chr(bits);

    EXPECT_EQ(bits.size(), chr.size());

    for (int index = 0; index < size; ++index) {
        EXPECT_EQ(false, chr.get(index));
        chr.set(index, true);
        EXPECT_EQ(true, chr.get(index));
    }

}

