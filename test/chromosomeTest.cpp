//file:     chromosomeTest.cpp
//author:   ntietz
//date:     2011.7.27
// Unit test for Chromosome class

#include "gtest/gtest.h"
#include "chromosome/chromosome.hpp"

TEST(Chromosome, DefaultSizeTest) {
    Chromosome chr;

    EXPECT_EQ(0, chr.size());
}

TEST(Chromosome, SetBitsSizeTest) {
    const int size = 10;
    Chromosome chr = Chromosome(std::vector<bool>(size));

    EXPECT_EQ(size, chr.size());
}

TEST(Chromosome, AssignmentSizeTest) {
    const int size = 10;
    Chromosome first = Chromosome(std::vector<bool>(size));
    Chromosome second = first;

    EXPECT_EQ(size, first.size());
    EXPECT_EQ(first.size(), second.size());
}

TEST(Chromosome, SetBits) {
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

TEST(Chromosome, SetAndGet) {
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

TEST(Chromosome, GetBits) {
    const int size = 3;
    Chromosome chr = Chromosome(std::vector<bool>(size));

    chr.set(0, true);
    chr.set(1, false);
    chr.set(2, true);

    std::vector<bool> bits = chr.getBits();

    EXPECT_EQ(true, bits[0]);
    EXPECT_EQ(false, bits[1]);
    EXPECT_EQ(true, bits[2]);
}

TEST(Chromosome, Flip) {
    const int size = 10;
    Chromosome chr = Chromosome(std::vector<bool>(size));

    for (int index = 0; index < size; ++index) {
        chr.set(index, false);
    }

    chr.flip(0);
    chr.flip(3);
    chr.flip(7);

    for (int index = 0; index < size; ++index) {
        switch (index) {
            case 0 :
            case 3 :
            case 7 :
                EXPECT_EQ(true, chr.get(index));
                break;
            default :
                EXPECT_EQ(false, chr.get(index));
                break;
        }
    }
}

TEST(Chromosome, Split) {
    const int size = 10;
    const int splitPoint = 5;
    Chromosome chr = Chromosome(std::vector<bool>(size));

    for (int index = 0; index < splitPoint; ++index) {
        chr.set(index, false);
    }

    for (int index = splitPoint; index < size; ++index) {
        chr.set(index, true);
    }

    std::vector<Chromosome> parts = chr.split(splitPoint);

    ASSERT_EQ(splitPoint, parts[0].size());
    ASSERT_EQ(size - splitPoint, parts[1].size());

    for (int index = 0; index < splitPoint; ++index) {
        EXPECT_EQ(false, parts[0].get(index));
    }

    for (int index = 0; index < (size - splitPoint); ++index) {
        EXPECT_EQ(true, parts[1].get(index));
    }
}

TEST(Chromosome, Merge) {
    Chromosome left = Chromosome(std::vector<bool>(3));
    Chromosome right = Chromosome(std::vector<bool>(5));
    left.set(0, true);
    left.set(1, false);
    left.set(2, false);
    right.set(0, true);
    right.set(1, true);
    right.set(2, true);
    right.set(3, false);
    right.set(4, false);

    Chromosome both = Chromosome().merge(left, right);

    ASSERT_EQ(8, both.size());

    EXPECT_EQ(true, both.get(0));
    EXPECT_EQ(false, both.get(1));
    EXPECT_EQ(false, both.get(2));
    EXPECT_EQ(true, both.get(3));
    EXPECT_EQ(true, both.get(4));
    EXPECT_EQ(true, both.get(5));
    EXPECT_EQ(false, both.get(6));
    EXPECT_EQ(false, both.get(7));
}

TEST(Chromosome, Brackets) {
    Chromosome chr = Chromosome(std::vector<bool>(3));
    chr.set(0, false);
    chr.set(1, true);
    chr.set(2, true);

    EXPECT_EQ(false, chr[0]);
    EXPECT_EQ(true, chr[1]);
    EXPECT_EQ(true, chr[2]);
}

