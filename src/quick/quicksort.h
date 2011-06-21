//file:     quicksort.h
//author:   ntietz
//date:     2011.5.26
// Specification and implementation of a generic, configurable quicksort object.

#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

#include "../common.h"
#include "../sort.h"
#include <vector>

enum pivotMethod {
    FIRST,
    RANDOM,
    AVERAGE
};

template<typename T>
class quicksort : public sorter<T> {
public:
    //constructors defined by interface
    quicksort();
    quicksort(std::vector<T>);
    ~quicksort();

    //setters defined by interface
    void setData(std::vector<T>);
    void setThreshold(int); //sets threshold to switch to a different sort
    void setSecondary(sorter<T>*);

    int getThreshold() { return threshold; }
    sortType getType() { return QUICK; }

    //sort function defined by interface
    std::vector<T> sort();

    //quicksort-specific setters
    void setPivotMethod(pivotMethod);
    void setNumAverage(int); //number of points to use in finding the average

    pivotMethod getPivotMethod();
    int getNumAverage();

    //quicksort-specific function
    std::vector<T> concatenate(std::vector<T>, T, std::vector<T>);

private:
    std::vector<T>* split();

    std::vector<T> data;
    int threshold;
    sorter<T>* secondsort;

};

template<typename T>
quicksort<T>::quicksort() {
    data = std::vector<T>();
    secondsort = null;
    threshold = 0;
}

template<typename T>
quicksort<T>::quicksort(std::vector<T> newData) {
    data = newData;
    secondsort = null;
    threshold = 0;
}

template<typename T>
quicksort<T>::~quicksort() {
    if (secondsort)
        delete secondsort;
}

template<typename T>
void quicksort<T>::setData(std::vector<T> newData) {
    data = newData;
}

template<typename T>
void quicksort<T>::setThreshold(int lowerBound) {
    threshold = lowerBound;
}

template<typename T>
void quicksort<T>::setSecondary(sorter<T>* newsort) {
    secondsort = newsort;
}

template<typename T>
std::vector<T> quicksort<T>::sort() {
    std::vector<T> results = std::vector<T>(data);

    if (results.size() == 0)
        return results;

    if ((long int)results.size() < (long int)threshold) {
        secondsort->setData(data);
        return secondsort->sort();
    }

    std::vector<T> left, right;

    T pivot = results[0]; //TODO: put in a pivot selection method switcher

    for (long int index = 1; index < (long int)results.size(); index++) {
        if (results[index] <= pivot) {
            left.push_back(results[index]);
        } else {
            right.push_back(results[index]);
        }
    }

    //create the objects for the next sorting level
    quicksort leftSorter(left);
        leftSorter.setThreshold(threshold);
        leftSorter.setSecondary(secondsort);
    quicksort rightSorter(right);
        rightSorter.setThreshold(threshold);
        rightSorter.setSecondary(secondsort);

    return concatenate(leftSorter.sort(), pivot, rightSorter.sort());
}

template<typename T>
std::vector<T> quicksort<T>::concatenate(std::vector<T> left, T middle, std::vector<T> right) {
    std::vector<T> results = left;
    results.push_back(middle);

    for (long int index = 0; index < (long int)right.size(); index++) {
        results.push_back(right[index]);
    }

    return results;
}

#endif
