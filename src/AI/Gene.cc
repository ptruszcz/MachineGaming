#include "Gene.h"

std::size_t Gene::getId() const {
    return id;
}

Gene::Gene(size_t how_many) {
    this->id = how_many - 1;
}
