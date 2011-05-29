//file:     mergesort.h
//author:   ntietz
//date:     2011.5.26
// Specification and implementation of a generic, configurable mergesort object.

#ifndef _MERGESORT_H_
#define _MERGESORT_H_

#include "../common.h"
#include "../sort.h"
#include <vector>

template<typename T>
class mergesort : public sorter<T> {
public:
    mergesort();
    mergesort(std::vector<T>);
    ~mergesort();

    void setData(std::vector<T>);
    void setThreshold(int); //sets threshold to switch to a different sort
    void setSecondary(sorter<T>*);

    std::vector<T> sort();

private:
    std::vector<T>* split();
    std::vector<T> merge(std::vector<T>, std::vector<T>);

    std::vector<T> data;
    int threshold;
    sorter<T>* secondsort;

};

template<typename T>
mergesort<T>::mergesort() {
    data = std::vector<T>();
    secondsort = null;
    threshold = 0;
}

template<typename T>
mergesort<T>::mergesort(std::vector<T> newData) {
    data = newData;
    secondsort = null;
    threshold = 0;
}

template<typename T>
mergesort<T>::~mergesort() {
    if (secondsort)
        delete secondsort;
}

template<typename T>
void mergesort<T>::setData(std::vector<T> newData) {
    data = newData;
}

template<typename T>
void mergesort<T>::setThreshold(int lowerBound) {
    threshold = lowerBound;
}

template<typename T>
void mergesort<T>::setSecondary(sorter<T>* newsort) {
    secondsort = newsort;
}

template<typename T>
std::vector<T> mergesort<T>::sort() {
    if (data.size() < threshold && secondsort != null) {
        secondsort->setData(data);
        return secondsort->sort();
    } else {
        if (data.size() == 1) {
            return data;
        } else {
            std::vector<T>* halves = split();

            //passes on the properties to the new sorts
            mergesort* left = new mergesort(halves[0]);
                left->setThreshold(threshold);
                left->setSecondary(secondsort);
            mergesort* right = new mergesort(halves[1]);
                right->setThreshold(threshold);
                right->setSecondary(secondsort);
            return merge(left->sort(), right->sort());
        }
    }

    return data;
}

template<typename T>
std::vector<T>* mergesort<T>::split() {
    std::vector<T>* halves = new std::vector<T>[2];

    int leftSize = data.size() / 2;
    int rightSize = data.size() - leftSize;

    halves[0].resize(leftSize);
    for (int index = 0; index < leftSize; index++) {
        halves[0][index] = data[index];
    }

    halves[1].resize(rightSize);
    for (int index = 0; index < rightSize; index++) {
        halves[1][index] = data[index + leftSize];
    }

    return halves;
}

template<typename T>
std::vector<T> mergesort<T>::merge(std::vector<T> left, std::vector<T> right) {
    std::vector<T> result;

    int leftIter = 0;   int leftSize = left.size();
    int rightIter = 0;  int rightSize = right.size();

    while (leftIter < leftSize && rightIter < rightSize) {
        if (left[leftIter] < right[rightIter]) {
            result.push_back(left[leftIter]);
            leftIter++;
        } else {
            result.push_back(right[rightIter]);
            rightIter++;
        }
    }

    while (leftIter < leftSize) {
        result.push_back(left[leftIter]);
        leftIter++;
    }

    while (rightIter < rightSize) {
        result.push_back(right[rightIter]);
        rightIter++;
    }

    return result;
}

#endif
