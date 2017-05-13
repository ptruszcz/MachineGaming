/*
File created by: Jakub Fajkowski
*/

#ifndef MACHINEGAMING_NEURON_H
#define MACHINEGAMING_NEURON_H

#include <ostream>
#include <memory>
#include "Counter.hpp"
#include "Gene.h"

class Neuron;
typedef std::shared_ptr<Neuron> PNeuron;
typedef std::vector<PNeuron> Neurons;

class Neuron : public Counter<Neuron>, public Gene {
private:
    int layer_number_;

public:
    Neuron(int layer_number);
    Neuron(const Neuron &neuron);

    virtual PGene clone() const;
    virtual void mutate(MutationType mutation_type);

    bool operator==(const Neuron &rhs) const;
    bool operator!=(const Neuron &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Neuron &neuron);

    int getLayerNumber() const;
};


#endif //MACHINEGAMING_NEURON_H
