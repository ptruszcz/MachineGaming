/*
File created by: Jakub Fajkowski
Modified by: Piotr Truszczyński
*/

#ifndef MACHINEGAMING_GENOME_H
#define MACHINEGAMING_GENOME_H

#include <armadillo>
#include <ostream>
#include "Neuron.h"
#include "Connection.h"
#include "Random.h"
#include "MutationType.h"
#include "Genotype.h"

class Genome;
typedef std::unique_ptr<Genome> PGenome;

class Genome {
private:
    static Random random;
    static int layer_counter;
    
    Genotype neurons_;
    Genotype connections_;

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
    void deleteNeuronConnections(const Neuron &neuron);
    void randomizeWeight();

    int layerSize(int layer_number);
    PNeuron getRandomNeuron(int layer_number);
    PConnection getRandomConnection();

public:
    Genome(int input_size, int hidden_layers, int output_size);
    Genome(const Genotype &neurons, const Genotype &connections);
    Genome(const Genome &genome);

    static PGenome crossover(Genome &parentA, Genome &parentB);
    void mutate(const MutationType &mutation_type);

    bool operator==(const Genome &rhs) const;
    bool operator!=(const Genome &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Genome &genome);

    Neurons getNeurons() const;
    Connections getConnections() const;
};


#endif //MACHINEGAMING_GENOME_H
