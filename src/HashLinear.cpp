#include "HashLinear.h"


TablaSecuencias::TablaSecuencias()
    : tabla(TAM_INICIAL_TABLA1), ocupada(TAM_INICIAL_TABLA1, false), n(0) {}

void TablaSecuencias::insertar(const DNASequence& s) { (void)s; }

const DNASequence* TablaSecuencias::buscar(const string& id) const { (void)id; return nullptr; }

int    TablaSecuencias::cantidad()    const { return n; }
int    TablaSecuencias::capacidad()   const { return (int)tabla.size(); }
double TablaSecuencias::factorCarga() const { return (double)n / tabla.size(); }

vector<string> TablaSecuencias::ids() const { return {}; }

int  TablaSecuencias::hashId(const string& id) const { (void)id; return 0; }
void TablaSecuencias::rehash() {}