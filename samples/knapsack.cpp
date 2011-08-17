//file:     knapsack.cpp
//author:   ntietz
//date:     2011.8.16
// Sample application, applying the GA to the 0-1 knapsack problem.

#include "ga/ga.h"
#include <iostream>
#include <vector>
#include <string>
using std::string;
using std::vector;
using std::cout;
using std::endl;

class Object {
public:
    Object(string n, int w, int v)
        : name(n)
        , weight(w)
        , value(v)
        { }

    string name;
    int weight;
    int value;
};

class Fitness {
public:
    Fitness() { }
    Fitness(vector<Object> pObjects, int pMax)
        : objects(pObjects)
        , maxWeight(pMax)
        { }

    int operator()(const Chromosome& candidate) const {
        int score = 0;
        int weight = 0;

        for (int index = 0; index < candidate.size(); ++index) {
            if ((weight + objects[index].weight < maxWeight) && candidate[index] == true) {
                score += objects[index].value;
                weight += objects[index].weight;
            }
        }

        return score;
    }

private:
    vector<Object> objects;
    int maxWeight;
};

int main() {
    DataGenerator* rng = new DataGenerator();
    int tournamentSize = 5;
    int populationSize = 100;
    int childrenPopulationSize = populationSize;

    double mutationRate = 0.06;
    double recombinationRate = 0.75;

    int maxWeight = 400;

    vector<Object> objects;
    objects.push_back(Object("map", 9, 150));
    objects.push_back(Object("compass", 13, 35));
    objects.push_back(Object("water", 153, 200));
    objects.push_back(Object("sandwich", 50, 160));
    objects.push_back(Object("glucose", 15, 60));
    objects.push_back(Object("tin", 68, 45));
    objects.push_back(Object("banana", 27, 60));
    objects.push_back(Object("apple", 39, 40));
    objects.push_back(Object("cheese", 23, 30));
    objects.push_back(Object("beer", 52, 10));
    objects.push_back(Object("suntan cream", 11, 70));
    objects.push_back(Object("camera", 32, 30));
    objects.push_back(Object("T-shirt", 24, 15));
    objects.push_back(Object("trousers", 48, 10));
    objects.push_back(Object("umbrella", 73, 40));
    objects.push_back(Object("waterproof trousers", 42, 70));
    objects.push_back(Object("waterproof overclothes", 43, 75));
    objects.push_back(Object("note-case", 22, 80));
    objects.push_back(Object("sunglasses", 7, 20));
    objects.push_back(Object("towel", 18, 12));
    objects.push_back(Object("socks", 4, 50));
    objects.push_back(Object("book", 30, 10));

    int chromosomeSize = objects.size();

    Fitness fitness(objects, maxWeight);
    KTournamentSelection<int, Fitness> selection(tournamentSize, childrenPopulationSize, rng, fitness);
    GenerationalSurvival survival;
    BitFlipMutate mutation(mutationRate, rng);
    SinglePointCrossover crossover(rng);

    GeneticAlgorithm< Fitness
                    , KTournamentSelection<int, Fitness>
                    , GenerationalSurvival
                    , BitFlipMutate
                    , SinglePointCrossover
                    > ga( fitness
                        , selection
                        , survival
                        , mutation
                        , crossover
                        );

    
    ga.setChromosomeSize(chromosomeSize)
      .setPopulationSize(populationSize)
      .setChildrenPopulationSize(childrenPopulationSize)
      .setMutationRate(mutationRate)
      .setRecombinationRate(recombinationRate)
      .setRng(rng);

    ga.init();

    int round = 0;
    int populationFitness = 0;
    int maxRounds = 100;

    int idealFitness = 1030; // known from the given input
    
    do {
        ga.step();

        int maxFitness = 0;
        int minFitness = chromosomeSize;
        int sum = 0;
        for (int index = 0; index < ga.get().size(); ++index) {
            int currentFitness = fitness(ga.get()[index]);

            if (currentFitness > maxFitness) {
                maxFitness = currentFitness;
            }

            if (currentFitness < minFitness) {
                minFitness = currentFitness;
            }

            sum += currentFitness;
        }
        double meanFitness = sum / ga.get().size();
        
        ++round;
        populationFitness = maxFitness;

        cout << "Round " << round << " has fitness " << populationFitness << endl;
    } while (round < maxRounds && populationFitness < idealFitness);

    
    cout << "Converged in " << round << " generations." << endl;

    int maxFitness = 0;
    int minFitness = chromosomeSize;
    int sum = 0;
    for (int index = 0; index < ga.get().size(); ++index) {
        int currentFitness = fitness(ga.get()[index]);

        if (currentFitness > maxFitness) {
            maxFitness = currentFitness;
        }

        if (currentFitness < minFitness) {
            minFitness = currentFitness;
        }

        sum += currentFitness;
    }
    double meanFitness = sum / ga.get().size();

    cout << "Final population statistics: " << endl
         << "  min:  " << minFitness << endl
         << "  max:  " << maxFitness << endl
         << "  mean: " << meanFitness << endl;


}

