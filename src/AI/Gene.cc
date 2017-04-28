#include "Gene.h"

Gene::Gene(const Gene &gene) {
    this->id = gene.id;
}

std::size_t Gene::getId() const {
    return id;
}

Gene::Gene(size_t how_many) {
    this->id = how_many - 1;
}

std::ostream &operator<<(std::ostream &os, const Gene &gene) {
    os << "id: " << gene.id;
    return os;
}
