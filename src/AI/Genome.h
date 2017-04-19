#ifndef MACHINEGAMING_GENOME_H
#define MACHINEGAMING_GENOME_H


#include <list>
#include <armadillo>
#include "boost/log/trivial.hpp"
#include "Neuron.h"
#include "Connection.h"
#include "Random.h"
#include "MutationType.h"
#include "Genotype.h"

class Genome {
private:
    static Random random;
    static int layer_counter;
    
    Genotype neurons;
    Genotype connections;

    void addNeuron();
    PNeuron addNeuron(int layer_number);

    void deleteNeuron();

    void addLayer(int size);
    void connectLayer(int layer_number);
    void addConnections(const Neurons &input_layer, const Neurons &output_layer);
    void addConnection();
    void addConnectionToPrevLayer(const PNeuron &output);
    void addConnectionToNextLayer(const PNeuron &input);
    void addConnection(const PNeuron &input, const PNeuron &output);
    void deleteConnection();
    void randomizeWeight();

    PNeuron getRandomNeuron(int layer_number);
    PConnection getRandomConnection();
public:
    Genome(int input_size, int hidden_layers, int output_size);
    Genome(Genotype neurons, Genotype connections);
    Genome(const Genome &genome);

    static Genome crossover(Genome &parentA, Genome &parentB);
    void mutate(const MutationType &mutation_type);

    Genes getNeurons();
    Genes getConnections();

    bool operator==(const Genome &rhs) const;
    bool operator!=(const Genome &rhs) const;

    void deleteNeuronConnections(const PNeuron &neuron);
};


#endif //MACHINEGAMING_GENOME_H
