#include "EvolutionaryAlgorithm.h"

Random EvolutionaryAlgorithm::random = Random();
bool EvolutionaryAlgorithm::compareNeuralNetworks(const PNeuralNetwork &p1, const PNeuralNetwork &p2) {
    return p1->getFitness() > p2->getFitness();
}

EvolutionaryAlgorithm::EvolutionaryAlgorithm() {

}

EvolutionaryAlgorithm::EvolutionaryAlgorithm(EvolutionaryAlgorithmParameters p)
        : population_size_(p.population_size),
          crossover_probability_(p.crossover_probability),
          mutation_probability_(p.mutation_probability),
          children_bred_per_generation_(p.children_bred_per_generation),
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

void EvolutionaryAlgorithm::breed() {
    std::sort(population_.begin(), population_.end(), compareNeuralNetworks);

    for(int i = 0; i < children_bred_per_generation_; ++i) {
        double random_value = random.next();

        if(random_value <= crossover_probability_) {
            PNeuralNetwork offspring = crossover();

            if(random_value <= mutation_probability_)
                mutate(*offspring);

            population_.push_back(std::move(offspring));
        }
    }
}

PNeuralNetwork EvolutionaryAlgorithm::crossover() {
    NeuralNetwork* first_parent = select();
    NeuralNetwork* second_parent = select();

    return NeuralNetwork::crossover(*first_parent, *second_parent);
}

NeuralNetwork* EvolutionaryAlgorithm::select() {
    int fitness_sum = 0;
    for(const auto &individual : population_) {
        fitness_sum += individual->getFitness();
    }

    double random_value = random.next() * fitness_sum;
    for(const auto &individual : population_) {
        random_value -= individual->getFitness();
        if(random_value <= 0)
            return individual.get();
    }
    return population_.front().get();
}

void EvolutionaryAlgorithm::mutate(NeuralNetwork& neural_network) {
    MutationType random_mutation_type = static_cast<MutationType>(random.next(0, NUM_OF_MUTATION_TYPES - 1));
    neural_network.mutate(random_mutation_type);
}

void EvolutionaryAlgorithm::removeWeakestIndividuals() {
    std::sort(population_.begin(), population_.end(), compareNeuralNetworks);

    while (population_.size() > population_size_) {
        population_.pop_back();
    }
}

const NeuralNetworks &EvolutionaryAlgorithm::getCurrentGeneration() const {
    return population_;
}

void EvolutionaryAlgorithm::save(std::string filename) {
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
    ofs.close();
}

void EvolutionaryAlgorithm::load(std::string filename) {
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia(ifs);
    ia >> *this;
    ifs.close();
}
