#ifndef PACIENTE_H
#define PACIENTE_H

#include <iostream>
#include <string>
using namespace std;

struct Paciente {
    int idPaciente;
    string nombre;
    int nivelUrgencia;

    Paciente() {
        idPaciente = -1;
        nombre = "";
        nivelUrgencia = 0;
    }

    Paciente(int id, string nom, int urg) {
        idPaciente = id;
        nombre = nom;
        nivelUrgencia = urg;
    }
};

#endif
// PACIENTE_H_INCLUDED

