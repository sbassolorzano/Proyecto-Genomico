// Parte b1) — Alumno 1
// Tabla hash con LINEAR PROBING.  Clave = id, valor = DNASequence.
#pragma once
#include "modulos.h"

class TablaSecuencias {
public:
    TablaSecuencias();   // empieza con 10 casilleros

    void insertar(const DNASequence& s);  // agranda si alfa >= 0.75
    const DNASequence* buscar(const string& id) const;  // nullptr si no existe

    int    cantidad()    const;   // cuántas secuencias hay
    int    capacidad()   const;   // cuántos casilleros hay
    double factorCarga() const;   // cantidad / capacidad
    vector<string> ids() const;   // todos los IDs (para el menú)

    //ACTUALIZACION A PARTIR DE AQUI
    long colisiones() const; // Choques por insertar
    int rehashes() const;   //Veces que se agrando la tabla



private:
    vector<DNASequence> tabla; // los casilleros
    vector<bool> ocupada;  // ¿el casillero i tiene algo?
    int n;     // cuántos ocupados
    long totalColisiones;  // Contador para choques entre los numeros 
    int totalRehashes; // Contador para agrandamientos

    int  hashId(const string& id) const;       // la fórmula nombre -> número
    void colocar(const DNASequence& s);
    void rehash();   // la "mudanza" a una tabla más grande
};