//file:     chromosome.cpp
//author:   ntietz
//date:     2011.5.26
// Implementation of a chromosome

#include "chromosome.hpp"

Chromosome::Chromosome() {
    // do nothing
}

Chromosome::Chromosome(std::vector<bool> newBits) {
    bits = newBits;
}

void Chromosome::setBits(std::vector<bool> newBits) {
    bits = newBits;
}

std::vector<bool> Chromosome::getBits() const {
    return bits;
}

void Chromosome::set(int index, bool value) {
    bits[index] = value;
}

bool Chromosome::get(int index) const {
    return bits[index];
}

int Chromosome::size() const {
    return bits.size();
}

void Chromosome::flip(int index) {
    bits[index] = !bits[index];
}

std::vector<Chromosome> Chromosome::split(int splitPoint) const {
    std::vector<Chromosome> results;

    long int leftSize = (splitPoint >= (int)bits.size()) ? (bits.size() - 1) : splitPoint;
    long int rightSize = bits.size() - leftSize - 1;

    std::vector<bool> left(leftSize);
    std::vector<bool> right(rightSize);

    for (int index = 0; index < (int)leftSize; index++) {
        left.push_back(bits[index]);
    }

    for (int index = 0; index < (int)rightSize; index++) {
        right.push_back(bits[index + leftSize]);
    }

    return results;
}

Chromosome Chromosome::merge(const Chromosome& left, const Chromosome& right) {
    std::vector<bool> bits;

    for (int index = 0; index < (int)left.size(); ++index) {
        bits.push_back(left[index]);
    }

    for (int index = 0; index < (int)right.size(); ++index) {
        bits.push_back(right[index]);
    }

    return Chromosome(bits);
}

bool Chromosome::operator[](int index) const {
    return bits[index];
}

