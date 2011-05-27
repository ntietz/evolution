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

    void setData(std::vector<T>);
    void setThreshold(int);
    void setSecondary(sorter<T>*);
    //setThreshold() and setSecondary() are not used but are required to be defined

    std::vector<T> sort();

private:

    std::vector<T> data;
    sorter<T>* secondsort;

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
void bubblesort<T>::setData(std::vector<T> newData) {
    data = newData;
}

template<typename T>
void bubblesort<T>::setThreshold(int i) {
    //ignore it
}

template<typename T>
void bubblesort<T>::setSecondary(sorter<T>* s) {
    //ignore it
}

template<typename T>
std::vector<T> bubblesort<T>::sort() {
    
    for (int index = 0; index < data.size() - 1; index++) {
        for (int jndex = index; jndex < data.size(); jndex++) {
            if (data[index] < data[jndex]) {
                swap(data[index], data[jndex]);
            }
        }
    }
}

#endif
