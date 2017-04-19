#ifndef MACHINEGAMING_NEURON_H
#define MACHINEGAMING_NEURON_H

#include <ostream>
#include <boost/shared_ptr.hpp>
#include "Counter.hpp"
#include "Gene.h"

class Neuron;
typedef std::shared_ptr<Neuron> PNeuron;
typedef std::vector<PNeuron> Neurons;

class Neuron : public Counter<Neuron>, public Gene {
private:
    int layer_number;

public:
    Neuron(int layer_number);
    Neuron(const Neuron &neuron);
    virtual PGene clone() const;

    virtual void mutate(MutationType mutation_type);

    int getLayerNumber() const;

    bool operator==(const Neuron &rhs) const;
    bool operator!=(const Neuron &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Neuron &neuron);
};


#endif //MACHINEGAMING_NEURON_H
