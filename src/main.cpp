#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "HashDouble.h"
#include "HashLinear.h"
#include "Parser.h"
#include "alumno2/Grafo.h"
#include "alumno2/MaxHeap.h"

namespace {

template <typename T>
bool leerNumero(const char* mensaje, T& valor) {
    std::cout << mensaje;
    std::string linea;
    if (!std::getline(std::cin, linea)) {
        return false;
    }

    std::istringstream entrada(linea);
    if (entrada >> valor) {
        entrada >> std::ws;
        if (entrada.eof()) {
            return true;
        }
    }

    std::cout << "Ingresa un numero valido.\n";
    return false;
}

void imprimirConteos(const std::vector<KmerCount>& conteos) {
    if (conteos.empty()) {
        std::cout << "No hay k-mers validos para mostrar.\n";
        return;
    }

    std::cout << "Patron\tFrecuencia\n";
    for (const KmerCount& par : conteos) {
        std::cout << par.first << '\t' << par.second << '\n';
    }
}

const DNASequence* buscarSecuencia(const TablaSecuencias& tabla) {
    std::cout << "ID de la secuencia (opcion 1 para ver los IDs): ";
    std::string id;
    if (!std::getline(std::cin, id)) {
        return nullptr;
    }

    const DNASequence* secuencia = tabla.buscar(id);
    if (!secuencia) {
        std::cout << "No se encontro el ID: " << id << '\n';
    }
    return secuencia;
}

void consultarKmers(const DNASequence& secuencia, bool soloTop) {
    // La tabla reserva al menos 4^k casillas.
    constexpr int maxK = 10;
    int k;
    if (!leerNumero("Longitud k del patron (1 a 10): ", k)) {
        return;
    }
    if (k < 1 || k > maxK || static_cast<std::size_t>(k) > secuencia.sequence.size()) {
        std::cout << "k debe estar entre 1 y 10 y caber en la secuencia.\n";
        return;
    }

    int n = 0;
    if (soloTop) {
        if (!leerNumero("Cantidad n de patrones: ", n)) {
            return;
        }
        if (n < 1) {
            std::cout << "n debe ser mayor que cero.\n";
            return;
        }
    }

    TablaKmers tabla(k);
    tabla.contarSecuencia(secuencia.sequence);

    if (soloTop) {
        imprimirConteos(topN(tabla.obtenerTodos(), n));
        return;
    }

    std::cout << "Patrones distintos: " << tabla.distintos() << '\n'
              << "Ventanas contadas: " << tabla.totalKmers() << '\n'
              << "Ventanas descartadas: " << tabla.descartados() << '\n'
              << "Capacidad: " << tabla.capacidad() << '\n'
              << "Colisiones: " << tabla.colisiones() << '\n'
              << "Patron de " << k << " letras (Enter para ver todos): ";

    std::string patron;
    if (!std::getline(std::cin, patron)) {
        return;
    }
    if (patron.empty()) {
        imprimirConteos(tabla.obtenerTodos());
        return;
    }
    if (patron.size() != static_cast<std::size_t>(k) ||
        patron.find_first_not_of("ACGT") != std::string::npos) {
        std::cout << "Escribe un patron de longitud k con letras A, C, G o T en mayusculas.\n";
        return;
    }

    std::cout << patron << " aparece " << tabla.buscar(patron) << " veces.\n";
}

}  // namespace

int main(int argc, char* argv[]) {
    const std::string ruta = argc > 1 ? argv[1] : "data/HIV2_ALL_2021_env_DNA.2000.fasta";
    const std::vector<DNASequence> secuencias = parseFasta(ruta);
    if (secuencias.empty()) {
        std::cerr << "No se cargaron secuencias de " << ruta << '\n';
        return 1;
    }

    TablaSecuencias tabla;
    for (const DNASequence& secuencia : secuencias) {
        tabla.insertar(secuencia);
    }
    std::cout << "Registros leidos: " << secuencias.size() << '\n';

    while (std::cin) {
        std::cout << "\n1. Listar registros del FASTA\n"
                  << "2. Buscar secuencia por ID\n"
                  << "3. Contar y consultar k-mers\n"
                  << "4. Mostrar los n k-mers mas frecuentes\n"
                  << "5. Imprimir el grafo de 2-mers\n"
                  << "0. Salir\n"
                  << "Opcion: ";

        std::string opcion;
        if (!std::getline(std::cin, opcion) || opcion == "0") {
            break;
        }

        if (opcion == "1") {
            std::cout << "ID\tLongitud\n";
            for (const DNASequence& secuencia : secuencias) {
                std::cout << secuencia.id << '\t' << secuencia.sequence.size() << '\n';
            }
            continue;
        }

        if (opcion != "2" && opcion != "3" && opcion != "4" && opcion != "5") {
            std::cout << "Opcion invalida.\n";
            continue;
        }

        const DNASequence* secuencia = buscarSecuencia(tabla);
        if (!secuencia) {
            continue;
        }

        if (opcion == "2") {
            std::cout << "ID: " << secuencia->id << '\n'
                      << "Longitud: " << secuencia->sequence.size() << '\n'
                      << "Secuencia: " << secuencia->sequence << '\n'
                      << "IDs almacenados: " << tabla.cantidad() << '\n'
                      << "Capacidad: " << tabla.capacidad() << '\n'
                      << "Colisiones: " << tabla.colisiones() << '\n'
                      << "Redimensiones: " << tabla.rehashes() << '\n';
        } else if (opcion == "5") {
            double beta;
            if (leerNumero("Beta (por ejemplo 1): ", beta)) {
                if (!std::isfinite(beta) || beta < 0.0) {
                    std::cout << "Beta debe ser un numero finito mayor o igual a cero.\n";
                } else {
                    imprimirMatriz(construirGrafo(secuencia->sequence, beta));
                }
            }
        } else {
            consultarKmers(*secuencia, opcion == "4");
        }
    }
}
