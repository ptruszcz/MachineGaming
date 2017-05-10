#include "Genotype.h"

Random Genotype::random = Random();

Genotype::Genotype(const Genotype &genotype) {
    for (auto gene: genotype.genes_) {
        if (gene) {
            this->insert(gene->clone());
        }
    }
}

PGenotype Genotype::clone() const {
    return std::make_unique<Genotype>(*this);
}

PGenotype Genotype::crossover(Genotype &parent_a, Genotype &parent_b) {
    return createChild(parent_a, parent_b);
}

PGenotype Genotype::createChild(Genotype &parent_a, Genotype &parent_b) {
    size_t common_size = makeEqualSize(parent_a, parent_b);

    PGenotype child_genotype = std::make_unique<Genotype>();
    child_genotype->genes_.reserve(common_size);
    PGene gene_a, gene_b, child_gene;

    for (size_t i = 0; i < common_size; ++i) {
        gene_a = parent_a.genes_[i];
        gene_b = parent_b.genes_[i];

        child_gene = chooseGene(gene_a, gene_b);

        child_genotype->genes_.push_back(child_gene);
    }

    return child_genotype;
}

size_t Genotype::makeEqualSize(Genotype &parent_a, Genotype &parent_b) {
    size_t a_size = parent_a.genes_.size();
    size_t b_size = parent_b.genes_.size();
    size_t common_size;

    if (a_size > b_size) {
        parent_b.genes_.resize(a_size);
        common_size = a_size;
    }
    else {
        parent_a.genes_.resize(b_size);
        common_size = b_size;
    }

    return common_size;
}

PGene Genotype::chooseGene(const PGene &gene_a, const PGene &gene_b) {
    PGene child_gene;

    if (gene_a && gene_b)
        child_gene = getRandomGene(gene_a, gene_b);
    else if (gene_a)
        child_gene = gene_a;
    else if (gene_b)
        child_gene = gene_b;
    else
        child_gene = nullptr;

    return child_gene;
}

PGene Genotype::getRandomGene(const PGene &gene_a, const PGene &gene_b) {
    PGene child_gene;

    if (random.next(0,1) == 0) {
        child_gene = gene_a;
    }
    else {
        child_gene = gene_b;
    }

    return child_gene;
}

void Genotype::insert(const PGene &gene) {
    size_t id = gene->getId();
    genes_.resize(id);

    Genes::iterator it = genes_.begin();
    genes_.insert(it + id, gene);
}

void Genotype::erase(const PGene &gene) {
    size_t id = gene->getId();
    genes_.at(id) = nullptr;
}

PGene &Genotype::operator[](size_t index) {
    return genes_[index];
}

const PGene &Genotype::operator[](size_t index) const {
    return genes_[index];
}

bool Genotype::operator==(const Genotype &rhs) const {
    return genes_ == rhs.genes_;
}

bool Genotype::operator!=(const Genotype &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Genotype &genotype) {
    os << "genes: ";
    for (auto gene: genotype.getGenes()) {
        os << gene << " ";
    }
    return os;
}

Genes Genotype::getGenes() const {
    Genes valid_genes;

    for (PGene gene: genes_) {
        if (gene) {
            valid_genes.push_back(gene);
        }
    }

    return valid_genes;
}
