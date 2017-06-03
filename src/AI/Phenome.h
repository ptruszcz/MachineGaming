/**
 * @class Phenome
 * @brief Represents phenome.
 * @details It is simulating the look of individual. In case of neural networks
 * it reads passed genome and using stored information - generates matrices
 * of neurons and connections.
 * @author Jakub Fajkowski
 */

#ifndef MACHINEGAMING_PHENOME_H
#define MACHINEGAMING_PHENOME_H


#include <armadillo>
#include <ostream>
#include "Genome.h"

class Phenome;
typedef std::unique_ptr<Phenome> PPhenome;
typedef std::pair<int, int> Coordinates;
typedef std::vector<std::vector<PNeuron>> NeuronLayers;
typedef arma::mat Matrix;

class Phenome {
private:
    std::vector<Matrix> neurons_;
    std::vector<Matrix> weights_;

    NeuronLayers createNeuronLayers(const Neurons &neurons);
    void generateNeuronMatrices(const NeuronLayers &neuron_layers);
    void generateWeightMatrices(const Connections &connection_list,
                                const NeuronLayers &neuron_layers);
    void fillWeightMatrices(const Connections &connection_list, const NeuronLayers &neuron_layers);
    Coordinates findNeuronCoordinates(const Neuron &neuron, const NeuronLayers &neuron_layers);

public:
    Phenome();
    Phenome(const Genome &genome);

    bool operator==(const Phenome &rhs) const;
    bool operator!=(const Phenome &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Phenome &phenome);

    std::vector<Matrix> &getNeurons();
    const std::vector<Matrix> &getWeights() const;
};


#endif //MACHINEGAMING_PHENOME_H
