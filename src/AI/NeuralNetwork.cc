#include "NeuralNetwork.h"

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

void NeuralNetwork::randomizeAllWeights() {
    for (PConnection connection: genome_.getConnections()) {
        connection->mutate(RANDOMIZE_WEIGHT);
    }

    phenome_ = Phenome(genome_);
}

Matrix NeuralNetwork::activationFunction(Matrix z) {
    return 1/(1 + arma::exp(-z));
}

PNeuralNetwork NeuralNetwork::crossover(NeuralNetwork &parent_a, NeuralNetwork &parent_b) {
    PGenome genome = Genome::crossover(parent_a.genome_, parent_b.genome_);
    return std::make_unique<NeuralNetwork>(*genome);
}

void NeuralNetwork::mutate(const MutationType &mutation_type) {
    genome_.mutate(mutation_type);
    phenome_ = Phenome(genome_);
}

void NeuralNetwork::feedForward(const Matrix &input) {
    if (!compatible(input))
        return;

    phenome_.getNeurons()[0] = input;
    for (int i = 0; i < phenome_.getWeights().size(); ++i) {
        phenome_.getNeurons()[i + 1] = activationFunction(phenome_.getNeurons()[i]
                                                         * phenome_.getWeights()[i]);
    }

    output_ = phenome_.getNeurons().back();
}

bool NeuralNetwork::compatible(const Matrix &input) {
    return size(phenome_.getNeurons()[0]) == size(input);
}

const Matrix &NeuralNetwork::getOutput() const {
    return output_;
}

double NeuralNetwork::getFitness() const {
    return fitness_;
}

void NeuralNetwork::setFitness(double fitness) {
    NeuralNetwork::fitness_ = fitness;
}

bool NeuralNetwork::operator==(const NeuralNetwork &rhs) const {
    return genome_ == rhs.genome_ &&
           phenome_ == rhs.phenome_;
}

bool NeuralNetwork::operator!=(const NeuralNetwork &rhs) const {
    return !(rhs == *this);
}
