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
    neurons_ = std::vector<Matrix>(neuron_layers.size());
    unsigned long layer_size;

    for (int i = 0; i < neuron_layers.size(); ++i) {
        layer_size = neuron_layers[i].size();
        neurons_[i] = Matrix(1, layer_size);
    }
}

void Phenome::generateWeightMatrices(const Connections &connection_list,
                                       const NeuronLayers &neuron_layers) {
    weights_ = std::vector<Matrix>(neuron_layers.size() - 1);
    unsigned long layer_size;
    unsigned long prev_layer_size;

    for (int i = 1; i < neuron_layers.size(); ++i) {
        layer_size = neuron_layers[i].size();
        prev_layer_size = neuron_layers[i-1].size();
        weights_[i-1] = Matrix(prev_layer_size, layer_size, arma::fill::zeros);
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

        weights_[input_coordinates.first](input_coordinates.second, output_coordinates.second) = connection->getWeight();
    }
}

Coordinates Phenome::findNeuronCoordinates(const PNeuron &neuron,
                                             const NeuronLayers &neuron_layers) {
    int layer_number = neuron->getLayerNumber();
    auto layer = neuron_layers[layer_number];

    int neuron_number = -1;
    for (int i = 0; i < layer.size(); ++i) {
        if (*layer[i] == *neuron)
            neuron_number = i;
    }

    return Coordinates(layer_number, neuron_number);
}

bool Phenome::operator==(const Phenome &rhs) const {
    if (neurons_.size() != rhs.neurons_.size() ||
        weights_.size() != rhs.weights_.size())
        return false;

    for (int i = 0; i < neurons_.size(); ++i) {
        if ((int) arma::accu(neurons_[i]) != (int) arma::accu(rhs.neurons_[i]))
            return false;
    }

    for (int j = 0; j < weights_.size(); ++j) {
        if ((int) arma::accu(weights_[j]) != (int) arma::accu(rhs.weights_[j]))
            return false;
    }

    return true;
}

bool Phenome::operator!=(const Phenome &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Phenome &phenome) {
    os << "neurons: " << phenome.neurons_.size() << " weights: " << phenome.weights_.size();
    return os;
}

std::vector<Matrix> &Phenome::getNeurons() {
    return neurons_;
}

const std::vector<Matrix> &Phenome::getWeights() const {
    return weights_;
}
