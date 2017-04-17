#ifndef MACHINEGAMING_GENOTYPE_H
#define MACHINEGAMING_GENOTYPE_H


#include <list>
#include <armadillo>
#include "boost/log/trivial.hpp"
#include "Neuron.h"
#include "Connection.h"
#include "Random.h"

enum MutationType {
    ADD_NEURON,
    ADD_CONNECTION,
    DISABLE_CONNECTION,
    RANDOMIZE_WEIGHT
};

class Genome {
private:
    static Random random;

    int layer_counter;
    // TODO Change vector structure (index == (neuron/connection).getOrderNumber())
    std::vector<PNeuron> neurons;
    std::vector<Connection> connections;

    PNeuron addNeuron();
    PNeuron addNeuron(int layer_number);

    void addLayer(int size);
    void connectLayer(int layer_number);
    void addConnections(const std::vector<PNeuron> &input_layer,
                        const std::vector<PNeuron> &output_layer);
    void addConnection();
    void addConnectionToPrevLayer(const PNeuron &output);
    void addConnectionToNextLayer(const PNeuron &input);
    void addConnection(const PNeuron &input, const PNeuron &output);
    void disableConnection();
    void randomizeWeight();

    const PNeuron getRandomNeuron(int layer_number) const;
public:
    Genome(int input_size, int hidden_layers, int output_size);
    Genome(const Genome &genome);

    static Genome cross(const Genome &parentA, const Genome &parentB);
    void mutate(const MutationType &mutation_type);

    const std::vector<PNeuron> & getNeurons() const;
    const std::vector<Connection> & getConnections() const;

    bool operator==(const Genome &rhs) const;
    bool operator!=(const Genome &rhs) const;
};


#endif //MACHINEGAMING_GENOTYPE_H
