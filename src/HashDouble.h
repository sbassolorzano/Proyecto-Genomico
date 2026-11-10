// Parte b2) — Alumno 1
// Tabla hash con DOUBLE HASHING.  Clave = k-mer, valor = conteo.
#pragma once
#include "modulos.h"

class TablaKmers {
public:
    explicit TablaKmers(int k);                // tamaño = siguientePrimo(4^k)

    void contarSecuencia(const string& seq);   // ventana deslizante de 1 en 1
    void insertar(const string& kmer);         // si existe suma 1, si no lo crea con 1
    int  buscar(const string& kmer) const;     // conteo, o 0 si no está

    vector<KmerCount> obtenerTodos() const;    // ESTO es lo que recibe el MaxHeap
    int k()          const;
    int capacidad()  const;
    int distintos()  const;                    // k-mers distintos guardados

private:
    int kLen;                                  // el valor de k
    vector<string> claves;                     // los k-mers guardados
    vector<int>    conteos;                    // cuántas veces aparece cada uno (0 = vacío)
    int n;                                     // k-mers distintos

    long codificar(const string& kmer) const;  // k-mer -> número en base 4
    int  h1(long x) const;                     // dónde empezar:  x mod m
    int  h2(long x) const;                     // tamaño del salto: 1 + x mod (m-1)
};