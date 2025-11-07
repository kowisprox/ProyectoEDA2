#include "HashPacientes.h"
#include <iostream>
using namespace std;

HashPacientes::HashPacientes(int capacidad) {
    this->capacidad = capacidad;
    tabla = new Paciente[capacidad];
    for (int i = 0; i < capacidad; i++) {
        tabla[i].idPaciente = -1;
    }
}

void HashPacientes::insertar(int id, string nombre, int urgencia) {
    int index = id % capacidad;
    while (tabla[index].idPaciente != -1) {
        index = (index + 1) % capacidad;
    }
    tabla[index] = {id, nombre, urgencia};
}

Paciente HashPacientes::buscar(int id) {
    int index = id % capacidad;
    int start = index;
    while (tabla[index].idPaciente != -1) {
        if (tabla[index].idPaciente == id)
            return tabla[index];
        index = (index + 1) % capacidad;
        if (index == start) break;
    }
    return {-1, "No encontrado", -1};
}

