// Paso 0: verificación del entorno.
// Comprueba que el compilador funciona y que el archivo FASTA se puede leer.
// Este main se reemplazará por el menú en el Paso 4.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    string ruta = (argc > 1) ? argv[1] : "data/HIV2_ALL_2021_env_DNA.2000.fasta";

    ifstream archivo(ruta);
    if (!archivo) {
        cerr << "No se pudo abrir: " << ruta << "\n";
        cerr << "Ejecuta el programa desde la carpeta proyecto-genomico/\n";
        return 1;
    }

    string linea, primerId;
    long totalSecuencias = 0, primeraLongitud = 0, noACGT = 0;

    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back(); // archivo viene con CRLF
        if (linea.empty()) continue;

        if (linea[0] == '>') {
            totalSecuencias++;
            if (totalSecuencias == 1) primerId = linea.substr(1);
        } else {
            if (totalSecuencias == 1) primeraLongitud += linea.size();
            for (char c : linea)
                if (c != 'A' && c != 'C' && c != 'G' && c != 'T') noACGT++;
        }
    }

    cout << "Compilador y lectura OK\n";
    cout << "Secuencias encontradas : " << totalSecuencias << "\n";
    cout << "Primer ID              : " << primerId << "\n";
    cout << "Longitud de la primera : " << primeraLongitud << " nt\n";
    cout << "Caracteres no ACGT     : " << noACGT << " (deben ignorarse al contar k-mers)\n";
    return 0;
}
