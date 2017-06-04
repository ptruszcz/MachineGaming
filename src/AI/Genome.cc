#include "Genome.h"

Random Genome::random = Random();

Genome::Genome() {

}

Genome::Genome(int input_size, int hidden_layers, int output_size) {
    layers_ = 0;
    addLayer(input_size);

    for (int i = 1; i <= hidden_layers; ++i) {
        addLayer(1);
        connectLayer(i);
    }

    addLayer(output_size);
    connectLayer(layers_ - 1);
}

void Genome::addLayer(int size) {
    for (int i = 0; i < size; ++i) {
        addNeuron(layers_);
    }

    ++layers_;
}

void Genome::connectLayer(int layer_number) {
    Neurons prev_layer_neurons = Neurons();
    Neurons this_layer_neurons = Neurons();

    for (auto neuron: getNeurons()) {
        if (neuron->getLayerNumber() == layer_number - 1) {
            prev_layer_neurons.push_back(neuron);
        } else if (neuron->getLayerNumber() == layer_number) {
            this_layer_neurons.push_back(neuron);
        }
    }

    addConnections(prev_layer_neurons, this_layer_neurons);
}

Genome::Genome(int layers, const Genotype<Neuron> &neurons, const Genotype<Connection> &connections) {
    layers_ = layers;
    neurons_ = Genotype<Neuron>(neurons);
    connections_ = Genotype<Connection>(connections);
}

Genome::Genome(const Genome &genome) {
    layers_ = genome.layers_;
    neurons_ = genome.neurons_;
    connections_ = *genome.connections_.clone();
}

PGenome Genome::crossover(Genome &parentA, Genome &parentB) {
    PGenotype<Neuron> neurons = Genotype<Neuron>::crossover(parentA.neurons_, parentB.neurons_);
    PGenotype<Connection> connections = Genotype<Connection>::crossover(parentA.connections_, parentB.connections_)->clone();

    return std::make_unique<Genome>(parentA.layers_, *neurons, *connections);
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

void Genome::addNeuron() {
    int random_layer_number = random.next(1, layers_ - 2);
    PNeuron neuron_ptr = addNeuron(random_layer_number);
    addConnectionToPrevLayer(neuron_ptr);
    addConnectionToNextLayer(neuron_ptr);
}

PNeuron Genome::addNeuron(int layer_number) {
    Neuron neuron_to_add = Neuron(layer_number);
    PNeuron neuron_ptr = std::make_shared<Neuron>(neuron_to_add);
    neurons_.insert(neuron_ptr);

    return neuron_ptr;
}

void Genome::deleteNeuron() {
    int random_layer_number = random.next(1, layers_ - 2);

    if (layerSize(random_layer_number) > 1) {
        PNeuron neuron_to_delete = getRandomNeuron(random_layer_number);
        neurons_.erase(neuron_to_delete);
        deleteNeuronConnections(*neuron_to_delete);
    }
}

void Genome::deleteNeuronConnections(const Neuron &neuron) {
    Connections matches;

    for (auto connection: getConnections()) {
        if (*connection->getInput() == neuron || *connection->getOutput() == neuron) {
            matches.push_back(connection);
        }
    }

    for (auto connection_to_erase: matches) {
        connections_.erase(connection_to_erase);
    }
}

void Genome::addConnections(const Neurons &input_layer, const Neurons &output_layer) {
    for (auto input_neuron: input_layer) {
        for (auto output_neuron: output_layer) {
            addConnection(input_neuron, output_neuron);
        }
    }
}

void Genome::addConnection() {
    int layer_number = random.next(1, layers_ - 2);
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
    PConnection connection = std::make_shared<Connection>(input, output);
    if (!connections_.contains(connection))
        connections_.insert(connection);
}

void Genome::deleteConnection() {
    PConnection connection = getRandomConnection();
    connections_.erase(connection);
}

void Genome::randomizeWeight() {
    PConnection connection = getRandomConnection();
    connection->mutate(RANDOMIZE_WEIGHT);
}

int Genome::layerSize(int layer_number) {
    Neurons matches;

    for (auto neuron: getNeurons()) {
        if (neuron->getLayerNumber() == layer_number)
            matches.push_back(neuron);
    }

    return (int) matches.size();
}

PNeuron Genome::getRandomNeuron(int layer_number) {
    Neurons matches;

    for (auto neuron: getNeurons()) {
        if (neuron->getLayerNumber() == layer_number)
            matches.push_back(neuron);
    }

    int index = random.next(0, (int) matches.size() - 1);

    return matches[index];
}

PConnection Genome::getRandomConnection() {
    Connections valid_connections = connections_.getGenes();
    int index = random.next(0, (int)(valid_connections.size() - 1));
    return valid_connections[index];
}

bool Genome::operator==(const Genome &rhs) const {
    Connections connections = getConnections();
    Connections rhs_connections = rhs.getConnections();

    bool connections_equal = std::equal(connections.begin(), connections.end(),
                    rhs_connections.begin(), rhs_connections.end(),
                    [](const PConnection lhs, const PConnection rhs){ return *lhs == *rhs; });

    return layers_ == rhs.layers_ &&
           neurons_ == rhs.neurons_ &&
           connections_equal;
}

bool Genome::operator!=(const Genome &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Genome &genome) {
    os << "neurons: " << genome.neurons_ << " connections: " << genome.connections_;
    return os;
}

Neurons Genome::getNeurons() const {
    return neurons_.getGenes();
}

Connections Genome::getConnections() const {
    return connections_.getGenes();
}
