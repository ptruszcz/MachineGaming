/**
 * @class Neuron
 * @brief Represents network neurons.
 * @details It provides Gene methods. It is stored in Genotype
 * and when needed Phenome connection matrices are built using it.
 * @author Jakub Fajkowski
 */

#ifndef MACHINEGAMING_NEURON_H
#define MACHINEGAMING_NEURON_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <ostream>
#include <memory>

#include "Counter.hpp"
#include "Gene.h"

class Neuron;
typedef std::shared_ptr<Neuron> PNeuron;
typedef std::vector<PNeuron> Neurons;

class Neuron : public Counter<Neuron>, public Gene {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Counter<Neuron>>(*this);
        ar & boost::serialization::base_object<Gene>(*this);
        ar & layer_number_;
    }

    int layer_number_;

public:
    Neuron();
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
