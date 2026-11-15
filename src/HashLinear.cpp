#include "HashLinear.h"
#include <iostream>

// Constructor con 10 casilleros vacios
TablaSecuencias::TablaSecuencias()
    : tabla(TAM_INICIAL_TABLA1), ocupada(TAM_INICIAL_TABLA1, false),
      n(0), totalColisiones(0), totalRehashes(0) {}


// La Funcion Hash cnvierte el ID en una posicion

int TablaSecuencias::hashId(const string& id ) const {
    unsigned long long h = 0;
    int m = (int)tabla.size();
    for (char c : id)
        h = (h * 31 + (unsigned char)c) % m;
    return (int)h;
}

// Coloca una ficha usando linear probing
void TablaSecuencias::colocar(const DNASequence& s) {
    int m = (int)tabla.size();
    int pos = hashId(s.id);

    while (ocupada[pos]) {
        if (tabla[pos].id == s.id) {      // el ID ya existe: se actualiza
            tabla[pos] = s;
            return;
        }
        totalColisiones++;                // casillero ocupado = choque
        pos = (pos + 1) % m;              // probar el siguiente
    }
    tabla[pos] = s;
    ocupada[pos] = true;
    n++;
}

//La funcion insertar coloca el numero y si es mayor a 0.75 se agranda la tabla

void TablaSecuencias::insertar(const DNASequence& s){
    colocar(s);
    if (factorCarga() >= UMBRAL_REHASH)
        rehash();
}

// Rehash : Nueva tabla de tamaño primo >= 2n

void TablaSecuencias::rehash() {
    int tamAnterior = (int)tabla.size();
    double alfaAnterior = factorCarga();

    vector<DNASequence> viejaTabla = tabla;
    vector<bool> viejaOcupada = ocupada;

    int nuevoTam = (int)siguientePrimo(2L * n);
    tabla.assign(nuevoTam, DNASequence());
    ocupada.assign(nuevoTam, false);
    n = 0;

    for (int i = 0; i < tamAnterior; i++)
        if (viejaOcupada[i])
            colocar(viejaTabla[i]);

    totalRehashes++;
    cout << "[rehash] " << tamAnterior << " -> " << nuevoTam
         << "alfa: " << alfaAnterior << " -> " << factorCarga() << "\n";
}


// Metodo Buscar
const DNASequence* TablaSecuencias::buscar(const string& id) const {
    int m = (int)tabla.size();
    int pos = hashId(id);

    for (int intentos = 0; intentos < m; intentos++) {
        if (!ocupada[pos]) return nullptr;          // casillero vacío: no existe
        if (tabla[pos].id == id) return &tabla[pos];
        pos = (pos + 1) % m;
    }
    return nullptr;
}

//Medidores

int    TablaSecuencias::cantidad()    const { return n; }
int    TablaSecuencias::capacidad()   const { return (int)tabla.size(); }
double TablaSecuencias::factorCarga() const { return (double)n / tabla.size(); }
long   TablaSecuencias::colisiones()  const { return totalColisiones; }
int    TablaSecuencias::rehashes()    const { return totalRehashes; }

vector<string> TablaSecuencias::ids() const {
    vector<string> lista;
    for (int i = 0; i < (int)tabla.size(); i++)
        if (ocupada[i]) lista.push_back(tabla[i].id);
    return lista;
}






