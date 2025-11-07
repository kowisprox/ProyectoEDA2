#ifndef HASHPACIENTES_H
#define HASHPACIENTES_H
#include "Paciente.h"
#include <string>
using namespace std;



class HashPacientes {
private:
    int capacidad;
    Paciente* tabla;
    Paciente P_NoEncontrado;

    int hashFuncion(int id);

public:
    HashPacientes(int tam = 1007);

    void insertar(int id, string nombre, int urgencia, string estado);

    Paciente& buscar(int id);
};

#endif
 // HASHPACIENTES_H_INCLUDED

