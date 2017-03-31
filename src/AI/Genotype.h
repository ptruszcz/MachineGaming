//
// Created by fajqa on 25.03.17.
//

#ifndef MACHINEGAMING_GENOTYPE_H
#define MACHINEGAMING_GENOTYPE_H


#include <list>
#include <boost/shared_ptr.hpp>
#include "Neuron.h"
#include "Connection.h"
#include "Random.h"

enum MutationType {
    ADD_NEURON,
    ADD_CONNECTION,
    DISABLE_CONNECTION,
    RANDOMIZE_WEIGHT
};

class Genotype {
private:
    static Random random;

    int layer_counter;
    std::list<std::shared_ptr<Neuron>> neurons;
    std::list<Connection> connections;

    void addNeuron();
    void addNeuron(int layer_number);
    void addLayer(int size);
    void connectLayer(int layer_number);
    void addConnections(const std::vector<std::shared_ptr<Neuron>> &input_layer,
                        const std::vector<std::shared_ptr<Neuron>> &output_layer);
    void addConnection();
    void addConnection(const Neuron &input, const Neuron &output);
    void disableConnection();
    void randomizeWeight();
public:
    Genotype(int input_size, int hidden_layers, int output_size);
    static Genotype cross(const Genotype &parentA, const Genotype &parentB);
    void mutate(const MutationType &mutation_type);

    const std::list<std::shared_ptr<Neuron>> &getNeurons() const;
    const std::list<Connection> &getConnections() const;
};


#endif //MACHINEGAMING_GENOTYPE_H
