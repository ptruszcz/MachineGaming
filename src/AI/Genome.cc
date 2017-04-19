#include "Genome.h"

Random Genome::random = Random();

Genome::Genome(int input_size, int hidden_layers, int output_size) {
    layer_counter = 0;
    addLayer(input_size);

    for (int i = 1; i <= hidden_layers; ++i) {
        addLayer(1);
        connectLayer(i);
    }

    addLayer(output_size);
    connectLayer(layer_counter - 1);
}

Genome::Genome(const Genome &genome) {
    layer_counter = genome.layer_counter;
    neurons = genome.neurons;
    connections =  genome.connections;
}

Genome Genome::crossover(const Genome &parentA, const Genome &parentB) {
    // TODO Implementation of genome crossing.
    return Genome(0, 0, 0);
}

void Genome::mutate(const MutationType &mutation_type) {
    switch (mutation_type) {
        case ADD_NEURON:
            addNeuron();
            break;

        case DELETE_NEURON:
            deleteNeuron();
            break;

        case ADD_CONNECTION:
            addConnection();
            break;

        case DELETE_CONNECTION:
            deleteConnection();
            break;

        case RANDOMIZE_WEIGHT:
            randomizeWeight();
            break;
    }
}

void Genome::addLayer(int size) {
    int layer_number = layer_counter;

    for (int i = 0; i < size; ++i) {
        addNeuron(layer_number);
    }

    ++layer_counter;
}

void Genome::addNeuron() {
    int random_layer_number = random.next(1, layer_counter);
    PNeuron neuron_ptr = addNeuron(random_layer_number);
    addConnectionToPrevLayer(neuron_ptr);
    addConnectionToNextLayer(neuron_ptr);
}

PNeuron Genome::addNeuron(int layer_number) {
    Neuron neuron_to_add = Neuron(layer_number);
    PNeuron neuron_ptr = std::make_shared<Neuron>(neuron_to_add);
    neurons.insert(neuron_ptr);

    BOOST_LOG_TRIVIAL(debug) << "[ADD NEURON] " << neuron_to_add;

    return neuron_ptr;
}

void Genome::deleteNeuron() {

}

void Genome::connectLayer(int layer_number) {
    std::vector<PNeuron> prev_layer_neurons = std::vector<PNeuron>();
    std::vector<PNeuron> this_layer_neurons = std::vector<PNeuron>();

    PNeuron neuron;
    for (auto gene: getNeurons()) {
        neuron = std::static_pointer_cast<Neuron>(gene);
        if (neuron->getLayerNumber() == layer_number - 1) {
            prev_layer_neurons.push_back(neuron);
        } else if (neuron->getLayerNumber() == layer_number) {
            this_layer_neurons.push_back(neuron);
        }
    }

    addConnections(prev_layer_neurons, this_layer_neurons);
}

void Genome::addConnections(const std::vector<PNeuron> &input_layer,
                              const std::vector<PNeuron> &output_layer) {
    for (auto input_neuron: input_layer) {
        for (auto output_neuron: output_layer) {
            addConnection(input_neuron, output_neuron);
        }
    }
}

void Genome::addConnection() {
    int layer_number = random.next(1, layer_counter);
    PNeuron neuron = getRandomNeuron(layer_number);
    addConnectionToPrevLayer(neuron);
}

void Genome::addConnectionToPrevLayer(const PNeuron &output) {
    PNeuron input;

    do {
        input = getRandomNeuron(output->getLayerNumber() - 1);
    } while (input == output);

    addConnection(input, output);
}

void Genome::addConnectionToNextLayer(const PNeuron &input) {
    PNeuron output;

    do {
        output = getRandomNeuron(input->getLayerNumber() + 1);
    } while (output == input);

    addConnection(input, output);
}

void Genome::addConnection(const PNeuron &input, const PNeuron &output) {
    Connection connection(*input, *output);
    connections.insert(std::make_shared<Connection>(connection));

    BOOST_LOG_TRIVIAL(debug) << "[ADD CONNECTION] " << connection;
}

void Genome::deleteConnection() {
    int index = random.next(0, (int)(getConnections().size() - 1));
    BOOST_LOG_TRIVIAL(debug) << "[DISABLE CONNECTION BEFORE] " << connections[index];
    //connections[index] = nullptr;

    BOOST_LOG_TRIVIAL(debug) << "[DISABLE CONNECTION AFTER] " << connections[index];
}

void Genome::randomizeWeight() {
    int index = random.next(0, (int)(getConnections().size() - 1));
    BOOST_LOG_TRIVIAL(debug) << "[RANDOMIZE WEIGHT BEFORE] " << connections[index];
    connections[index]->mutate(RANDOMIZE_WEIGHT);

    BOOST_LOG_TRIVIAL(debug) << "[RANDOMIZE WEIGHT AFTER] " << connections[index];
}

PNeuron Genome::getRandomNeuron(int layer_number) {
    std::vector<PNeuron> matches;
    PNeuron neuron;
    for (auto gene: getNeurons()) {
        neuron = std::static_pointer_cast<Neuron>(gene);
        if (neuron->getLayerNumber() == layer_number)
            matches.push_back(neuron);
    }

    int index = random.next(0, (int) matches.size() - 1);

    return matches[index];
}

Genes Genome::getNeurons() {
    return neurons.getGenes();
}

Genes Genome::getConnections() {
    return connections.getGenes();
}

bool Genome::operator==(const Genome &rhs) const {
    return layer_counter == rhs.layer_counter &&
           neurons == rhs.neurons &&
           connections == rhs.connections;
}

bool Genome::operator!=(const Genome &rhs) const {
    return !(rhs == *this);
}
