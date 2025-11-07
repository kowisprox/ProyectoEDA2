#ifndef HEAPURGENCIAS_H
#define HEAPURGENCIAS_H
#include "Paciente.h"
#include "HashPacientes.h"
#include <iostream>
#include <algorithm>
using namespace std;

class HeapUrgencias {
private:
    Paciente* heap;
    int capacidad;
    int size;

    void subir(int i);
    void bajar(int i);
    void swap(Paciente &a, Paciente &b);
public:
    HeapUrgencias(int cap = 10000);

    void insertar(const Paciente& p);

    Paciente extraerMax();

    bool estaVacio() const;

    Paciente verMax() const;

    void imprimir() const;

    int getSize() const;
};

#endif

