#include "Genome.h"

Random Genome::random = Random();
int Genome::layer_counter = 0;

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

Genome::Genome(Genotype neurons, Genotype connections) {
    this->neurons = Genotype(neurons);
    this->connections = Genotype(connections);
}

Genome::Genome(const Genome &genome) {
    layer_counter = genome.layer_counter;
    neurons = *genome.neurons.clone();
    connections = *genome.connections.clone();
}

Genome Genome::crossover(Genome &parentA, Genome &parentB) {
    Genotype neurons = Genotype::crossover(parentA.neurons, parentB.neurons);
    Genotype connections = *Genotype::crossover(parentA.connections, parentB.connections).clone();

    return Genome(neurons, connections);
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
    int random_layer_number = random.next(1, layer_counter);
    PNeuron neuron_to_delete = getRandomNeuron(random_layer_number);
    neurons.erase(neuron_to_delete);
    deleteNeuronConnections(neuron_to_delete);

    BOOST_LOG_TRIVIAL(debug) << "[DELETE NEURON] " << neuron_to_delete;
}

void Genome::deleteNeuronConnections(const PNeuron &neuron) {
    Connections matches;
    PConnection connection;

    for (auto gene: getConnections()) {
        connection = std::static_pointer_cast<Connection>(gene);

        if (connection->getInput() == neuron || connection->getOutput() == neuron) {
            matches.push_back(connection);
        }
    }

    for (auto connection: matches) {
        connections.erase(connection);
    }
}

void Genome::connectLayer(int layer_number) {
    Neurons prev_layer_neurons = Neurons();
    Neurons this_layer_neurons = Neurons();

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

void Genome::addConnections(const Neurons &input_layer, const Neurons &output_layer) {
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
    input = getRandomNeuron(output->getLayerNumber() - 1);
    addConnection(input, output);
}

void Genome::addConnectionToNextLayer(const PNeuron &input) {
    PNeuron output;
    output = getRandomNeuron(input->getLayerNumber() + 1);
    addConnection(input, output);
}

void Genome::addConnection(const PNeuron &input, const PNeuron &output) {
    Connection connection(input, output);
    connections.insert(std::make_shared<Connection>(connection));

    BOOST_LOG_TRIVIAL(debug) << "[ADD CONNECTION] " << connection;
}

void Genome::deleteConnection() {
    PConnection connection = getRandomConnection();
    connections.erase(connection);

    BOOST_LOG_TRIVIAL(debug) << "[DELETE CONNECTION] " << *connection;
}

void Genome::randomizeWeight() {
    PConnection connection = getRandomConnection();
    connection->mutate(RANDOMIZE_WEIGHT);

    BOOST_LOG_TRIVIAL(debug) << "[RANDOMIZE WEIGHT] " << *connection;
}

PNeuron Genome::getRandomNeuron(int layer_number) {
    Neurons matches;
    PNeuron neuron;
    for (auto gene: getNeurons()) {
        neuron = std::static_pointer_cast<Neuron>(gene);
        if (neuron->getLayerNumber() == layer_number)
            matches.push_back(neuron);
    }

    int index = random.next(0, (int) matches.size() - 1);

    return matches[index];
}

PConnection Genome::getRandomConnection() {
    Genes valid_connections = connections.getGenes();
    int index = random.next(0, (int)(valid_connections.size() - 1));
    return std::static_pointer_cast<Connection>(valid_connections[index]);
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