#include "Neuron.h"

Neuron::Neuron() {

}

Neuron::Neuron(int layer_number) : Counter(), Gene(getCount()) {
    this->layer_number_ = layer_number;
}

Neuron::Neuron(const Neuron &neuron) : Counter(neuron), Gene(neuron) {
    this->layer_number_ = neuron.layer_number_;
}

PGene Neuron::clone() const {
    return std::make_shared<Neuron>(*this);
}

void Neuron::mutate(MutationType mutation_type) {}

bool Neuron::operator==(const Neuron &rhs) const {
    return id == rhs.id &&
            layer_number_ == rhs.layer_number_;
}

bool Neuron::operator!=(const Neuron &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Neuron &neuron) {
    os << "[No. " << neuron.id << " Layer " << neuron.layer_number_ << "]";
    return os;
}

int Neuron::getLayerNumber() const {
    return layer_number_;
}
