#include "HashDouble.h"


TablaKmers::TablaKmers(int k)
    : kLen(k), n(0), total(0), totalDescartados(0), totalColisiones(0) {
    long m = 1;
    for (int i = 0; i < k; i++) m *= 4;   // m = 4^k   (k=3 -> 64)
    m = siguientePrimo(m);                // 64 -> 67
    claves.assign(m, "");
    conteos.assign(m, 0);
}


// Codifica los k-mers -> numero en base 4 (ATG = 0*16 + 3*4 + 2 = 14)
// Devuelve -1 si no es las letras A C G T
long TablaKmers::codificar(const string & kmer) const
{
    long x = 0;
    for (char c : kmer)
    {
        int v = valorBase(c);
        if (v < 0)
            return -1;
        x = x * 4 + v;
    }
    return x;
}

// h1 : Posicion inicial
// h2 : tamaño del salto -> 1+ (codigo base mod 4 (m-1))

int TablaKmers::h1(const string & kmer) const
{
    unsigned long long h = 0;
    int m = (int)claves.size();
    for (char c : kmer)
        h = (h * 31 + (unsigned char)c) % m;
    return (int)h;
}

int TablaKmers::h2(long x) const
{
    int m = (int)claves.size();
    return 1 + (int)(x % (m - 1));
}

// Metodo Insertar : si el kmer existe se suma 1
void TablaKmers::insertar(const string &kmer)
{
    long x = codificar(kmer);
    if (x < 0)
    {
        totalDescartados++;
        return;
    } // Alguna letra rara se descarta

    int m = (int)claves.size();
    int pos = h1(kmer);
    int salto = h2(x);

    for (int intentos = 0; intentos < m; intentos++)
    {
        if (conteos[pos] == 0)
        { // casillero vacío: nuevo k-mer
            claves[pos] = kmer;
            conteos[pos] = 1;
            n++;
            total++;
            return;
        }
        if (claves[pos] == kmer)
        { // Su ya existe se suma 1
            conteos[pos]++;
            total++;
            return;
        }
        totalColisiones++;       // ocupado por otro k-mer
        pos = (pos + salto) % m; // saltar
    }
}
// En el metodo contar Se realiza un deslizancia 1 en 1 en la secuencia
void TablaKmers::contarSecuencia(const string &seq)
{
    if ((int)seq.size() < kLen)
        return;
    for (size_t i = 0; i + kLen <= seq.size(); i++)
        insertar(seq.substr(i, kLen));
}

// Metodo para buscar
int TablaKmers::buscar(const string &kmer) const
{
    long x = codificar(kmer);
    if (x < 0 || (int)kmer.size() != kLen)
        return 0;

    int m = (int)claves.size();
    int pos = h1(kmer);
    int salto = h2(x);

    for (int intentos = 0; intentos < m; intentos++)
    {
        if (conteos[pos] == 0)
            return 0; // vacío: no está
        if (claves[pos] == kmer)
            return conteos[pos];
        pos = (pos + salto) % m;
    }
    return 0;
}

//Entros todo al MaxHeap
vector<KmerCount> TablaKmers::obtenerTodos() const {
    vector<KmerCount> lista;
    for (int i = 0; i < (int)claves.size(); i++)
        if (conteos[i] > 0)
            lista.push_back({claves[i], conteos[i]});
    return lista;
}

//Medidores

int  TablaKmers::k()           const { return kLen; }
int  TablaKmers::capacidad()   const { return (int)claves.size(); }
int  TablaKmers::distintos()   const { return n; }
long TablaKmers::totalKmers()  const { return total; }
long TablaKmers::descartados() const { return totalDescartados; }
long TablaKmers::colisiones()  const { return totalColisiones; }
