//file:     chromosome.cpp
//author:   ntietz
//date:     2011.5.26
// Implementation of a chromosome

#include "chromosome.hpp"

Chromosome::Chromosome()
{
    // do nothing
}

Chromosome::Chromosome(std::vector<bool> newBits)
{
    bits = newBits;
}

void Chromosome::setBits(std::vector<bool> newBits)
{
    bits = newBits;
}

std::vector<bool> Chromosome::getBits() const
{
    return bits;
}

void Chromosome::set(int index, bool value)
{
    bits[index] = value;
}

bool Chromosome::get(int index) const
{
    return bits[index];
}

int Chromosome::size() const
{
    return bits.size();
}

void Chromosome::flip(int index)
{
    bits[index] = !bits[index];
}

std::vector<Chromosome> Chromosome::split(int splitPoint) const
{
    std::vector<Chromosome> results;

    long int leftSize = (bits.size() < splitPoint) ? (bits.size() - 1) : splitPoint;
    long int rightSize = bits.size() - leftSize;

    std::vector<bool> left;
    std::vector<bool> right;

    for (int index = 0; index < (int)leftSize; ++index)
    {
        left.push_back(bits[index]);
    }

    for (int index = 0; index < (int)rightSize; ++index)
    {
        right.push_back(bits[index + leftSize]);
    }

    results.push_back(Chromosome(left));
    results.push_back(Chromosome(right));

    return results;
}

Chromosome Chromosome::merge( const Chromosome& left
                            , const Chromosome& right
                            )
{
    std::vector<bool> newBits;

    for (int index = 0; index < (int)left.size(); ++index)
    {
        newBits.push_back(left[index]);
    }

    for (int index = 0; index < (int)right.size(); ++index)
    {
        newBits.push_back(right[index]);
    }

    return Chromosome(newBits);
}

bool Chromosome::operator[](int index) const
{
    return bits[index];
}

bool Chromosome::operator==(const Chromosome& other) const
{
    if (bits.size() != other.size())
    {
        return false;
    }
    else
    {
        for (int index = 0; index < bits.size(); ++index)
        {
            if (bits[index] != other[index])
            {
                return false;
            }
        }
        return true;
    }
}

bool Chromosome::operator!=(const Chromosome& other) const
{
    return !((*this) == other);
}

