//file:     chromosome.hpp
//author:   ntietz
//date:     2011.5.26
// Specification of a chromosome

#ifndef _CHROMOSOME_HPP_
#define _CHROMOSOME_HPP_

#include <vector>
#include "../common.h"

class Chromosome {
public:
    Chromosome();
    Chromosome(std::vector<bool>);

    void setBits(std::vector<bool>);
    std::vector<bool> getBits();
    void set(int, bool);
    bool get(int);
    int size();

    void flip(int);
    std::vector<Chromosome> split(int);

    Chromosome merge(Chromosome, Chromosome) const;

    //operators
    bool operator[](int);

private:
    std::vector<bool>* bits;

};

#endif
