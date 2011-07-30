//file:     bubblesortTest.cpp
//author:   ntietz
//date:     2011.7.30
// Unit test for bubblesort class.

#include "gtest/gtest.h"
#include "bubble/bubblesort.h"

TEST(Bubblesort, Sort) {

    std::vector<int> unsortedData;
    unsortedData.push_back(-302);
    unsortedData.push_back(201);
    unsortedData.push_back(2012);
    unsortedData.push_back(0);
    unsortedData.push_back(-1);
    unsortedData.push_back(23);
    unsortedData.push_back(12);
    unsortedData.push_back(-2);

    bubblesort<int> bsort;
    bsort.setData(unsortedData);

    std::vector<int> sortedData = bsort.sort();

    ASSERT_EQ(unsortedData.size(), sortedData.size());

    for (int index = 0; index < sortedData.size() - 1; ++index) {
        EXPECT_LT(sortedData[index], sortedData[index+1]);
    }
}

