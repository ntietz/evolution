//file:     ga.cpp
//author:   ntietz
//date:     2011.6.27
// Implementation of a genetic algorithm class.

#include "ga.hpp"

GeneticAlgorithm::GeneticAlgorithm() {
    selector = &tournamentSelection;

    // this seeds the rng from /dev/urandom
    rng = new DataGenerator();
}

GeneticAlgorithm* GeneticAlgorithm::setChromosomeSize(int size) {
    chromosomeSize = size;
    return this;
}

GeneticAlgorithm* GeneticAlgorithm::setPopulationSize(int size) {
    populationSize = size;
    return this;
}

GeneticAlgorithm* GeneticAlgorithm::setSelectionMechanism(Population* (*function)(Population*)) {
    selector = function;
    return this;
}

GeneticAlgorithm* GeneticAlgorithm::setFitnessFunction(int (*function)(Chromosome*)) {
    scorer = function;
    return this;
}

// tournament selection
Population* tournamentSelection(Population* parents) {

    //int num = rng->getUnsignedInt();

    //TODO: implement

    return 0;
}

// roulette wheel selection
Population* rouletteWheelSelection(Population* parents) {

    //TODO: implement

    return 0;
}


// stochastic universal selection
Population* stochasticUniversalSampling(Population* parents) {

    //TODO: implement

    return 0;
}


