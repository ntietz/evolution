//file:     expressions.cpp
//author:   ntietz
//date:     2011.8.13
// Sample expression-creating program

#include "ga/ga.h"
#include <iostream>
#include <string>
#include <vector>
#include <climits>
using std::cout;
using std::endl;
using std::string;
using std::vector;

void display(const Chromosome&);

char convertFromBits(string bits) {
    if (bits == "0000")
        return '0';
    else if (bits == "0001")
        return '1';
    else if (bits == "0010")
        return '2';
    else if (bits == "0011")
        return '3';
    else if (bits == "0100")
        return '4';
    else if (bits == "0101")
        return '5';
    else if (bits == "0110")
        return '6';
    else if (bits == "0111")
        return '7';
    else if (bits == "1000")
        return '8';
    else if (bits == "1001")
        return '9';
    else if (bits == "1010")
        return '+';
    else if (bits == "1011")
        return '-';
    else if (bits == "1100")
        return '*';
    else if (bits == "1101")
        return '/';

    return '*';
}

string convertToBits(char c) {
    switch (c) {
        case '0' :
            return "0000";
        case '1' :
            return "0001";
        case '2' :
            return "0010";
        case '3' :
            return "0011";
        case '4' :
            return "0100";
        case '5' :
            return "0101";
        case '6' :
            return "0110";
        case '7' :
            return "0111";
        case '8' :
            return "1000";
        case '9' :
            return "1001";
        case '+' :
            return "1010";
        case '-' :
            return "1011";
        case '*' :
            return "1100";
        case '/' :
            return "1101";
        case '?' :
            return "1110";

    }
}

string expressionFromChromosome(const Chromosome& candidate) {
    string expression = "";

    int numBlocks = candidate.size() / 4;

    for (int index = 0; index < numBlocks; ++index) {
        string bits = "";
        for (int loc = 0; loc < 4; ++loc) {
            bits += (candidate[4*index + loc] == true ? '1' : '0');
        }

        if ('?' != convertFromBits(bits))
        expression += convertFromBits(bits);

    }

    return expression;
}

int stringToInt(string str) {
    int value = 0;

    for (int index = 0; index < str.size(); ++index) {
        value = 10*value + (str[index] - '0');
    }

    return value;
}

vector<string> tokenize(string expression) {
    vector<string> tokens;
    string token = "0";
    bool wasNum = true;

    for (int index = 0; index < expression.size(); ++index) {

        switch (expression[index]) {
            case '0' :
            case '1' :
            case '2' :
            case '3' :
            case '4' :
            case '5' :
            case '6' :
            case '7' :
            case '8' :
            case '9' :
                if (!wasNum) {
                    tokens.push_back(token);
                    token = "";

                    wasNum = true;
                }
                
                token += expression[index];

                break;

            case '+' :
            case '-' :
            case '*' :
            case '/' :
                if (wasNum) {
                    tokens.push_back(token);
                    token = "";
                    wasNum = false;

                    token = expression[index];
                }

                break;

            default :
                break;

        }
    }

    tokens.push_back(token);

    return tokens;
}

class Fitness {
public:
    Fitness() { }
    Fitness(int pTarget)
        : target(pTarget)
        { }

    int operator()(const Chromosome& candidate) const {
        int value;

        vector<string> tokens = tokenize(expressionFromChromosome(candidate));

        value = stringToInt(tokens[0]);
        tokens.erase(tokens.begin());

        while (tokens.size() > 1) {
            int tokenValue = stringToInt(tokens[1]);

            char op = tokens[0][0];

            switch (op) {
                case '+' :
                    value += tokenValue;
                    break;
                case '-' :
                    value -= tokenValue;
                    break;
                case '*' :
                    value *= tokenValue;
                    break;
                case '/' :
                    if (tokenValue != 0)
                    value = (int) ( (double)value / tokenValue);
                    break;
            }

            tokens.erase(tokens.begin());
            tokens.erase(tokens.begin());
        }

        int score = target - value;
        if (score > 0) {
            score = -1 * score;
        }

        return score;
    }

private:
    int target;
};

void display(const Chromosome& candidate) {
    vector<string> tokens = tokenize(expressionFromChromosome(candidate));

    for (int index = 0; index < (tokens.size() - 1); ++index) {
        cout << tokens[index] << " ";
    }
    cout << tokens[tokens.size() - 1] << endl;
}

int main() {
    DataGenerator* rng = new DataGenerator(1024, 1024);
    int tournamentSize = 10;
    int populationSize = 100;
    int childrenPopulationSize = populationSize;
    int chromosomeSize = 60;

    double mutationRate = 0.05;
    double recombinationRate = 0.7;

    Fitness fitness(1293);
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

    Population firstGeneration = ga.get();

    int initialMaxFitness = fitness(ga.get()[0]);
    int initialMinFitness = initialMaxFitness;
    double initialSum = 0;
    for (int index = 0; index < firstGeneration.size(); ++index) {
        int currentFitness = fitness(firstGeneration[index]);

        if (currentFitness > initialMaxFitness) {
            initialMaxFitness = currentFitness;
        }

        if (currentFitness < initialMinFitness) {
            initialMinFitness = currentFitness;
        }

        initialSum += currentFitness;
    }
    double initialMeanFitness = initialSum / firstGeneration.size();

    cout << "Initial population statistics: " << endl
         << "  min:  " << initialMinFitness << endl
         << "  max:  " << initialMaxFitness << endl
         << "  mean: " << initialMeanFitness << endl;

    int round = 0;
    int populationFitness = 0;
    int maxRounds = 100;
    
    do {
        ga.step();

        int maxFitness = fitness(ga.get()[0]);
        int minFitness = maxFitness;
        double sum = 0;
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
    } while (round < maxRounds && populationFitness < 0);

    cout << "Converged in " << round << " generations." << endl;

    int maxFitness = fitness(ga.get()[0]);
    int minFitness = maxFitness;
    double sum = 0;
    int best = 0;
    for (int index = 0; index < ga.get().size(); ++index) {
        int currentFitness = fitness(ga.get()[index]);

        if (currentFitness > maxFitness) {
            maxFitness = currentFitness;
            best = index;
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

    fitness(ga.get()[best]);
    display(ga.get()[best]);

}

