//
// Created by fajqa on 25.03.17.
//

#include <armadillo>
#include "Genotype.h"

Genotype::Genotype() {

}

Genotype Genotype::cross(const Genotype &parentA, const Genotype &parentB) {
    return Genotype();
}

void Genotype::mutate(MutationType mutation_type) {
    switch (mutation_type) {
        case ADD_NEURON:
            addNeuron();
            break;

        case ADD_CONNECTION:
            addConnection();
            break;

        case DISABLE_CONNECTION:
            disableConnection();
            break;

        case RANDOMIZE_WEIGHT:
            randomizeWeight();
            break;
    }
}

void Genotype::addNeuron() {

}

void Genotype::addConnection() {

}

void Genotype::disableConnection() {

}

void Genotype::randomizeWeight() {

}

const std::list<std::shared_ptr<Neuron>> &Genotype::getNeurons() const {
    return neurons;
}

const std::list<std::shared_ptr<Connection>> &Genotype::getConnections() const {
    return connections;
}
