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
    static Genotype cross(const Genotype &parentA, const Genotype &parentB);

    const std::list<Neuron> &getNeurons() const;
    const std::list<Connection> &getConnections() const;
};


#endif //MACHINEGAMING_GENOTYPE_H
