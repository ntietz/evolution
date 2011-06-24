//file:     random.cpp
//author:   ntietz
//date:     2011.6.23
// Implementation of a wrapper class for random number generation.

UniformRandom::UniformRandom(int lower, int upper) {
    setBounds(lower, upper);
}

UniformRandom::UniformRandom(float lower, float upper) {
    setBounds(lower, upper);
}

UniformRandom::UniformRandom(int intLower, int intUpper, float floatLower, float floatUpper) {
    setBounds(intLower, intUpper);
    setBounds(floatLower, floatUpper);
}

void UniformRandom::setBounds(int lower, int upper) {
    if (!engine)
        engine = new std::mersenne_twister();

    intDistribution = new std::uniform_int(lower, upper);
}

void UniformRandom::setBounds(float lower, float upper) {
    if (!engine)
        engine = new std::mersenne_twister();

    floatDistribution = new std::uniform_float(lower, upper);
}

int UniformRandom::nextInt() {
    return intDistribution(engine);
}

float UniformRandom::nextFloat() {
    return floatDistribution(engine);
}

