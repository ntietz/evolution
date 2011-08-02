//file:     sort.h
//author:   ntietz
//date:     2011.5.26
// Defines a template for a sorting algorithm.

#ifndef _SORT_H_
#define _SORT_H_

#include <vector>

enum sortType { BOGUS, BUBBLE, MERGE, QUICK };

template<typename T>
class sorter {
public:
    sorter() { }
    sorter(std::vector<T>) { }
    virtual ~sorter() { }

    virtual void setData(std::vector<T>) = 0;
    virtual void setThreshold(int) = 0;
    virtual void setSecondary(sorter<T>*) = 0;

    std::vector<T> getData() const { return data;}
    int getThreshold() const { return threshold; }
    sorter<T> getSecondary() const { return secondsort; }

    virtual std::vector<T> sort() = 0;

    virtual sortType getType() { return BOGUS; }

protected:
    std::vector<T> data;
    int threshold;
    sorter* secondsort;
};

#endif
