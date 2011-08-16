//file:     expressions.cpp
//author:   ntietz
//date:     2011.8.13
// Sample expression-creating program

#include "ga/ga.h"
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

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
    else if (bits == "1110")
        return 'x';
    else if (bits == "1111")
        return 'y';
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
        case 'x' :
            return "1110";
        case 'y' :
            return "1111";

    }
}

class Triple {
public:
    Triple(int x, int y, int z)
        : first(x)
        , second(y)
        , third(z)
        { }

    int first;
    int second;
    int third;
};

class Fitness {
public:
    Fitness() { }
    Fitness(Chromosome pTarget, vector<Triple> pData)
        : target(pTarget)
        , data(pData)
        { }

    int operator()(const Chromosome& candidate) const {
        int score = 0;

        int numBlocks = candidate.size() / 4;

        string expression = "";

        for (int index = 0; index < numBlocks; ++index) {
            string bits = "";
            for (int loc = 0; loc < 4; ++loc) {
                bits += (candidate[4*index + loc] == true ? '1' : '0');
            }

            expression += convertFromBits(bits);

        }

        vector<string> tokens;
        string token = "";
        bool wasNum = false;
        bool wasVar = false;
        bool wasOp = false;
        bool pushed = false;

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
                    if (wasVar || wasOp) {
                        tokens.push_back(token);
                        token = "";

                        if (wasVar) {
                            tokens.push_back("*");
                        }

                        wasVar = false;
                        wasOp = false;
                        pushed = true;
                    }
                    wasNum = true;
                    
                    token += expression[index];
                    pushed = false;

                    break;

                case '+' :
                case '-' :
                case '*' :
                case '/' :
                    if (wasNum || wasVar) {
                        tokens.push_back(token);
                        token = "";
                        wasNum = false;
                        wasVar = false;
                        pushed = true;
                    }

                    if (! wasOp) {
                        token += expression[index];
                        pushed = false;
                    }

                    wasOp = true;
                    break;

                case 'x' :
                case 'y' :
                    if (wasNum || wasOp) {
                        if (wasNum) {
                        }
                        tokens.push_back(token);
                        token = "";

                        if (! wasVar) {
                            if (wasNum) {
                                tokens.push_back("*");
                            }
                            token = expression[index];
                        }

                        wasNum = false;
                        wasOp = false;
                        pushed = true;
                    }

                    wasVar = true;
                    break;

                default :
                    break;

            }
        }

        if (!pushed) {
            tokens.push_back(token);
        }

        if (tokens[0][0] < '0' || tokens[0][0] > '9') {
            tokens.insert(tokens.begin(), "0");
        }

        int value = 0;

        /*
        for (int index = 0; index < tokens.size(); ++index) {
            cout << tokens[index] << " ";
        }   cout << " = ";
        */

        vector<string> original = tokens;

        for (int index = 0; index < data.size(); ++index) {
            tokens = original;
            int xValue = data[index].first;
            int yValue = data[index].second;
            int expected = data[index].third;
            value = 0;

            while (tokens.size() > 1) {
                int tokenValue = 0;

                if (tokens[0] == "x") {
                    tokenValue = xValue;
                } else if (tokens[0] == "y") {
                    tokenValue = yValue;
                } else {
                    token = tokens[0];
                    for (int loc = 0; loc < token.size(); ++loc) {
                        tokenValue = 10 * tokenValue + (token[loc] - '0');
                    }
                }

                char op = tokens[1][0];

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
                        value /= tokenValue;
                        break;
                }

                tokens.erase(tokens.begin());
                tokens.erase(tokens.begin());
            }

            int diff = expected - value;
            if (diff < 0) {
                diff = -1 * diff;
            }

            score -= diff;
            score += (original.size());

        }

        cout << value << endl;
        cout << expression << endl;

        return score;
    }

private:
    Chromosome target;
    vector<Triple> data;
};

int main() {
    DataGenerator* rng = new DataGenerator(1024, 1024);
    int tournamentSize = 10;
    int populationSize = 100;
    int childrenPopulationSize = populationSize;
    int chromosomeSize = 40;

    double mutationRate = 0.01;
    double recombinationRate = 0.5;

    Chromosome target; //TODO: fill these in
    vector<Triple> data;
    //data.push_back(Triple(0, 0, 98));
    //data.push_back(Triple(120,-192, 98));
    //data.push_back(Triple(-392, -10210, 98));
    data.push_back(Triple(2, 2, 10));
    data.push_back(Triple(100, 1, 101));
    data.push_back(Triple(-10, 10, 990));

    Fitness fitness(target, data);
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

    int initialMaxFitness = 0;
    int initialMinFitness = chromosomeSize;
    int initialSum = 0;
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
    } while (round < maxRounds && populationFitness != 25);

    cout << "Converged in " << round << " generations." << endl;

    int maxFitness = 0;
    int minFitness = chromosomeSize;
    int sum = 0;
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

}

