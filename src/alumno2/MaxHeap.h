#pragma once
#include "../modulos.h"

class MaxHeap {
private:
    std::vector<KmerCount> datos;

public:
    void insertar(const KmerCount& elemento);
    KmerCount cima() const;
    KmerCount extraerMaximo();
    bool vacio() const;
};
std::vector<KmerCount> topN(const std::vector<KmerCount>& conteos, int n);
