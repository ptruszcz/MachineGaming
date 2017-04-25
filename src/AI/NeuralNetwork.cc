#include "NeuralNetwork.h"

const std::string greet( ) {
    return std::string("Hello world");
}

NeuralNetwork::NeuralNetwork(int input_size, int hidden_layers, int output_size)
        : genome(input_size, hidden_layers, output_size),
          phenome(genome) {}

NeuralNetwork::NeuralNetwork(const NeuralNetwork &neural_network) :
        genome(neural_network.genome),
        phenome(genome) {
    randomizeConnections(genome.getConnections());
}

NeuralNetwork::NeuralNetwork(const Genome &genome) :
        genome(genome),
        phenome(this->genome) {}

void NeuralNetwork::randomizeConnections (const Connections &connections) {
    for (PConnection connection: connections) {
        connection->randomizeWeight();
    }
}

Matrix NeuralNetwork::activationFunction(Matrix z) {
    return 1/(1 + arma::exp(-z));
}

PNeuralNetwork NeuralNetwork::crossover(PNeuralNetwork &parent_a, PNeuralNetwork &parent_b) {
    PGenome genome = Genome::crossover(parent_a->genome, parent_b->genome);
    return std::make_shared<NeuralNetwork>(*genome);
}

void NeuralNetwork::mutate(const MutationType &mutation_type) {
    genome.mutate(mutation_type);
}

Matrix NeuralNetwork::feedForward(Matrix input) {
    if (!compatible(input)) return Matrix();

    phenome.getNeurons()[0] = input;
    for (int i = 0; i < phenome.getWeights().size(); ++i) {
        phenome.getNeurons()[i + 1] = activationFunction(phenome.getNeurons()[i]
                                                         * phenome.getWeights()[i]);
    }
    return getOutput();
}

bool NeuralNetwork::compatible(const Matrix &input) {
    return size(phenome.getNeurons()[0]) == size(input);
}

Matrix &NeuralNetwork::getOutput() {
    return phenome.getNeurons().back();
}
