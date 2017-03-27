//
// Created by fajqa on 27.03.17.
//

#ifndef MACHINEGAMING_PHENOTYPE_H
#define MACHINEGAMING_PHENOTYPE_H


#include <armadillo>
#include "Genotype.h"

class Phenotype {
private:
    std::vector<arma::mat> neurons;
    std::vector<arma::mat> weights;

    std::vector<int> calculateNumberOfNeuronsPerLayer(const std::list<std::shared_ptr<Neuron>> &neuron_list);
    void generateNeuronMatrices(const std::vector<int> &layer_sizes);

    void generateWeightMatrices(const std::list<std::shared_ptr<Connection>> &connection_list, const std::vector<int> &layer_sizes);
public:
    Phenotype(Genotype genotype);

    const std::vector<arma::mat> &getNeurons() const;

    const std::vector<arma::mat> &getWeights() const;
};


#endif //MACHINEGAMING_PHENOTYPE_H
