
//Parte principal de los modulos del proyecto -- No borrar ni modificar este archivo

#pragma once
#include <string>
#include <vector>
#include <utility>
using namespace std;

struct DNASequence {
    string id;       // identificador de secuencia
    string sequence; // secuencia de ADN
};

//Formato de intercambio ( b y c)

using KmerCount = pair<string, int>; // par de kmer y conteo

// Formato para la parte d
using Matriz= vector<vector<double>>; //Matriz 16 x 16

// ============================================================
//  DECISIONES ACORDADAS (justificarlas en el informe)
// ============================================================
// 1) Caracteres que no son A/C/G/T (R, Y, W, K, M, N...):
//    se descarta todo k-mer o par que los contenga.
//
// 2) Tabla 1 (linear probing): tamaño inicial 10.
//    Con direccionamiento abierto el factor de carga nunca supera 1,
//    así que se redimensiona cuando alfa >= UMBRAL_REHASH.
//    Nuevo tamaño = siguientePrimo(2 * elementos)  => alfa queda ~0.5
const int    TAM_INICIAL_TABLA1 = 10;
const double UMBRAL_REHASH      = 0.75;
//
// 3) Tabla 2 (double hashing): tamaño = siguientePrimo(4^k).
//    h1(x) = x mod m          h2(x) = 1 + (x mod (m - 1))   (nunca 0)
//    x = k-mer codificado en base 4 (A=0, C=1, G=2, T=3).
//
// 4) Grafo: pares SIN solapamiento, arista entre todo par i<j con
//    peso 1/(j-i)^beta; aristas repetidas se SUMAN.
//    Si la longitud es impar, se ignora la última base.


// Utilidades compartidas entre los modulos

//Convierte un caracter a su valor en base 4
inline int valorBase(char c) {
    switch (c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: return -1; // Caracter no válido
    }
}
//Responde si es caracter valido
inline bool esBaseValida(char c) {
    return valorBase(c) != -1;
}

//Array de los 16 dinucleotidos posibles
// En una matriz 16x16
const string DINUCLEOTIDOS[16] = {
    "AA","AC","AG","AT","CA","CC","CG","CT",
    "GA","GC","GG","GT","TA","TC","TG","TT"
};

//Convierte un par de caracteres a su indice en la matriz 16x16
inline int indice2mer(char a , char b){
    int x = valorBase(a) , y = valorBase(b);
    if(x < 0 || y < 0) return -1; //Caracter no valido
    return x*4 + y;
}

//Encuentran los primos mas cercanos (ejem: 10 -> 11, 16 ->17)
inline bool esPrimo(long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (long i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;          // <- esta línea faltaba
}

//Menor primo
inline long siguientePrimo(long n){
    while(!esPrimo(n)) n++;
    return n;
}




