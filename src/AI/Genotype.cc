//
// Created by fajqa on 25.03.17.
//

#include "Genotype.h"

Random Genotype::random = Random();

Genotype::Genotype(int input_size, int hidden_layers, int output_size) {
    layer_counter = 0;
    addLayer(input_size);

    for (int i = 1; i <= hidden_layers; ++i) {
        addLayer(1);
        connectLayer(i);
    }

    addLayer(output_size);
    connectLayer(layer_counter - 1);
}

Genotype::Genotype(const Genotype &genotype) {
    layer_counter = genotype.layer_counter;
    neurons = genotype.neurons;
    connections =  genotype.connections;
}

Genotype Genotype::cross(const Genotype &parentA, const Genotype &parentB) {
    // TODO Implementation of genotype crossing.
    return Genotype(0, 0, 0);
}

void Genotype::mutate(const MutationType &mutation_type) {
    switch (mutation_type) {
        case ADD_NEURON:
            addNeuron();
            break;

        case ADD_CONNECTION:
            addConnection();
            break;

        case DISABLE_CONNECTION:
            disableConnection();
            break;

        case RANDOMIZE_WEIGHT:
            randomizeWeight();
            break;
    }
}

PNeuron Genotype::addNeuron() {
    int random_layer_number = random.next(1, layer_counter);
    PNeuron neuron_ptr = addNeuron(random_layer_number);
    addConnectionToPrevLayer(neuron_ptr);
    addConnectionToNextLayer(neuron_ptr);

    return neuron_ptr;
}

PNeuron Genotype::addNeuron(int layer_number) {
    Neuron neuron_to_add = Neuron(layer_number);
    PNeuron neuron_ptr = std::make_shared<Neuron>(neuron_to_add);
    neurons.push_back(neuron_ptr);

    BOOST_LOG_TRIVIAL(debug) << "[ADD NEURON] " << neuron_to_add;

    return neuron_ptr;
}

void Genotype::addLayer(int size) {
    int layer_number = layer_counter;

    for (PNeuron neuron: neurons) {
        if (neuron->getLayerNumber() >= layer_number)
            neuron->incrementLayerNumber();
    }

    for (int i = 0; i < size; ++i) {
        addNeuron(layer_number);
    }

    ++layer_counter;
}

void Genotype::connectLayer(int layer_number) {
    std::vector<PNeuron> prev_layer_neurons = std::vector<PNeuron>();
    std::vector<PNeuron> this_layer_neurons = std::vector<PNeuron>();

    for (auto neuron: neurons) {
        if (neuron->getLayerNumber() == layer_number - 1) {
            prev_layer_neurons.push_back(neuron);
        } else if (neuron->getLayerNumber() == layer_number) {
            this_layer_neurons.push_back(neuron);
        }
    }

    addConnections(prev_layer_neurons, this_layer_neurons);
}

void Genotype::addConnections(const std::vector<PNeuron> &input_layer,
                              const std::vector<PNeuron> &output_layer) {
    for (auto input_neuron: input_layer) {
        for (auto output_neuron: output_layer) {
            addConnection(input_neuron, output_neuron);
        }
    }
}

void Genotype::addConnection() {
    int layer_number = random.next(1, layer_counter);
    PNeuron neuron = getRandomNeuron(layer_number);
    addConnectionToPrevLayer(neuron);
}

void Genotype::addConnectionToPrevLayer(const PNeuron &output) {
    PNeuron input;

    do {
        input = getRandomNeuron(output->getLayerNumber() - 1);
    } while (input == output);

    addConnection(input, output);
}

void Genotype::addConnectionToNextLayer(const PNeuron &input) {
    PNeuron output;

    do {
        output = getRandomNeuron(input->getLayerNumber() + 1);
    } while (output == input);

    addConnection(input, output);
}

void Genotype::addConnection(const PNeuron &input, const PNeuron &output) {
    Connection connection(input, output);
    connections.push_back(connection);

    BOOST_LOG_TRIVIAL(debug) << "[ADD CONNECTION] " << connection;
}

void Genotype::disableConnection() {
    int index = random.next(0, (int)(connections.size() - 1));
    BOOST_LOG_TRIVIAL(debug) << "[DISABLE CONNECTION BEFORE] " << connections[index];
    connections[index].enabled = false;

    BOOST_LOG_TRIVIAL(debug) << "[DISABLE CONNECTION AFTER] " << connections[index];
}

void Genotype::randomizeWeight() {
    int index = random.next(0, (int)(connections.size() - 1));
    BOOST_LOG_TRIVIAL(debug) << "[RANDOMIZE WEIGHT BEFORE] " << connections[index];
    connections[index].randomizeWeight();

    BOOST_LOG_TRIVIAL(debug) << "[RANDOMIZE WEIGHT AFTER] " << connections[index];
}

const std::vector<PNeuron> & Genotype::getNeurons() const {
    return neurons;
}

const PNeuron Genotype::getRandomNeuron(int layer_number) const {
    std::vector<PNeuron> matches;
    for (auto neuron: neurons) {
        if (neuron->getLayerNumber() == layer_number)
            matches.push_back(neuron);
    }

    int index = random.next(0, (int) matches.size() - 1);

    return matches[index];
}

const std::vector<Connection> & Genotype::getConnections() const {
    return connections;
}

bool Genotype::operator==(const Genotype &rhs) const {
    return layer_counter == rhs.layer_counter &&
           neurons == rhs.neurons &&
           connections == rhs.connections;
}

bool Genotype::operator!=(const Genotype &rhs) const {
    return !(rhs == *this);
}