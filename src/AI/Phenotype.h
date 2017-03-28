//
// Created by fajqa on 27.03.17.
//

#ifndef MACHINEGAMING_PHENOTYPE_H
#define MACHINEGAMING_PHENOTYPE_H


#include <armadillo>
#include "Genotype.h"
#include "Coordinates.h"

typedef std::vector<std::vector<std::shared_ptr<Neuron>>> NeuronLayers;

class Phenotype {
private:
    std::vector<arma::mat> neurons;
    std::vector<arma::mat> weights;

    NeuronLayers createNeuronLayers(const std::list<std::shared_ptr<Neuron>> &neuron_list);
    void generateNeuronMatrices(const NeuronLayers &neuron_layers);
    void generateWeightMatrices(const std::list<std::shared_ptr<Connection>> &connection_list,
                                const NeuronLayers &neuron_layers);
    Coordinates findNeuronCoordinates(const Neuron &neuron, const NeuronLayers &neuron_layers);

public:
    Phenotype(Genotype genotype);

    const std::vector<arma::mat> &getNeurons() const;
    const std::vector<arma::mat> &getWeights() const;
};


#endif //MACHINEGAMING_PHENOTYPE_H
