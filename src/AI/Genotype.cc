//
// Created by fajqa on 25.03.17.
//

#include <armadillo>
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

Genotype Genotype::cross(const Genotype &parentA, const Genotype &parentB) {
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

void Genotype::addNeuron() {
    int random_layer_number = random.next(1, layer_counter);
    addNeuron(random_layer_number);
}

void Genotype::addNeuron(int layer_number) {
    Neuron neuron_to_add = Neuron(layer_number);
    neurons.push_back(std::make_shared<Neuron>(neuron_to_add));
}

void Genotype::addLayer(int size) {
    int layer_number = layer_counter;
    Neuron *neuron;

    for(auto neuron_ptr: neurons) {
        neuron = neuron_ptr.get();

        if (neuron->getLayerNumber() >= layer_number)
            neuron->incrementLayerNumber();
    }

    for (int i = 0; i < size; ++i) {
        addNeuron(layer_number);
    }

    ++layer_counter;
}

void Genotype::connectLayer(int layer_number) {
    std::vector<std::shared_ptr<Neuron>> prev_layer_neurons = std::vector<std::shared_ptr<Neuron>>();
    std::vector<std::shared_ptr<Neuron>> this_layer_neurons = std::vector<std::shared_ptr<Neuron>>();
    Neuron *neuron;

    for (auto neuron_ptr: neurons) {
        neuron = neuron_ptr.get();

        if (neuron->getLayerNumber() == layer_number - 1) {
            prev_layer_neurons.push_back(neuron_ptr);
        } else if (neuron->getLayerNumber() == layer_number) {
            this_layer_neurons.push_back(neuron_ptr);
        }
    }

    addConnections(prev_layer_neurons, this_layer_neurons);
}

void Genotype::addConnections(const std::vector<std::shared_ptr<Neuron>> &input_layer,
                              const std::vector<std::shared_ptr<Neuron>> &output_layer) {
    Neuron *input_neuron;
    Neuron *output_neuron;

    for (auto input_neuron_ptr: input_layer) {
        input_neuron = input_neuron_ptr.get();

        for (auto output_neuron_ptr: output_layer) {
            output_neuron = output_neuron_ptr.get();

            addConnection(*input_neuron, *output_neuron);
        }
    }
}

void Genotype::addConnection() {

}

void Genotype::addConnection(const Neuron &input, const Neuron &output) {
    std::shared_ptr<Neuron> input_ptr = std::make_shared<Neuron>(input);
    std::shared_ptr<Neuron> output_ptr = std::make_shared<Neuron>(output);
    Connection connection(input_ptr, output_ptr);
    connections.push_back(connection);
}

void Genotype::disableConnection() {

}

void Genotype::randomizeWeight() {

}

const std::list<std::shared_ptr<Neuron>> &Genotype::getNeurons() const {
    return neurons;
}

const std::list<Connection> &Genotype::getConnections() const {
    return connections;
}
