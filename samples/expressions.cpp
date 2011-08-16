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

struct Triple {
    int first;
    int second;
    int third;
    bool hasFirst;
    bool hasSecond;
    bool hasThird;
};

class Fitness {
public:
    Fitness() { }
    Fitness(Chromosome pTarget, vector<Triple> pData)
        : target(pTarget)
        , data(pData)
        { }

    int operator()(const Chromosome& candidate) const {
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

        for (int index = 0; index < tokens.size(); ++index) {
            cout << tokens[index] << " ";
        }   cout << " = ";


        while (tokens.size() > 1) {
            if (tokens[0] == "x" || tokens[0] == "y") {
                tokens.erase(tokens.begin());
                tokens.erase(tokens.begin());
                continue;
            }

            int tokenValue = 0;
            token = tokens[0];
            for (int loc = 0; loc < token.size(); ++loc) {
                tokenValue = 10 * tokenValue + (token[loc] - '0');
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

        cout << value << endl;
        cout << expression << endl;

        return 0;
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
    vector<Triple> data; //TODO: fill these in

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
    ga.step();

    Population firstGeneration = ga.get();

}

