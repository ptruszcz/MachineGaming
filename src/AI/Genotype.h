//
// Created by fajqa on 25.03.17.
//

#ifndef MACHINEGAMING_GENOTYPE_H
#define MACHINEGAMING_GENOTYPE_H


#include <list>
#include "Neuron.h"
#include "Connection.h"

class Genotype {
private:
    std::list<Neuron> neurons;
    std::list<Connection> connections;

public:
    arma::mat generateNeuronMatrix();
    arma::mat generateWeightMatrix();
    static Genotype cross(const Genotype &parentA, const Genotype &parentB);
};


#endif //MACHINEGAMING_GENOTYPE_H
