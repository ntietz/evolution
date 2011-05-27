//file:     mergesort.h
//author:   Nicholas Tietz
//license:  <will be GPL>
//date:     2011.5.21

#include "../../src/merge/mergesort.h"
#include <vector>
#include <iostream>

int main() {

    mergesort<int>* mySort = new mergesort<int>();

    int arrData[] = {45, 89, 23, 1, 345, -123, 346, 1204, 12040230, 123, 123134, 123, 536457, 123, -12345, -234};
    std::vector<int> data;
    for (int index = 0; index < 16; index++) {
        data.push_back(arrData[index]);
    }

    mySort->setData(data);

    std::vector<int> result = mySort->sort();

    int success = true;

    for (int index = 0; index < result.size() - 1; index++) {
        if (result[index+1] < result[index]) success = false;
    }

    if (success == true) std::cout << "Test passed.\n";
    else                 std::cout << "Test failed. Out of order.\n";

}

