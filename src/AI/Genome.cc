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

void Genome::addLayer(int size) {
    int layer_number = layer_counter;

    for (int i = 0; i < size; ++i) {
        addNeuron(layer_number);
    }

    ++layer_counter;
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

Genome::Genome(const Genotype &neurons, const Genotype &connections) {
    this->neurons_ = Genotype(neurons);
    this->connections_ = Genotype(connections);
}

Genome::Genome(const Genome &genome) {
    layer_counter = genome.layer_counter;
    neurons_ = genome.neurons_;
    connections_ = *genome.connections_.clone();
}

PGenome Genome::crossover(Genome &parentA, Genome &parentB) {
    PGenotype neurons = Genotype::crossover(parentA.neurons_, parentB.neurons_);
    PGenotype connections = Genotype::crossover(parentA.connections_, parentB.connections_)->clone();

    return std::make_shared<Genome>(*neurons, *connections);
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
    int random_layer_number = random.next(1, layer_counter - 2);
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
    // TODO Deal when only one Neuron in Layer
    //int random_layer_number = random.next(1, layer_counter - 2);
    //PNeuron neuron_to_delete = getRandomNeuron(random_layer_number);
    //neurons_.erase(neuron_to_delete);
    //deleteNeuronConnections(*neuron_to_delete);
}

void Genome::deleteNeuronConnections(const Neuron &neuron) {
    Connections matches;
    PConnection connection;

    for (auto gene: getConnections()) {
        connection = std::static_pointer_cast<Connection>(gene);

        if (*connection->getInput() == neuron || *connection->getOutput() == neuron) {
            matches.push_back(connection);
        }
    }

    for (auto connection: matches) {
        connections_.erase(connection);
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
    int layer_number = random.next(1, layer_counter - 2);
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
    connections_.insert(std::make_shared<Connection>(connection));
}

void Genome::deleteConnection() {
    PConnection connection = getRandomConnection();
    connections_.erase(connection);
}

void Genome::randomizeWeight() {
    PConnection connection = getRandomConnection();
    connection->mutate(RANDOMIZE_WEIGHT);
}

PNeuron Genome::getRandomNeuron(int layer_number) {
    Neurons matches;
    PNeuron neuron;
    Neurons neurons = getNeurons();
    for (auto gene: getNeurons()) {
        neuron = std::static_pointer_cast<Neuron>(gene);
        if (neuron->getLayerNumber() == layer_number)
            matches.push_back(neuron);
    }

    int index = random.next(0, (int) matches.size() - 1);

    return matches[index];
}

PConnection Genome::getRandomConnection() {
    Genes valid_connections = connections_.getGenes();
    int index = random.next(0, (int)(valid_connections.size() - 1));
    return std::static_pointer_cast<Connection>(valid_connections[index]);
}

bool Genome::operator==(const Genome &rhs) const {
    return layer_counter == rhs.layer_counter &&
           neurons_ == rhs.neurons_ &&
           connections_ == rhs.connections_;
}

bool Genome::operator!=(const Genome &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Genome &genome) {
    os << "neurons: " << genome.neurons_ << " connections: " << genome.connections_;
    return os;
}

Neurons Genome::getNeurons() const {
    Genes genes = neurons_.getGenes();
    Neurons result;
    for (PGene gene: genes) {
        result.push_back(std::static_pointer_cast<Neuron>(gene));
    }

    return result;
}

Connections Genome::getConnections() const {
    Genes genes = connections_.getGenes();
    Connections result;
    for (PGene gene: genes) {
        result.push_back(std::static_pointer_cast<Connection>(gene));
    }

    return result;
}
