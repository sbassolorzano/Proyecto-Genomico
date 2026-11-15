#include "Parser.h"
#include <fstream>
#include <iostream>

//Convertir el archivo FASTA en una lista de 218 fichas
// Cada ficha contiene un ID y un sequence

vector<DNASequence> parseFasta(const string& ruta){
    vector<DNASequence> resultado;
    
    ifstream archivo(ruta);
    if (!archivo) {
        cerr << "No se puedo abrir " << ruta << "\n";
        return resultado;
    }

    string linea;
    while (getline(archivo, linea)) { //Recorre toda la linea
        if (!linea.empty() && linea.back() == '\r') // Quita el \r del final en caso de window
            linea.pop_back();

        if (linea.empty()) continue; //Salta fichas

        if (linea[0] == '>') { //Detecta el inicio de una nuevo registro , a partir del >
            DNASequence nueva;
            nueva.id = linea.substr(1); // Busca la secuencia MAC.US .......
            nueva.sequence = ""; 
            resultado.push_back(nueva); // La agrega
        } else {
            if (resultado.empty()) continue; // Pega cada letra a la ultima ficha
            for (char c : linea) {
                if (c >= 'a' && c <= 'z') c = c - 'a' + 'A'; // De minusculas a mayusculas
                if (c != ' ' && c != '\t') resultado.back().sequence += c; // Secuencias limpias
            }
        }
    }
    return resultado;
    
}



