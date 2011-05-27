//file:     sort.h
//author:   ntietz
//date:     2011.5.26
// Defines a template for a sorting algorithm.

#ifndef _SORT_H_
#define _SORT_H_

#include <vector>

template<typename T>
class sorter {
public:
    sorter() { }
    sorter(std::vector<T>) { }

    virtual void setData(std::vector<T>) = 0;
    virtual void setThreshold(int) = 0;
    virtual void setSecondary(sorter*) = 0;

    virtual std::vector<T> sort() = 0;
};

#endif
