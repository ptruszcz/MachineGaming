//
// Created by fajqa on 25.03.17.
//

#include <armadillo>
#include "Genotype.h"

Genotype Genotype::cross(const Genotype &parentA, const Genotype &parentB) {
    return Genotype();
}

const std::list<std::shared_ptr<Neuron>> &Genotype::getNeurons() const {
    return neurons;
}

const std::list<std::shared_ptr<Connection>> &Genotype::getConnections() const {
    return connections;
}
