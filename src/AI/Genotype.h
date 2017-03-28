//
// Created by fajqa on 25.03.17.
//

#ifndef MACHINEGAMING_GENOTYPE_H
#define MACHINEGAMING_GENOTYPE_H


#include <list>
#include "Neuron.h"
#include "Connection.h"

enum MutationType {
    ADD_NEURON,
    ADD_CONNECTION,
    DISABLE_CONNECTION,
    RANDOMIZE_WEIGHT
};

class Genotype {
private:
    std::list<std::shared_ptr<Neuron>> neurons;
    std::list<std::shared_ptr<Connection>> connections;

    void addNeuron();
    void addConnection();
    void disableConnection();
    void randomizeWeight();
public:
    Genotype();
    static Genotype cross(const Genotype &parentA, const Genotype &parentB);
    void mutate(MutationType mutation_type);

    const std::list<std::shared_ptr<Neuron>> &getNeurons() const;
    const std::list<std::shared_ptr<Connection>> &getConnections() const;
};


#endif //MACHINEGAMING_GENOTYPE_H
