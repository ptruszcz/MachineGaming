#include "EvolutionaryAlgorithm.h"

Random EvolutionaryAlgorithm::random = Random();

EvolutionaryAlgorithm::EvolutionaryAlgorithm() {

}

EvolutionaryAlgorithm::EvolutionaryAlgorithm(EvolutionaryAlgorithmParameters p)
        : population_size_(p.population_size),
          crossover_probability_(p.crossover_probability),
          mutation_probability_(p.mutation_probability),
          children_bred_per_generation_(p.children_bred_per_generation),
          hidden_layers_(p.hidden_layers),
          weight_variance_(p.weight_variance) {
    Connection::weight_variance = p.weight_variance;
    generateInitialPopulation(p.input_size, p.hidden_layers, p.output_size);
}

EvolutionaryAlgorithm::EvolutionaryAlgorithm(const EvolutionaryAlgorithm &eA) :
        population_(eA.population_),
        population_size_(eA.population_size_),
        children_bred_per_generation_(eA.children_bred_per_generation_),
        crossover_probability_(eA.crossover_probability_),
        mutation_probability_(eA.mutation_probability_) {
}

void EvolutionaryAlgorithm::generateInitialPopulation(int input_size, int hidden_layers, int output_size) {
    PNeuralNetwork ancestor = std::make_unique<NeuralNetwork>(input_size, hidden_layers, output_size);
    PNeuralNetwork descendant;

    for(int i = 0; i < population_size_; ++i) {
        descendant = std::make_unique<NeuralNetwork>(*ancestor);
        descendant->randomizeAllWeights();
        population_.push_back(std::move(descendant));
    }
}

/**
 * A method that sorts the population depending on their fitness and then
 * it crossovers individuals with some probability. An offspring can be mutated.
 */
void EvolutionaryAlgorithm::breed() {
    std::sort(population_.begin(), population_.end(), NeuralNetwork::compare);

    for(int i = 0; i < children_bred_per_generation_; ++i) {
        double random_value = random.next();

        if(random_value <= crossover_probability_) {
            PNeuralNetwork offspring = crossover();

            if(random_value <= mutation_probability_)
                mutate(*offspring);

            population_.push_back(std::move(offspring));
            ++children_bred_;
        }
    }
}

/**
 * It selects two parents and create an offspring.
 * @return New neural network with mixed genome.
 */
PNeuralNetwork EvolutionaryAlgorithm::crossover() {
    PNeuralNetwork first_parent = select();
    PNeuralNetwork second_parent = select();

    return NeuralNetwork::crossover(*first_parent, *second_parent);
}

/**
 * It uses roulette wheel selection.
 * @return Individual with probability of selection proportional to fitness.
 */
PNeuralNetwork EvolutionaryAlgorithm::select() {
    int fitness_sum = 0;
    for(const auto &individual : population_) {
        fitness_sum += individual->getFitness();
    }

    double random_value = random.next() * fitness_sum;
    for(const auto &individual : population_) {
        random_value -= individual->getFitness();
        if(random_value <= 0)
            return individual;
    }
    return population_.front();
}

void EvolutionaryAlgorithm::mutate(NeuralNetwork& neural_network) {
    MutationType random_mutation_type = static_cast<MutationType>(random.next(0, NUM_OF_MUTATION_TYPES - 1));
    neural_network.mutate(random_mutation_type);
}

/**
 * It sorts population and deletes individuals with smallest fitness.
 */
void EvolutionaryAlgorithm::removeWeakestIndividuals() {
    std::sort(population_.begin(), population_.end(), NeuralNetwork::compare);

    while (population_.size() > population_size_) {
        population_.pop_back();
    }
}

void EvolutionaryAlgorithm::save(std::string path) {
    std::ofstream ofs(path);
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
    ofs.close();
}

void EvolutionaryAlgorithm::load(std::string path) {
    std::ifstream ifs(path);
    boost::archive::text_iarchive ia(ifs);
    ia >> *this;
    ifs.close();
}

const NeuralNetworks &EvolutionaryAlgorithm::getPopulation() const {
    return population_;
}

/**
 * The result of this method depends on current_network_ counter. If current network number
 * is equal to population size - there are some offsprings added to population vector. After that
 * algorithm will return children networks. If the last child is selected, counter resets
 * and the weakest networks are killed.
 * @return Current neural network chosen by algorithm.
 */
PNeuralNetwork EvolutionaryAlgorithm::getNext() {
    if (current_network_ == population_size_) {
        breed();
    }

    if (current_network_ == population_size_ + children_bred_) {
        removeWeakestIndividuals();
        current_network_ = 0;
        children_bred_ = 0;
        ++current_generation_;
    }

    return population_[current_network_++];
}

int EvolutionaryAlgorithm::getCurrentNetwork() const {
    return current_network_;
}

int EvolutionaryAlgorithm::getCurrentGeneration() const {
    return current_generation_;
}

int EvolutionaryAlgorithm::getPopulationSize() const {
    return population_size_;
}

int EvolutionaryAlgorithm::getChildrenBredPerGeneration() const {
    return children_bred_per_generation_;
}

double EvolutionaryAlgorithm::getCrossoverProbability() const {
    return crossover_probability_;
}

double EvolutionaryAlgorithm::getMutationProbability() const {
    return mutation_probability_;
}

int EvolutionaryAlgorithm::getHiddenLayers() const {
    return hidden_layers_;
}

double EvolutionaryAlgorithm::getWeightVariance() const {
    return weight_variance_;
}
