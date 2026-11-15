#include "MaxHeap.h"
#include <utility>

void MaxHeap::insertar(const KmerCount& elemento) {
    datos.push_back(elemento);
    auto i = datos.size() - 1;
    while (i > 0) {
        auto padre = (i - 1) / 2;

        if (datos[padre].second >= datos[i].second) {
            break;
        }

        std::swap(datos[i], datos[padre]);
        i = padre;
}
}

KmerCount MaxHeap::cima() const {
    return datos[0];
}

    KmerCount MaxHeap::extraerMaximo() {
    KmerCount mayor = datos[0];
    datos[0] = datos.back();
    datos.pop_back();
    std::size_t i = 0;

    while (true) {
        auto izquierdo = 2 * i + 1;

        if (izquierdo >= datos.size()) {
            break;
        }

        auto derecho = izquierdo + 1;
        auto hijoMayor = izquierdo;

        if (derecho < datos.size() &&
            datos[derecho].second > datos[izquierdo].second) {
            hijoMayor = derecho;
        }

        if (datos[i].second >= datos[hijoMayor].second) {
            break;
        }

        std::swap(datos[i], datos[hijoMayor]);
        i = hijoMayor;


    }

    return mayor;
}

bool MaxHeap::vacio() const {
    return datos.empty();
}

std::vector<KmerCount> topN(const std::vector<KmerCount>& conteos, int n) {
    MaxHeap heap;
    std::vector<KmerCount> resultado;

    for (const KmerCount& par : conteos) {
        heap.insertar(par);
    }

    for (int sacados = 0; sacados < n && !heap.vacio(); ++sacados) {
        KmerCount mayor = heap.extraerMaximo();
        resultado.push_back(mayor);
    }

    return resultado;
}


