/*
File created by: Jakub Fajkowski
*/

#ifndef MACHINEGAMING_GENOTYPE_H
#define MACHINEGAMING_GENOTYPE_H

#include <boost/serialization/vector.hpp>
#include <ostream>
#include "Gene.h"
#include "Random.h"

template <typename T>
class Genotype;

template<class T>
using PGenotype = std::unique_ptr<Genotype<T>>;

template <typename T>
class Genotype {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & genes_;
    }

    static Random random;
    std::vector<std::shared_ptr<T>> genes_;

    static PGenotype<T> createChild(Genotype &parent_a, Genotype &parent_b);
    static size_t makeEqualSize(Genotype &parent_a, Genotype &parent_b);
    static std::shared_ptr<T> chooseGene(const std::shared_ptr<T> &gene_a, const std::shared_ptr<T> &gene_b);
    static std::shared_ptr<T> getRandomGene(const std::shared_ptr<T> &gene_a, const std::shared_ptr<T> &gene_b);
    
public:
    Genotype() {};
    Genotype(const Genotype &genotype);
    PGenotype<T> clone() const;

    static PGenotype<T> crossover(Genotype &parent_a, Genotype &parent_b);

    void insert(const std::shared_ptr<T> &gene);
    void erase(const std::shared_ptr<T> &gene);

    std::shared_ptr<T> & operator[](size_t index);
    const std::shared_ptr<T> & operator[](size_t index) const;
    bool operator==(const Genotype &rhs) const;
    bool operator!=(const Genotype &rhs) const;

    std::vector<std::shared_ptr<T>> getGenes() const;
};

template <typename T>
Random Genotype<T>::random = Random();

template <typename T>
Genotype<T>::Genotype(const Genotype &genotype) {
    for (auto gene: genotype.genes_) {
        if (gene) {
            this->insert(std::static_pointer_cast<T>(gene->clone()));
        }
    }
}

template <typename T>
PGenotype<T> Genotype<T>::clone() const {
    return std::make_unique<Genotype>(*this);
}

template <typename T>
PGenotype<T> Genotype<T>::crossover(Genotype &parent_a, Genotype &parent_b) {
    return createChild(parent_a, parent_b);
}

template <typename T>
PGenotype<T> Genotype<T>::createChild(Genotype &parent_a, Genotype &parent_b) {
    size_t common_size = makeEqualSize(parent_a, parent_b);

    PGenotype<T> child_genotype = std::make_unique<Genotype>();
    child_genotype->genes_.reserve(common_size);
    std::shared_ptr<T> gene_a, gene_b, child_gene;

    for (size_t i = 0; i < common_size; ++i) {
        gene_a = parent_a.genes_[i];
        gene_b = parent_b.genes_[i];

        child_gene = chooseGene(gene_a, gene_b);

        child_genotype->genes_.push_back(child_gene);
    }

    return child_genotype;
}

template <typename T>
size_t Genotype<T>::makeEqualSize(Genotype &parent_a, Genotype &parent_b) {
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

template <typename T>
std::shared_ptr<T> Genotype<T>::chooseGene(const std::shared_ptr<T> &gene_a, const std::shared_ptr<T> &gene_b) {
    std::shared_ptr<T> child_gene;

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

template <typename T>
std::shared_ptr<T> Genotype<T>::getRandomGene(const std::shared_ptr<T> &gene_a, const std::shared_ptr<T> &gene_b) {
    std::shared_ptr<T> child_gene;

    if (random.next(0,1) == 0) {
        child_gene = gene_a;
    }
    else {
        child_gene = gene_b;
    }

    return child_gene;
}

template <typename T>
void Genotype<T>::insert(const std::shared_ptr<T> &gene) {
    size_t id = gene->getId();
    genes_.resize(id);

    typename std::vector<std::shared_ptr<T>>::iterator it = genes_.begin();
    genes_.insert(it + id, gene);
}

template <typename T>
void Genotype<T>::erase(const std::shared_ptr<T> &gene) {
    size_t id = gene->getId();
    genes_.at(id) = nullptr;
}

template <typename T>
std::shared_ptr<T> &Genotype<T>::operator[](size_t index) {
    return genes_[index];
}

template <typename T>
const std::shared_ptr<T> &Genotype<T>::operator[](size_t index) const {
    return genes_[index];
}

template <typename T>
bool Genotype<T>::operator==(const Genotype &rhs) const {
    return genes_ == rhs.genes_;
}

template <typename T>
bool Genotype<T>::operator!=(const Genotype &rhs) const {
    return !(rhs == *this);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Genotype<T> &genotype) {
    os << "genes: ";
    for (auto gene: genotype.getGenes()) {
        os << gene << " ";
    }
    return os;
}

template <typename T>
std::vector<std::shared_ptr<T>> Genotype<T>::getGenes() const {
    std::vector<std::shared_ptr<T>> valid_genes;

    for (std::shared_ptr<T> gene: genes_) {
        if (gene) {
            valid_genes.push_back(gene);
        }
    }

    return valid_genes;
}


#endif //MACHINEGAMING_GENOTYPE_H
