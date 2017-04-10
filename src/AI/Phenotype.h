//
// Created by fajqa on 27.03.17.
//

#ifndef MACHINEGAMING_PHENOTYPE_H
#define MACHINEGAMING_PHENOTYPE_H


#include <armadillo>
#include "Genotype.h"

typedef std::pair<int, int> Coordinates;
typedef std::vector<std::vector<PNeuron>> NeuronLayers;

class Phenotype {
private:
    std::vector<arma::mat> neurons;
    std::vector<arma::mat> weights;

    NeuronLayers createNeuronLayers(const std::vector<PNeuron> &neurons);
    void generateNeuronMatrices(const NeuronLayers &neuron_layers);
    void generateWeightMatrices(const std::vector<Connection> &connection_list,
                                const NeuronLayers &neuron_layers);
    void fillWeightMatrices(const std::vector<Connection> &connection_list, const NeuronLayers &neuron_layers);
    Coordinates findNeuronCoordinates(const PNeuron &neuron, const NeuronLayers &neuron_layers);

public:
    Phenotype(Genotype genotype);

    const std::vector<arma::mat> &getNeurons() const;
    const std::vector<arma::mat> &getWeights() const;

    bool operator==(const Phenotype &rhs) const;
    bool operator!=(const Phenotype &rhs) const;
};


#endif //MACHINEGAMING_PHENOTYPE_H
