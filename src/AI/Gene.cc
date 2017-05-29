#include "Gene.h"

Gene::Gene() {

}

Gene::Gene(size_t how_many) {
    this->id = how_many - 1;
}

Gene::Gene(const Gene &gene) {
    this->id = gene.id;
}

std::ostream &operator<<(std::ostream &os, const Gene &gene) {
    os << "id: " << gene.id;
    return os;
}

std::size_t Gene::getId() const {
    return id;
}
