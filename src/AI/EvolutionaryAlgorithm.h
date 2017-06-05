/**
 * @struct EvolutionaryAlgorithmParameters
 * @brief Parameters defining evolutionary algorithm.
 * @authors Piotr Truszczynski, Jakub Fajkowski
 */

/**
 * @class EvolutionaryAlgorithm
 * @brief Main library class controlling evolutionary algorithm process.
 * @details Stores collection of neural networks and using EvolutionaryAlgorithmParameters
 * decides whether it should crossover or mutate individuals. User can determine shape
 * of neural networks, crossover and mutation probabilities, weight variance, population size
 * and how many children should be bred per generation.
 * @authors Piotr Truszczynski, Jakub Fajkowski
 */

#ifndef MACHINEGAMING_EVOLUTIONARYALGORITHM_H
#define MACHINEGAMING_EVOLUTIONARYALGORITHM_H


#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <vector>

#include "NeuralNetwork.h"

struct EvolutionaryAlgorithmParameters {
    int population_size = 10;
    int children_bred_per_generation = 2;
    double crossover_probability = 0.5;
    double mutation_probability = 0.5;
    int input_size = 1;
    int hidden_layers = 1;
    int output_size = 1;
    double weight_variance = 10.0;
};

class EvolutionaryAlgorithm {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & current_network_;
        ar & current_generation_;
        ar & children_bred_;
        ar & population_;
        ar & population_size_;
        ar & children_bred_per_generation_;
        ar & crossover_probability_;
        ar & mutation_probability_;
        ar & hidden_layers_;
        ar & weight_variance_;
        Connection::weight_variance = weight_variance_;
    }

    static Random random;

    int current_network_ = 0;
    int current_generation_ = 1;
    int children_bred_ = 0;
    NeuralNetworks population_;
    int population_size_;
    int children_bred_per_generation_;
    double crossover_probability_;
    double mutation_probability_;
    int hidden_layers_;
    double weight_variance_;

    void generateInitialPopulation(int input_size, int hidden_layers, int output_size);
    void breed();
    void removeWeakestIndividuals();
    PNeuralNetwork select();
    PNeuralNetwork crossover();
    void mutate(NeuralNetwork& neural_network);

public:
    EvolutionaryAlgorithm();
    EvolutionaryAlgorithm(EvolutionaryAlgorithmParameters p);
    EvolutionaryAlgorithm(const EvolutionaryAlgorithm &eA);

    void save(std::string path);
    void load(std::string path);

    PNeuralNetwork getNext();
    int getCurrentNetwork() const;
    int getCurrentGeneration() const;
    const NeuralNetworks &getPopulation() const;
    int getPopulationSize() const;
    int getChildrenBredPerGeneration() const;
    double getCrossoverProbability() const;
    double getMutationProbability() const;
    int getHiddenLayers() const;
    double getWeightVariance() const;
};

#endif //MACHINEGAMING_EVOLUTIONARYALGORITHM_H
