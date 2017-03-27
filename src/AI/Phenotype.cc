//
// Created by fajqa on 27.03.17.
//

#include "Phenotype.h"

Phenotype::Phenotype(Genotype genotype) {
    std::vector<int> layer_sizes = calculateNumberOfNeuronsPerLayer(genotype.getNeurons());
    generateNeuronMatrices(layer_sizes);
    generateWeightMatrices(genotype.getConnections(), layer_sizes);
}

std::vector<int> Phenotype::calculateNumberOfNeuronsPerLayer(const std::list<std::shared_ptr<Neuron>> &neuron_list) {
    std::vector<int> neuronsPerLayers = std::vector();

    for (auto neuron_ptr: neuron_list) {
        Neuron *neuron = neuron_ptr.get();

        if (neuron->getLayerNumber() >= neuronsPerLayers.size()) {
            neuronsPerLayers.push_back(1);
        }
        else {
            neuronsPerLayers[neuron->getLayerNumber()]++;
        }
    }

    return neuronsPerLayers;
}

void Phenotype::generateNeuronMatrices(const std::vector<int> &layer_sizes) {
    neurons = std::vector<arma::mat>(layer_sizes.size());
    int layer_size;

    for (int i = 0; i < layer_sizes.size(); ++i) {
        layer_size = layer_sizes[i];
        neurons[i] = arma::mat(1, layer_size);
    }
}

void Phenotype::generateWeightMatrices(const std::list<std::shared_ptr<Connection>> &connection_list,
                                       const std::vector<int> &layer_sizes) {
    weights = std::vector<arma::mat>(layer_sizes.size());
    int layer_size, prev_layer_size;

    for (int i = 1; i < layer_sizes.size(); ++i) {
        layer_size = layer_sizes[i];
        prev_layer_size = layer_sizes[i-1];
        weights[i-1] = arma::mat(prev_layer_size, layer_size, arma::fill::zeros);
    }

    //TODO: Weight assigning to proper places in matrix.
}

const std::vector<arma::mat> &Phenotype::getNeurons() const {
    return neurons;
}

const std::vector<arma::mat> &Phenotype::getWeights() const {
    return weights;
}
