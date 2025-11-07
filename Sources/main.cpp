#include <iostream>
#include <fstream>
#include <sstream>
#include "HashPacientes.h"
#include "HeapUrgencias.h"
using namespace std;

void cargarPacientesDesdeArchivo(const string& nombreArchivo, HashPacientes &hash, HeapUrgencias &heap) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    int id, urgencia;
    string nombre;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string idStr, nombreStr, urgenciaStr;

        getline(ss, idStr, ',');
        getline(ss, nombreStr, ',');
        getline(ss, urgenciaStr, ',');

        id = stoi(idStr);
        nombre = nombreStr;
        urgencia = stoi(urgenciaStr);

        hash.insertar(id, nombre, urgencia);
        heap.insertar({id, nombre, urgencia});
    }

    archivo.close();
    cout << "Pacientes cargados correctamente desde " << nombreArchivo << endl;
}

int main() {
    HashPacientes hash(10007);
    HeapUrgencias heap(10000);

    cargarPacientesDesdeArchivo("pacientesEDA.txt", hash, heap);


    while (!heap.estaVacio()) {
        Paciente p = heap.extraerMax();
        Paciente datos = hash.buscar(p.idPaciente);
        cout << "Atendiendo a: " << datos.nombre
             << " (Urgencia " << datos.nivelUrgencia << ")\n";
    }

        cout << "\n--- PRUEBA DE BUSQUEDA ---\n";
    int idBuscado = 1007; // cambia por un ID real del archivo
    Paciente encontrado = hash.buscar(idBuscado);
    if (encontrado.idPaciente != -1)
        cout << "Paciente encontrado: " << encontrado.nombre << " (Urgencia " << encontrado.nivelUrgencia << ")\n";
    else
        cout << "Paciente con ID " << idBuscado << " no encontrado.\n";

    return 0;
}
