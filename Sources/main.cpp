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
    string estado = "En espera";

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

        hash.insertar(id, nombre, urgencia, estado);
        heap.insertar({id, nombre, urgencia, estado});
    }

    archivo.close();
    cout << "Pacientes cargados correctamente desde " << nombreArchivo << endl;
}

int main() {
    HashPacientes hash(10000);
    HeapUrgencias heap(10000);
    string respuesta;

    cout << "\n--------------------------------\n";
    cout << "  SISTEMA DE TRIAGE HOSPITALARIO\n";
    cout << "----------------------------------\n";

    cout << "Desea cargar los pacientes desde el archivo? (si/no): ";
    cin >> respuesta;

    if (respuesta == "si" || respuesta == "SI" || respuesta == "Si" || respuesta == "sI"|| respuesta == "sí"|| respuesta == "Sí"|| respuesta == "SÍ"|| respuesta == "sÍ") {
        cargarPacientesDesdeArchivo("pacientesEDA.txt", hash, heap);

    } else {
        cout << "No se cargaron pacientes. Saliendo del sistema...\n";
        return 0;
    }

        int opcion;
    do {
        cout<<"\n--------------------------------\n";
        cout<<"  SISTEMA DE TRIAGE HOSPITALARIO\n";
        cout<<"----------------------------------\n";
        cout<<"1. Buscar paciente por ID\n";
        cout<<"2. Atender siguiente paciente (maxima urgencia)\n";
        cout<<"3. Atender multiples pacientes \n";
        cout<<"4. Mostrar cantidad pendiente\n";
        cout<<"5. Salir\n";
        cout<<"------------------------------\n";
        cout<<"Seleccione una opcion: ";
        cin>>opcion;
        cout<<endl;

        switch (opcion) {
            case 1: {
                int idBuscado;
                cout<<"\nIngrese el ID del paciente: ";
                cin>>idBuscado;
                Paciente encontrado = hash.buscar(idBuscado);
                if (encontrado.idPaciente != -1)
                    cout<<"Paciente encontrado: "<<encontrado.nombre<<" (Urgencia: "<<encontrado.nivelUrgencia<<"), Estado: "<<encontrado.estado<<"\n";
                else
                    cout<<"El Paciente con el ID:"<<idBuscado<<" no existe\n";
                break;
            }
            case 2: {
                if (heap.estaVacio()) {
                    cout<<"No hay pacientes pendientes\n";
                } else {
                    Paciente pHeap = heap.extraerMax();
                    Paciente &pHash = hash.buscar(pHeap.idPaciente);
                    pHash.estado = "Atendido";
                    cout<<"Atendiendo a: "<<pHash.nombre<<"con ID: "<<pHash.idPaciente<<"(Urgencia "<<pHash.nivelUrgencia<<"), Estado: "<<pHash.estado<<"\n";
                }
                break;
            }
            case 3:
                if (heap.estaVacio()) {
                    cout << "No hay pacientes pendientes\n";
                    break;
                    }

                int cantidad;
                cout << "Ingrese la cantidad de pacientes a atender (0 para todos): ";
                cin >> cantidad;

                if (cantidad == 0) {
                    while (!heap.estaVacio()) {
                    Paciente pHeap = heap.extraerMax();
                    Paciente &pHash = hash.buscar(pHeap.idPaciente);
                    pHash.estado = "Atendido";
                    cout<<"Atendiendo a: "<<pHash.nombre<<"con ID: "<<pHash.idPaciente<<"(Urgencia "<<pHash.nivelUrgencia<<"), Estado: "<<pHash.estado<<"\n";
                        }
                }
                else{
                    for (int i = 0; i < cantidad && !heap.estaVacio(); i++) {
                    Paciente pHeap = heap.extraerMax();
                    Paciente &pHash = hash.buscar(pHeap.idPaciente);
                    pHash.estado = "Atendido";
                    cout<<"Atendiendo a: "<<pHash.nombre<<"con ID: "<<pHash.idPaciente<<"(Urgencia "<<pHash.nivelUrgencia<<"), Estado: "<<pHash.estado<<"\n";
                            }
                        }
                    break;
            case 4:
                cout<<"Pacientes restantes por atender: "<<heap.getSize()<< endl;
                break;
            case 5:
                cout<<"\nSaliendo del sistema...\n";
                break;
            default:
                cout<<"Opcion no valida. Intente nuevamente.\n";
        }

    }while(opcion != 5);

    return 0;
}


