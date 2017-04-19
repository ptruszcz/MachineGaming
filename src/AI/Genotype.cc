#include "Genotype.h"

Random Genotype::random = Random();

Genotype Genotype::crossover(Genotype &parent_a, Genotype &parent_b) {
    size_t a_size = parent_a.genes.size();
    size_t b_size = parent_b.genes.size();
    size_t common_size;

    if (a_size > b_size) {
        parent_b.genes.resize(a_size);
        common_size = a_size;
    }
    else {
        parent_a.genes.resize(b_size);
        common_size = b_size;
    }

    Genotype child_genotype = Genotype();
    child_genotype.genes.reserve(common_size);
    PGene gene_a, gene_b, child_gene;

    for (size_t i = 0; i < common_size; ++i) {
        gene_a = parent_a.genes[i];
        gene_b = parent_b.genes[i];


        if (random.next(0,1) == 0) {
            child_gene = gene_a;
        }
        else {
            child_gene = gene_b;
        }

        child_genotype.genes.push_back(child_gene);
    }

    return child_genotype;
}

void Genotype::insert(const PGene &gene) {
    size_t id = gene->getId();
    genes.resize(id);

    Genes::iterator it = genes.begin();
    genes.insert(it + id, gene);
}

void Genotype::erase(const PGene &gene) {
    size_t id = gene->getId();

    Genes::iterator it = genes.begin();
    genes.erase(it + id);
}

std::vector<PGene> Genotype::getGenes() {
    Genes valid_genes;

    for (PGene gene: genes) {
        if (gene) {
            valid_genes.push_back(gene);
        }
    }

    return valid_genes;
}

PGene &Genotype::operator[](size_t index) {
    return genes[index];
}

const PGene &Genotype::operator[](size_t index) const {
    return genes[index];
}

bool Genotype::operator==(const Genotype &rhs) const {
    return genes == rhs.genes;
}

bool Genotype::operator!=(const Genotype &rhs) const {
    return !(rhs == *this);
}
