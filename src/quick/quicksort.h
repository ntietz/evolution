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

    //setters defined by interface
    void setData(std::vector<T>);
    void setThreshold(int); //sets threshold to switch to a different sort
    void setSecondary(sorter<T>*);

    //sort function defined by interface
    std::vector<T> sort();

    //quicksort-specific setters
    void setPivotMethod(pivotMethod);
    void setNumAverage(int); //number of points to use in finding the average

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
void quicksort<T>::setData(std::vector<T> newData) {
    data = newData;
}

template<typename T>
void setThreshold(int lowerBound) {
    threshold = lowerBound;
}

template<typename T>
void setSecondary(sorter<T>* newsort) {
    secondsort = newsort;
}

#endif
