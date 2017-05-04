#include "EvolutionaryAlgorithm.h"

Random EvolutionaryAlgorithm::random = Random();
bool EvolutionaryAlgorithm::compareNetworkFitnessPair(PNetworkFitnessPair &p1, PNetworkFitnessPair &p2) {
    return p1->fitness < p2->fitness;
}


EvolutionaryAlgorithm::EvolutionaryAlgorithm(int population_size, int input_size, int hidden_layers, int output_size,
                                             double crossover_probability, double mutation_probability)
        : initial_population_size(population_size), crossover_probability(crossover_probability),
          mutation_probability(mutation_probability) {

    for(int i = 0; i < population_size; ++i) {
        PNetworkFitnessPair pair_to_add;
        pair_to_add->network = std::make_shared<NeuralNetwork>(input_size, hidden_layers, output_size);
        pair_to_add->fitness = evaluateFitness(pair_to_add->network);
        population.push_back(pair_to_add);
    }
}

void EvolutionaryAlgorithm::processGeneration(int parents_selected_per_generation) {
    for(int i = 0; i < parents_selected_per_generation; ++i) {
        double random_value = random.next(0.0, 1.0);

        if(random_value <= crossover_probability) {
            PNetworkFitnessPair offspring = crossover();

            if(random_value <= mutation_probability)
                mutate(offspring);

            population.push_back(offspring);
        }

        removeWeakest();
    }
}

int EvolutionaryAlgorithm::evaluateFitness(PNeuralNetwork &network) {
    return 0; //TODO: connect with game
}

PNetworkFitnessPair EvolutionaryAlgorithm::select() {
    std::sort(population.begin(), population.end(), compareNetworkFitnessPair);

    int fitness_sum = 0;
    for(auto pair : population) {
        fitness_sum += pair->fitness;
    }

    double random_value = random.next(0.0, 1.0) * fitness_sum;
    for(auto pair : population) {
        random_value -= pair->fitness;
        if(random_value <= 0)
            return pair;
    }
    return population.front();
}

void EvolutionaryAlgorithm::removeWeakest() {
    std::sort(population.begin(), population.end(), compareNetworkFitnessPair);

    while (population.size() > initial_population_size) {
        population.pop_back();
    }
}

PNetworkFitnessPair EvolutionaryAlgorithm::crossover() {
    PNetworkFitnessPair first_parent = select();
    PNetworkFitnessPair second_parent;
    do {
        second_parent = select();
    } while(first_parent->network == second_parent->network);

    PNetworkFitnessPair offspring;
    offspring->network = NeuralNetwork::crossover(first_parent->network, second_parent->network);
    return offspring;
}

void EvolutionaryAlgorithm::mutate(PNetworkFitnessPair &networkFitnessPair) {
    MutationType random_mutation_type = static_cast<MutationType>(random.next(0, NUM_OF_MUTATION_TYPES - 1));
    networkFitnessPair->network->mutate(random_mutation_type);
}
