//file:     sort.h
//author:   ntietz
//date:     2011.5.26
// Defines a template for a sorting algorithm.

#ifndef _SORT_H_
#define _SORT_H_

#include <vector>

enum sortType { BUBBLE, MERGE, QUICK };

template<typename T>
class sorter {
public:
    sorter() { }
    sorter(std::vector<T>) { }
    ~sorter() { if (secondsort) delete secondsort; }

    virtual void setData(std::vector<T>) = 0;
    virtual void setThreshold(int) = 0;
    virtual void setSecondary(sorter*) = 0;

    std::vector<T> getData() const { return data;}
    int getThreshold() const { return threshold; }
    sorter* getSecondary() const { return secondsort; }

    virtual std::vector<T> sort() = 0;

    virtual sortType getType() = 0;

protected:
    std::vector<T> data;
    int threshold;
    sorter<T>* secondsort;
};

#endif
