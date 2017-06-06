#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork() {

}

/**
 * It creates new NeuralNetwork with single Neuron in each hidden layer.
 * @param input_size First layer size.
 * @param hidden_layers Number of hidden layers.
 * @param output_size Last layer size.
 */
NeuralNetwork::NeuralNetwork(int input_size, int hidden_layers, int output_size) {
    genome_ = std::make_unique<Genome>(input_size, hidden_layers, output_size);
    phenome_ = std::make_unique<Phenome>(*genome_);
}

/**
 * Copy constructor used to initialize NeuralNetwork with same structure, and Gene id's.
 * @param neural_network NeuralNetwork to be copied.
 */
NeuralNetwork::NeuralNetwork(const NeuralNetwork &neural_network) {
    genome_ = std::make_unique<Genome>(*neural_network.genome_);
    phenome_ = std::make_unique<Phenome>(*neural_network.genome_);
}

/**
 * Creates new NeuralNetwork using provided Genome.
 * @param genome Parents crossed Genome.
 */
NeuralNetwork::NeuralNetwork(const Genome &genome) {
    genome_ = std::make_unique<Genome>(genome);
    phenome_ = std::make_unique<Phenome>(genome);
}

/**
 * Randomizes all Connections weights.
 */
void NeuralNetwork::randomizeAllWeights() {
    for (PConnection connection: genome_->getConnections()) {
        connection->mutate(RANDOMIZE_WEIGHT);
    }

    phenome_ = std::make_unique<Phenome>(*genome_);
}

Matrix NeuralNetwork::activationFunction(Matrix z) {
    return 1/(1 + arma::exp(-z));
}

/**
 * Creates and offspring.
 * @param parent_a
 * @param parent_b
 * @return NeuralNetwork with features common with parents.
 */
PNeuralNetwork NeuralNetwork::crossover(NeuralNetwork &parent_a, NeuralNetwork &parent_b) {
    PGenome genome = Genome::crossover(*parent_a.genome_, *parent_b.genome_);
    return std::make_unique<NeuralNetwork>(*genome);
}

/**
 * Applies mutation to NeuralNetwork.
 * @param mutation_type Type of mutation.
 */
void NeuralNetwork::mutate(const MutationType &mutation_type) {
    genome_->mutate(mutation_type);
    phenome_ = std::make_unique<Phenome>(*genome_);
}

/**
 * Neural network using provided input calculate some output values.
 * @param input vector
 */
void NeuralNetwork::feedForward(const Matrix &input) {
    if (!compatible(input))
        return;

    phenome_->getNeurons()[0] = input;
    for (int i = 0; i < phenome_->getWeights().size(); ++i) {
        phenome_->getNeurons()[i + 1] = activationFunction(phenome_->getNeurons()[i]
                                                         * phenome_->getWeights()[i]);
    }

    output_ = phenome_->getNeurons().back();
}

bool NeuralNetwork::compatible(const Matrix &input) {
    return size(phenome_->getNeurons()[0]) == size(input);
}

/**
 * Feed forward method should be called before.
 * @return Calculated output value.
 */
const Matrix &NeuralNetwork::getOutput() const {
    return output_;
}

double NeuralNetwork::getFitness() const {
    return fitness_;
}

void NeuralNetwork::setFitness(double fitness) {
    fitness_ = fitness;
}

bool NeuralNetwork::operator==(const NeuralNetwork &rhs) const {
    return genome_ == rhs.genome_ &&
           phenome_ == rhs.phenome_;
}

bool NeuralNetwork::operator!=(const NeuralNetwork &rhs) const {
    return !(rhs == *this);
}

/**
 * Comparator using neural network fitness.
 * @param neural network one
 * @param neural network two
 * @return True if p1's fitness is greater than p2's fitness. Else false.
 */
bool NeuralNetwork::compare(const PNeuralNetwork &p1, const PNeuralNetwork &p2) {
    return p1->getFitness() > p2->getFitness();
}
