#include "HashDouble.h"

// TODO (Alumno 1): implementar en el Paso 3

TablaKmers::TablaKmers(int k) : kLen(k), n(0) {
    long m = 1;
    for (int i = 0; i < k; i++) m *= 4;   // m = 4^k   (k=3 -> 64)
    m = siguientePrimo(m);                // 64 -> 67
    claves.assign(m, "");
    conteos.assign(m, 0);
}

void TablaKmers::contarSecuencia(const string& seq) { (void)seq; }
void TablaKmers::insertar(const string& kmer) { (void)kmer; }
int  TablaKmers::buscar(const string& kmer) const { (void)kmer; return 0; }

vector<KmerCount> TablaKmers::obtenerTodos() const { return {}; }
int TablaKmers::k()         const { return kLen; }
int TablaKmers::capacidad() const { return (int)claves.size(); }
int TablaKmers::distintos() const { return n; }

long TablaKmers::codificar(const string& kmer) const { (void)kmer; return 0; }
int  TablaKmers::h1(long x) const { (void)x; return 0; }
int  TablaKmers::h2(long x) const { (void)x; return 1; }