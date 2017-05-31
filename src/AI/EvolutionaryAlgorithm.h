/*
File created by: Piotr Truszczyński
*/

#ifndef MACHINEGAMING_EVOLUTIONARYALGORITHM_H
#define MACHINEGAMING_EVOLUTIONARYALGORITHM_H


#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <vector>
#include <fstream>
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
        ar & population_;
        ar & population_size_;
        ar & children_bred_per_generation_;
        ar & crossover_probability_;
        ar & mutation_probability_;
        ar & weight_variance_;
        Connection::weight_variance = weight_variance_;
    }

    static Random random;
    static bool compareNeuralNetworks(const PNeuralNetwork &p1, const PNeuralNetwork &p2); //fitness_ comparison

    NeuralNetworks population_;
    int population_size_;
    int children_bred_per_generation_;
    double crossover_probability_;
    double mutation_probability_;
    double weight_variance_;

    void generateInitialPopulation(int input_size, int hidden_layers, int output_size);
    NeuralNetwork* select();
    PNeuralNetwork crossover();
    void mutate(NeuralNetwork& neural_network);

public:
    EvolutionaryAlgorithm();
    EvolutionaryAlgorithm(EvolutionaryAlgorithmParameters p);
    EvolutionaryAlgorithm(const EvolutionaryAlgorithm &eA);

    void breed();
    void removeWeakestIndividuals();

    void save(std::string filename);
    void load(std::string filename);

    const NeuralNetworks &getCurrentGeneration() const;
};

#endif //MACHINEGAMING_EVOLUTIONARYALGORITHM_H
