#include <iostream>
#include "Parser.h"
#include "HashLinear.h"
#include "HashDouble.h"
using namespace std;

int main() {
    // 1) Parser + tabla 1
    vector<DNASequence> secuencias = parseFasta("data/HIV2_ALL_2021_env_DNA.2000.fasta");
    TablaSecuencias tabla;
    for (const DNASequence& s : secuencias) tabla.insertar(s);
    cout << "\nTabla 1 lista: " << tabla.cantidad() << " secuencias\n\n";

    // 2) Elegir una secuencia por ID (usa la tabla 1)
    string id = "MAC.US.x.239.M33262";
    const DNASequence* s = tabla.buscar(id);
    if (!s) { cout << "No existe " << id << "\n"; return 1; }
    cout << "Secuencia: " << s->id << " (" << s->sequence.size() << " nt)\n\n";

    // 3) Contar k-mers con la tabla 2, para varios k
    int valoresK[] = {3, 5, 8};
    for (int k : valoresK) {
        TablaKmers t(k);
        t.contarSecuencia(s->sequence);
        cout << "k = " << k << "\n";
        cout << "  Capacidad (primo >= 4^k) : " << t.capacidad() << "\n";
        cout << "  Esperados (L - k + 1)    : " << s->sequence.size() - k + 1 << "\n";
        cout << "  Contados + descartados   : " << t.totalKmers() << " + " << t.descartados()
             << " = " << t.totalKmers() + t.descartados() << "\n";
        cout << "  k-mers distintos         : " << t.distintos() << "\n";
        cout << "  Colisiones               : " << t.colisiones() << "\n\n";
    }

    // 4) Búsquedas con k = 3
    TablaKmers t3(3);
    t3.contarSecuencia(s->sequence);
    string pruebas[] = {"ATG", "GGG", "CGC", "ANT"};
    cout << "Busquedas (k = 3):\n";
    for (const string& km : pruebas)
        cout << "  " << km << " -> " << t3.buscar(km) << " veces\n";

    // 5) Lo que se entrega al heap
    cout << "\nobtenerTodos() entrega " << t3.obtenerTodos().size() << " pares (k-mer, conteo)\n";
    return 0;
}