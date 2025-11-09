#ifndef REDMAIN_H
#define REDMAIN_H

#include <iostream>
#include <string>
#include "HashPacientes.h"
#include "HeapUrgencias.h"
#include "ArbolCitas.h"

using namespace std;


class RedMain {
private:

    int diaActual;
    int horaActualCitas;

    HashPacientes hash;
    HeapUrgencias heap;
    ArbolCitas arbolCitas;

    void cargarPacientesDesdeArchivo(const string& nombreArchivo);
    void avanzarProximaCita();
    int generarLlaveCita();
    void atenderYAgendar();
    void mostrarMenuPrincipal();
    int solicitarHoraValida();
    void opcionBuscarPaciente();
    void opcionAtenderN();
    void opcionReprogramarCita();
    void opcionCancelarCita();

public:
    RedMain(); //
    void iniciarSimulacion();
};

#endif
