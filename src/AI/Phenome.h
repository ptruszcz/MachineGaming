#ifndef MACHINEGAMING_PHENOME_H
#define MACHINEGAMING_PHENOME_H


#include <armadillo>
#include "Genome.h"

typedef std::pair<int, int> Coordinates;
typedef std::vector<std::vector<PNeuron>> NeuronLayers;

class Phenome {
private:
    std::vector<arma::mat> neurons;
    std::vector<arma::mat> weights;

    NeuronLayers createNeuronLayers(const std::vector<PNeuron> &neurons);
    void generateNeuronMatrices(const NeuronLayers &neuron_layers);
    void generateWeightMatrices(const std::vector<Connection> &connection_list,
                                const NeuronLayers &neuron_layers);
    void fillWeightMatrices(const std::vector<Connection> &connection_list, const NeuronLayers &neuron_layers);
    Coordinates findNeuronCoordinates(const PNeuron &neuron, const NeuronLayers &neuron_layers);

public:
    Phenome(Genome genome);

    const std::vector<arma::mat> &getNeurons() const;
    const std::vector<arma::mat> &getWeights() const;

    bool operator==(const Phenome &rhs) const;
    bool operator!=(const Phenome &rhs) const;
};


#endif //MACHINEGAMING_PHENOME_H