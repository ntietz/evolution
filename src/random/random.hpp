//file:     random.hpp
//author:   ntietz
//date:     2011.6.23
// Specification of a wrapper class for random number generation.

#ifndef _RANDOM_HPP_
#define _RANDOM_HPP_

class UniformRandom {
public:
    UniformRandom(int, int);
    UniformRandom(float, float);
    UniformRandom(int, int, float, float);

    void setBounds(int, int);
    void setBounds(float, float);

    int nextInt();
    float nextFloat();

private:
    std::mersenne_twister* engine;
    std::uniform_int* intDistribution;
    std::uniform_float* floatDistribution;

};

#endif

