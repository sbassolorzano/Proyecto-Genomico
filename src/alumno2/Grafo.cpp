#include "Grafo.h"
#include <cmath>
#include <iostream>
#include <iomanip>

Matriz construirGrafo(const std::string& secuencia, double beta) {
    Matriz matriz(16, std::vector<double>(16, 0.0));
    std::vector<int> bloques;

    for (std::size_t pos = 0; pos + 1 < secuencia.size(); pos += 2) {
        int indice = indice2mer(secuencia[pos], secuencia[pos + 1]);
        bloques.push_back(indice);
    }
    for (std::size_t i = 0; i < bloques.size(); ++i) {
    int fila = bloques[i];
    if (fila == -1) {
        continue;
    }

    for (std::size_t j = i + 1; j < bloques.size(); ++j) {
        int columna = bloques[j];
        if (columna == -1) {
            continue;
        }

        double peso = 1.0 / std::pow(j - i, beta);
        matriz[fila][columna] += peso;
    }
}

    return matriz;
}

void imprimirMatriz(const Matriz& matriz) {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << std::setw(6) << "";

    for (std::size_t j = 0; j < matriz.size(); ++j) {
        std::cout << std::setw(7) << DINUCLEOTIDOS[j];
    }
    std::cout << '\n';

    for (std::size_t i = 0; i < matriz.size(); ++i) {
        std::cout << std::setw(6) << DINUCLEOTIDOS[i];

        for (std::size_t j = 0; j < matriz[i].size(); ++j) {
            std::cout << std::setw(7) << matriz[i][j];
        }
        std::cout << '\n';
     }
}
