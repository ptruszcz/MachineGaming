/*
File created by: Jakub Fajkowski
*/

#ifndef MACHINEGAMING_PHENOME_H
#define MACHINEGAMING_PHENOME_H


#include <armadillo>
#include <ostream>
#include "Genome.h"

typedef std::pair<int, int> Coordinates;
typedef std::vector<std::vector<PNeuron>> NeuronLayers;
typedef arma::mat Matrix;

class Phenome {
private:
    std::vector<Matrix> neurons;
    std::vector<Matrix> weights;

    NeuronLayers createNeuronLayers(const Neurons &neurons);
    void generateNeuronMatrices(const NeuronLayers &neuron_layers);
    void generateWeightMatrices(const Connections &connection_list,
                                const NeuronLayers &neuron_layers);
    void fillWeightMatrices(const Connections &connection_list, const NeuronLayers &neuron_layers);
    Coordinates findNeuronCoordinates(const PNeuron &neuron, const NeuronLayers &neuron_layers);

public:
    Phenome(const Genome &genome);

    std::vector<Matrix> &getNeurons();
    const std::vector<Matrix> &getWeights() const;

    bool operator==(const Phenome &rhs) const;
    bool operator!=(const Phenome &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Phenome &phenome);
};


#endif //MACHINEGAMING_PHENOME_H
