#include <iostream>
#include "Parser.h"
#include "HashLinear.h"
using namespace std;

int main() {
    // 1) Parser
    vector<DNASequence> secuencias = parseFasta("data/HIV2_ALL_2021_env_DNA.2000.fasta");
    cout << "Secuencias leidas: " << secuencias.size() << "\n\n";
    if (secuencias.empty()) return 1;

    // 2) Insertar todas en la tabla 1
    TablaSecuencias tabla;
    cout << "Insertando en la tabla 1 (tamano inicial " << tabla.capacidad() << ")...\n";
    for (const DNASequence& s : secuencias)
        tabla.insertar(s);

    cout << "\nResultado final:\n";
    cout << "  Elementos       : " << tabla.cantidad() << "\n";
    cout << "  Capacidad       : " << tabla.capacidad() << "\n";
    cout << "  Factor de carga : " << tabla.factorCarga() << "\n";
    cout << "  Rehashes        : " << tabla.rehashes() << "\n";
    cout << "  Colisiones      : " << tabla.colisiones() << "\n\n";

    // 3) Búsquedas de prueba
    string pruebas[] = { "MAC.US.x.239.M33262",
                         "STM.US.89.STM_37_16.M83293",
                         "NO.EXISTE.123" };
    for (const string& id : pruebas) {
        const DNASequence* r = tabla.buscar(id);
        if (r) cout << "  Encontrado : " << id << " (" << r->sequence.size() << " nt)\n";
        else   cout << "  No existe  : " << id << "\n";
    }
    return 0;
}