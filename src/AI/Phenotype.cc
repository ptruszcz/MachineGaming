//
// Created by fajqa on 27.03.17.
//

#include "Phenotype.h"

Phenotype::Phenotype(Genotype genotype) {
    NeuronLayers neurons = createNeuronLayers(genotype.getNeurons());
    generateNeuronMatrices(neurons);
    generateWeightMatrices(genotype.getConnections(), neurons);
}

NeuronLayers Phenotype::createNeuronLayers(const std::vector<PNeuron> &neurons) {
    NeuronLayers neuron_layers;

    for (auto neuron: neurons) {
        if (neuron->getLayerNumber() >= neuron_layers.size()) {
            neuron_layers.push_back(std::vector<PNeuron>());
        }

        neuron_layers[neuron->getLayerNumber()].push_back(neuron);
    }

    return neuron_layers;
}

void Phenotype::generateNeuronMatrices(const NeuronLayers &neuron_layers) {
    neurons = std::vector<arma::mat>(neuron_layers.size());
    unsigned long layer_size;

    for (int i = 0; i < neuron_layers.size(); ++i) {
        layer_size = neuron_layers[i].size();
        neurons[i] = arma::mat(1, layer_size);
    }
}

void Phenotype::generateWeightMatrices(const std::vector<Connection> &connection_list,
                                       const NeuronLayers &neuron_layers) {
    weights = std::vector<arma::mat>(neuron_layers.size() - 1);
    unsigned long layer_size;
    unsigned long prev_layer_size;

    for (int i = 1; i < neuron_layers.size(); ++i) {
        layer_size = neuron_layers[i].size();
        prev_layer_size = neuron_layers[i-1].size();
        weights[i-1] = arma::mat(prev_layer_size, layer_size, arma::fill::zeros);
    }

    fillWeightMatrices(connection_list, neuron_layers);
}

void Phenotype::fillWeightMatrices(const std::vector<Connection> &connection_list,
                                   const NeuronLayers &neuron_layers) {
    for (auto connection: connection_list) {
        if (connection.isEnabled()) {
            PNeuron input_neuron = connection.getInput();
            Coordinates input_coordinates = findNeuronCoordinates(input_neuron, neuron_layers);

            PNeuron output_neuron = connection.getOutput();
            Coordinates output_coordinates = findNeuronCoordinates(output_neuron, neuron_layers);

            weights[input_coordinates.first][output_coordinates.second] = connection.getWeight();
        }
    }
}

Coordinates Phenotype::findNeuronCoordinates(const PNeuron &neuron,
                                             const NeuronLayers &neuron_layers) {
    int layer_number = neuron->getLayerNumber();
    auto layer = neuron_layers[layer_number];

    auto iterator = std::find(layer.begin(), layer.end(), neuron);
    int neuron_number = (int) (iterator - layer.begin());

    return Coordinates(layer_number, neuron_number);
}

const std::vector<arma::mat> &Phenotype::getNeurons() const {
    return neurons;
}

const std::vector<arma::mat> &Phenotype::getWeights() const {
    return weights;
}
