//file:     ga.cpp
//author:   ntietz
//date:     2011.6.27
// Implementation of a genetic algorithm class.

#include "ga.hpp"

template < typename Fitness
         , typename Selection
         , typename Survival
         , typename Mutation
         , typename Recombination
         >
Population* GeneticAlgorithm<Fitness, Selection, Survival, Mutation, Recombination>
::getGeneration() {

    //TODO: implement

    return 0;
}

/*
template <typename Fitness>
Population KTournamentSelection<Fitness>::operator()(const Population& parents) const {
    int size = parents.size();
    int* scores = new int[size];

    for (int index = 0; index < size; index++) {
        scores[index] = Fitness(&parents.at(index));
    }

    Population children();

    while (children.size() < childrenPopulationSize) {
        
    }

    //int num = rng->getUnsignedInt();

    //TODO: implement

    return 0;
}

Population* RouletteWheelSelection::select(Population* parents) {

    //TODO: implement

    return 0;
}

Population* StochasticUniversalSampling::select(Population* parents) {

    //TODO: implement

    return 0;
}
*/

