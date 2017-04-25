#include "Phenome.h"

Phenome::Phenome(const Genome &genome) {
    NeuronLayers neurons = createNeuronLayers(genome.getNeurons());
    generateNeuronMatrices(neurons);
    generateWeightMatrices(genome.getConnections(), neurons);
}

NeuronLayers Phenome::createNeuronLayers(const Neurons &neurons) {
    NeuronLayers neuron_layers;

    for (auto neuron: neurons) {
        if (neuron->getLayerNumber() >= neuron_layers.size()) {
            neuron_layers.push_back(std::vector<PNeuron>());
        }

        neuron_layers[neuron->getLayerNumber()].push_back(neuron);
    }

    return neuron_layers;
}

void Phenome::generateNeuronMatrices(const NeuronLayers &neuron_layers) {
    neurons = std::vector<Matrix>(neuron_layers.size());
    unsigned long layer_size;

    for (int i = 0; i < neuron_layers.size(); ++i) {
        layer_size = neuron_layers[i].size();
        neurons[i] = Matrix(1, layer_size);
    }
}

void Phenome::generateWeightMatrices(const Connections &connection_list,
                                       const NeuronLayers &neuron_layers) {
    weights = std::vector<Matrix>(neuron_layers.size() - 1);
    unsigned long layer_size;
    unsigned long prev_layer_size;

    for (int i = 1; i < neuron_layers.size(); ++i) {
        layer_size = neuron_layers[i].size();
        prev_layer_size = neuron_layers[i-1].size();
        weights[i-1] = Matrix(prev_layer_size, layer_size, arma::fill::zeros);
    }

    fillWeightMatrices(connection_list, neuron_layers);
}

void Phenome::fillWeightMatrices(const Connections &connection_list,
                                   const NeuronLayers &neuron_layers) {
    PNeuron input_neuron, output_neuron;

    for (auto connection: connection_list) {
        input_neuron = connection->getInput();
        Coordinates input_coordinates = findNeuronCoordinates(input_neuron, neuron_layers);

        output_neuron = connection->getOutput();
        Coordinates output_coordinates = findNeuronCoordinates(output_neuron, neuron_layers);

        weights[input_coordinates.first](input_coordinates.second, output_coordinates.second) = connection->getWeight();
    }
}

Coordinates Phenome::findNeuronCoordinates(const PNeuron &neuron,
                                             const NeuronLayers &neuron_layers) {
    int layer_number = neuron->getLayerNumber();
    auto layer = neuron_layers[layer_number];

    auto iterator = std::find(layer.begin(), layer.end(), neuron);
    int neuron_number = (int) (iterator - layer.begin());

    return Coordinates(layer_number, neuron_number);
}

std::vector<Matrix> &Phenome::getNeurons() {
    return neurons;
}

const std::vector<Matrix> &Phenome::getWeights() const {
    return weights;
}

bool Phenome::operator==(const Phenome &rhs) const {
    if (neurons.size() != rhs.neurons.size() ||
        weights.size() != rhs.weights.size())
        return false;

    for (int i = 0; i < neurons.size(); ++i) {
        if ((int) arma::accu(neurons[i]) != (int) arma::accu(rhs.neurons[i]))
            return false;
    }

    for (int j = 0; j < weights.size(); ++j) {
        if ((int) arma::accu(weights[j]) != (int) arma::accu(rhs.weights[j]))
            return false;
    }

    return true;
}

bool Phenome::operator!=(const Phenome &rhs) const {
    return !(rhs == *this);
}
