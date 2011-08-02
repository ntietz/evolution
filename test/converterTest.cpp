//file:     converterTest.cpp
//author:   ntietz
//date:     2011.7.30
// Unit test for the converter class

#include "gtest/gtest.h"
#include "converter/converter.hpp"
#include "all_sorts.h"

TEST(Convert, Quicksort) {
    int arraySize = 5;

    Converter<int> converter;

    quicksort<int>* sorts = new quicksort<int>[5];

    sorts[0] = quicksort<int>();
    sorts[0].setThreshold(0);
    sorts[0].setSecondary(0);
    sorts[0].setPivotMethod(FIRST);
    sorts[0].setNumAverage(0);
        
    sorts[1] = sorts[0];
    sorts[1].setThreshold(13);

    sorts[2] = sorts[0];
    sorts[2].setSecondary(new bubblesort<int>());

    sorts[3] = sorts[0];
    sorts[3].setPivotMethod(RANDOM);

    sorts[4] = sorts[0];
    sorts[4].setNumAverage(3);

    for (int index = 0; index < arraySize; ++index) {
        for (int otherIndex = index; otherIndex < arraySize; ++otherIndex) {
            sorter<int> first = sorts[index];
            sorter<int> second = sorts[otherIndex];
            Chromosome left = converter.toChromosome(first);
            Chromosome right = converter.toChromosome(second);

            if (index != otherIndex) {
                EXPECT_NE(left, right);
            } else {
                EXPECT_EQ(left, right);
            }
        }
    }
}

TEST(Convert, Bubblesort) {


}

TEST(Convert, Mergesort) {


}

