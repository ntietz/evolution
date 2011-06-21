//file:     bubblesort.h
//author:   ntietz
//date:     2011.5.26
// Specification and implementation of a generic, configurable bubblesort object.

#ifndef _BUBBLESORT_H_
#define _BUBBLESORT_H_

#include "../common.h"
#include "../sort.h"
#include <vector>

template<typename T>
class bubblesort : public sorter<T> {
public:
    bubblesort();
    bubblesort(std::vector<T>);
    ~bubblesort();

    void setData(std::vector<T>);
    void setThreshold(int);
    void setSecondary(sorter<T>*);

    std::vector<T> sort();

    sortType getType() { return BUBBLE; }

private:

    // gaining access to parent's protected members...
    using sorter<T>::data;
    using sorter<T>::threshold;
    using sorter<T>::secondsort;
};

template<typename T>
bubblesort<T>::bubblesort() {
    data = std::vector<T>();
}

template<typename T>
bubblesort<T>::bubblesort(std::vector<T> newData) {
    data = newData;
}

template<typename T>
bubblesort<T>::~bubblesort() {
    delete secondsort;
}

template<typename T>
void bubblesort<T>::setData(std::vector<T> newData) {
    data = newData;
}

template<typename T>
void bubblesort<T>::setThreshold(int i) {
    threshold = i;
}

template<typename T>
void bubblesort<T>::setSecondary(sorter<T>* s) {
    secondsort = s;
}

template<typename T>
std::vector<T> bubblesort<T>::sort() {
    
    bool swapped = true;

    while (swapped) {
        swapped = false;

        for (long int index = 0; index < (long int)data.size() - 1; index++) {
            if (data[index] > data[index + 1]) {
                swap(data[index], data[index + 1]);
                swapped = true;
            }
        }
    }

    return data;
}

#endif
