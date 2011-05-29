//file:     chromosome.hpp
//author:   ntietz
//date:     2011.5.26
// Specification of a chromosome

#ifndef _CHROMOSOME_HPP_
#define _CHROMOSOME_HPP_

#include <vector>
#include "../common.h"

class chromosome {
public:
    chromosome();
    chromosome(std::vector<bool>);

    void setBits(std::vector<bool>);
    void set(int, bool);
    bool get(int);

    void flip(int);
    chromosome* split(int);

    //operators
    bool operator[](int);
    

private:
    std::vector<bool>* bits;

};

#endif
