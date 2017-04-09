//
// Created by fajqa on 27.03.17.
//

#include "Phenotype.h"

Phenotype::Phenotype(Genotype genotype) {
    auto layer_sizes = createNeuronLayers(genotype.getNeurons());
    generateNeuronMatrices(layer_sizes);
    generateWeightMatrices(genotype.getConnections(), layer_sizes);
}

NeuronLayers Phenotype::createNeuronLayers(const std::vector<PNeuron> &neuron_list) {
    NeuronLayers neuron_layers;

    for (auto neuron_ptr: neuron_list) {
        Neuron *neuron = neuron_ptr.get();

        if (neuron->getLayerNumber() >= neuron_layers.size()) {
            neuron_layers.push_back(std::vector<PNeuron>());
        }

        neuron_layers[neuron->getLayerNumber()].push_back(neuron_ptr);
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
    weights = std::vector<arma::mat>(neuron_layers.size());
    unsigned long layer_size;
    unsigned long prev_layer_size;

    for (int i = 1; i < neuron_layers.size(); ++i) {
        layer_size = neuron_layers[i].size();
        prev_layer_size = neuron_layers[i-1].size();
        weights[i-1] = arma::mat(prev_layer_size, layer_size, arma::fill::zeros);
    }

    for (auto connection: connection_list) {
        if (connection.isEnabled()) {
            Neuron *input_neuron = connection.getInput().get();
            Coordinates input_coordinates = findNeuronCoordinates(*input_neuron, neuron_layers);

            Neuron *output_neuron = connection.getOutput().get();
            Coordinates output_coordinates = findNeuronCoordinates(*output_neuron, neuron_layers);

            weights[input_coordinates.first][output_coordinates.second] = connection.getWeight();
        }
    }
}

Coordinates Phenotype::findNeuronCoordinates(const Neuron &neuron, const NeuronLayers &neuron_layers) {
    for (int layer_number = 0; layer_number < neuron_layers.size(); ++layer_number) {
        for (int neuron_number = 0; neuron_number < neuron_layers[layer_number].size(); ++neuron_number) {
            if (neuron == *neuron_layers[layer_number][neuron_number].get())
                return Coordinates(layer_number, neuron_number);
        }
    }
}

const std::vector<arma::mat> &Phenotype::getNeurons() const {
    return neurons;
}

const std::vector<arma::mat> &Phenotype::getWeights() const {
    return weights;
}
