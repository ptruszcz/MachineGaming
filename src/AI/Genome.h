/**
 * @class Genome
 * @brief Represents genome.
 * @details It consists of two genotypes - one representing Neurons
 * and other representing Connections. It applies specified
 * mutation types (like adding, deleting or modyfing Neuron/Connection)
 * It allows crossing with other genome.
 * @author Jakub Fajkowski
 */

#ifndef MACHINEGAMING_GENOME_H
#define MACHINEGAMING_GENOME_H


#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <armadillo>
#include <ostream>
#include "Neuron.h"
#include "Connection.h"
#include "Random.h"
#include "MutationType.h"
#include "Genotype.hpp"

class Genome;
typedef std::unique_ptr<Genome> PGenome;

class Genome {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & neurons_;
        ar & connections_;
    }

    static Random random;
    static int layer_counter;
    
    Genotype<Neuron> neurons_;
    Genotype<Connection> connections_;

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
    Genome();
    Genome(int input_size, int hidden_layers, int output_size);
    Genome(const Genotype<Neuron> &neurons, const Genotype<Connection> &connections);
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
