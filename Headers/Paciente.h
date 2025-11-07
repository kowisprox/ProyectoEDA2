#ifndef PACIENTE_H
#define PACIENTE_H

#include <iostream>
#include <string>
using namespace std;

struct Paciente {
    int idPaciente;
    string nombre;
    int nivelUrgencia;
    string estado;

    Paciente() {
        idPaciente = -1;
        nombre = "";
        nivelUrgencia = 0;
        estado = "En espera";
    }

    Paciente(int id, string nom, int urg, string est) {
        idPaciente = id;
        nombre = nom;
        nivelUrgencia = urg;
        estado = est;
    }
};

#endif
// PACIENTE_H_INCLUDED

