#include "NeuralNetwork.h"

const std::string greet( ) {
    return std::string("Hello world");
}

NeuralNetwork::NeuralNetwork(int input_size, int hidden_layers, int output_size)
        : genome_(input_size, hidden_layers, output_size),
          phenome_(genome_) {}

NeuralNetwork::NeuralNetwork(const NeuralNetwork &neural_network) :
        genome_(neural_network.genome_),
        phenome_(genome_) {
}

NeuralNetwork::NeuralNetwork(const Genome &genome) :
        genome_(genome),
        phenome_(genome_) {}

void NeuralNetwork::randomizeConnections () {
    for (PConnection connection: genome_.getConnections()) {
        connection->mutate(RANDOMIZE_WEIGHT);
    }

    phenome_ = Phenome(genome_);
}

Matrix NeuralNetwork::activationFunction(Matrix z) {
    return 1/(1 + arma::exp(-z));
}

PNeuralNetwork NeuralNetwork::crossover(PNeuralNetwork &parent_a, PNeuralNetwork &parent_b) {
    PGenome genome = Genome::crossover(parent_a->genome_, parent_b->genome_);
    return std::make_shared<NeuralNetwork>(*genome);
}

void NeuralNetwork::mutate(const MutationType &mutation_type) {
    genome_.mutate(mutation_type);
    phenome_ = Phenome(genome_);
}

Matrix NeuralNetwork::feedForward(Matrix input) {
    if (!compatible(input)) return Matrix();

    phenome_.getNeurons()[0] = input;
    for (int i = 0; i < phenome_.getWeights().size(); ++i) {
        phenome_.getNeurons()[i + 1] = activationFunction(phenome_.getNeurons()[i]
                                                         * phenome_.getWeights()[i]);
    }
    return getOutput();
}

bool NeuralNetwork::compatible(const Matrix &input) {
    return size(phenome_.getNeurons()[0]) == size(input);
}

Matrix &NeuralNetwork::getOutput() {
    return phenome_.getNeurons().back();
}

bool NeuralNetwork::operator==(const NeuralNetwork &rhs) const {
    return genome_ == rhs.genome_ &&
           phenome_ == rhs.phenome_;
}

bool NeuralNetwork::operator!=(const NeuralNetwork &rhs) const {
    return !(rhs == *this);
}
