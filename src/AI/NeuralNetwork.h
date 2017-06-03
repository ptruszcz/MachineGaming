/*
File created by: Jakub Fajkowski
*/

#ifndef PROJECT_NEURALNETWORK_H
#define PROJECT_NEURALNETWORK_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <vector>
#include <armadillo>
#include <cstdlib>
#include "Genome.h"
#include "Phenome.h"

class NeuralNetwork;
typedef std::shared_ptr<NeuralNetwork> PNeuralNetwork;
typedef std::vector<PNeuralNetwork> NeuralNetworks;

class NeuralNetwork {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & genome_;
        phenome_ = std::make_unique<Phenome>(*genome_);
        ar & fitness_;
    }

    PGenome genome_;
    PPhenome phenome_;

    double fitness_ = 0;
    Matrix output_;

    bool compatible(const Matrix &input);

    Matrix activationFunction(Matrix z);

public:
    NeuralNetwork();
    NeuralNetwork(int input_size, int hidden_layers, int output_size);
    NeuralNetwork(const NeuralNetwork &neural_network);
    NeuralNetwork(const Genome &genome);

    /// Fitness comparison
    static bool compare(const PNeuralNetwork &p1, const PNeuralNetwork &p2);

    static PNeuralNetwork crossover(NeuralNetwork &parent_a, NeuralNetwork &parent_b);
    void mutate(const MutationType &mutation_type);

    void randomizeAllWeights();
    void feedForward(const Matrix &input);

    const Matrix &getOutput() const;
    double getFitness() const;
    void setFitness(double fitness);

    bool operator==(const NeuralNetwork &rhs) const;
    bool operator!=(const NeuralNetwork &rhs) const;
};
#endif //PROJECT_NEURALNETWORK_H
