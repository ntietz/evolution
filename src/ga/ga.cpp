//file:     ga.cpp
//author:   ntietz
//date:     2011.6.27
// Implementation of a genetic algorithm class.

#include "ga.hpp"

GeneticAlgorithm::GeneticAlgorithm() {
    //selector = &tournamentSelection;

    // this seeds the rng from /dev/urandom
    rng = new DataGenerator();
}

GeneticAlgorithm* GeneticAlgorithm::setChromosomeSize(unsigned int size) {
    chromosomeSize = size;
    return this;
}

GeneticAlgorithm* GeneticAlgorithm::setPopulationSize(unsigned int size) {
    populationSize = size;
    return this;
}

GeneticAlgorithm* GeneticAlgorithm::setChildrenPopulationSize(unsigned int size) {
    childrenPopulationSize = size;
    return this;
}

unsigned int GeneticAlgorithm::getGenerationNumber() {
    return generationNumber;
}

Population* GeneticAlgorithm::getGeneration() {

    //TODO: implement

    return 0;
}

Population* TournamentSelection::select(Population* parents) {
    
    int size = parents->size();
    int* scores = new int[size];

    for (int index = 0; index < size; index++) {
        scores[index] = fitness(&parents->at(index));
    }

    Population* children = new Population();

    while (children->size() < childrenPopulationSize) {
        //TODO: do stuff
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

Population* NoElitism::generate( Population* parents
                               , Population* children
                               ) {
    
    //TODO: implement

    return 0;
}

Population* FullElitism::generate( Population* parents
                                 , Population* children
                                 ) {

    //TODO: implement

    return 0;
}

Population* Aging::generate( Population* parents
                           , Population* children
                           ) {
    
    //TODO: implement

    return 0;
};

