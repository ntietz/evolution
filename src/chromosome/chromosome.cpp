//file:     chromosome.cpp
//author:   ntietz
//date:     2011.5.26
// Implementation of a chromosome

#include "chromosome.hpp"

chromosome::chromosome() {
    bits = null;
}

chromosome::chromosome(std::vector<bool> newBits) {
    bits = new std::vector<bool>(newBits);
}

void chromosome::setBits(std::vector<bool> newBits) {
    bits = new std::vector<bool>(newBits);
}

std::vector<bool> chromosome::getBits() {
    return *bits;
}

void chromosome::set(int index, bool value) {
    (*bits)[index] = value;
}

bool chromosome::get(int index) {
    return (*bits)[index];
}

int chromosome::size() {
    return bits->size();
}

void chromosome::flip(int index) {
    (*bits)[index] = !(*bits)[index];
}

std::vector<chromosome> chromosome::split(int splitPoint) {
    std::vector<chromosome> results;

    int leftSize = (splitPoint >= bits->size()) ? (bits->size() - 1) : splitPoint;
    int rightSize = bits->size() - leftSize - 1;

    std::vector<bool> left(leftSize);
    std::vector<bool> right(rightSize);

    for (int index = 0; index < leftSize; index++) {
        left.push_back((*bits)[index]);
    }

    for (int index = 0; index < rightSize; index++) {
        right.push_back((*bits)[index + leftSize]);
    }

    return results;
}

chromosome chromosome::merge(chromosome left, chromosome right) const {
    std::vector<bool> bits;

    for (int index = 0; index < left.size(); index++) {
        bits.push_back(left[index]);
    }

    for (int index = 0; index < right.size(); index++) {
        bits.push_back(right[index]);
    }

    return chromosome(bits);
}

bool chromosome::operator[](int index) {
    return (*bits)[index];
}

