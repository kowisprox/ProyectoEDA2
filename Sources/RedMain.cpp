#include "RedMain.h"
#include <fstream>
#include <sstream>

RedMain::RedMain()
    : diaActual(1),
      horaActualCitas(0),
      hash(15000),
      heap(15000),
      arbolCitas()
{

}


void RedMain::iniciarSimulacion() {
    string respuesta;
    cout << "\n--------------------------------\n";
    cout << "  SISTEMA DE TRIAGE HOSPITALARIO\n";
    cout << "----------------------------------\n";
    cout << "Desea cargar los pacientes desde el archivo? (si/no): ";
    cin >> respuesta;
    if (respuesta == "si" || respuesta == "SI") {
        cargarPacientesDesdeArchivo("pacientesEDA.txt");
    } else {
        cout << "No se cargaron pacientes. Saliendo del sistema...\n";
        return;
    }

    int opcion;
    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1:
                opcionBuscarPaciente();
                break;
            case 2:
                atenderYAgendar();
                break;
            case 3:
                opcionAtenderN();
                break;
            case 4:
                cout << "Pacientes restantes por atender: " << heap.getSize() << endl;
                break;
            case 5:
                arbolCitas.mostrarCitasOrdenadas();
                break;
            case 6:
                opcionReprogramarCita();
                break;
            case 7:
                opcionCancelarCita();
                break;
            case 8:
                cout << "\nSaliendo del sistema...\n";
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente.\n";
        }

    } while (opcion != 8);
}

void RedMain::cargarPacientesDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) { cout << "No se pudo abrir el archivo: " << nombreArchivo << endl; return; }
    string linea; int id, urgencia; string nombre; string estado = "En espera";
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea); string idStr, nombreStr, urgenciaStr;
        getline(ss, idStr, ','); getline(ss, nombreStr, ','); getline(ss, urgenciaStr, ',');
        id = stoi(idStr); nombre = nombreStr; urgencia = stoi(urgenciaStr);
        hash.insertar(id, nombre, urgencia, estado);
        heap.insertar({id, nombre, urgencia, estado});
    }
    archivo.close();
    cout << "Pacientes cargados correctamente desde " << nombreArchivo << endl;
}

void RedMain::avanzarProximaCita() {
    horaActualCitas += 10;
    if (horaActualCitas % 100 >= 60) {
        horaActualCitas = (horaActualCitas / 100 + 1) * 100;
    }
    if (horaActualCitas >= 2400) {
        horaActualCitas = 0;
        diaActual++;
        cout << "\n-------------------------------------------------";
        cout << "\nTERMINO EL DIA. COMENZANDO DIA " << diaActual;
        cout << "\n-------------------------------------------------\n";
    }
}

int RedMain::generarLlaveCita() {
    return diaActual * 10000 + horaActualCitas;
}

void RedMain::atenderYAgendar() {
    if (heap.estaVacio()) { cout << "No hay pacientes pendientes\n"; return; }

    Paciente pHeap = heap.extraerMax();
    Paciente &pHash = hash.buscar(pHeap.idPaciente);
    pHash.estado = "Atendido";
    cout<<"Atendiendo a: "<<pHash.nombre<<" con ID: "<<pHash.idPaciente<<" (Urgencia "<<pHash.nivelUrgencia<<")\n";

    while (true) {
        int nuevaLlave = generarLlaveCita();
        int horaCita = (int)(nuevaLlave % 10000);
        Cita nuevaCita(nuevaLlave, pHash.idPaciente, pHash.nombre);

        if (arbolCitas.insertarCita(nuevaCita)) {
            cout << "Agendando cita de seguimiento para Dia " << diaActual << ", Hora " << horaCita << "...\n";
            avanzarProximaCita();
            break;
        } else {
            cout << "  ...Buscando siguiente horario disponible...\n";
            avanzarProximaCita();
        }
    }
}

void RedMain::mostrarMenuPrincipal() {
    cout << "\n";
    cout << "  +------------------------------------+\n";
    cout << "  |     SISTEMA DE TRIAGE HOSPITALARIO |\n";
    cout << "  +------------------------------------+\n";
    cout << "  | (Dia " << diaActual << " - " << horaActualCitas << "hs)\n";
    cout << "  |------------------------------------|\n";
    cout << "  | 1. Buscar paciente por ID          |\n";
    cout << "  | 2. Atender siguiente paciente      |\n";
    cout << "  | 3. Atender N pacientes (Prueba)    |\n";
    cout << "  | 4. Mostrar cantidad pendiente      |\n";
    cout << "  | 5. Mostrar citas agendadas         |\n";
    cout << "  | 6. Reprogramar Cita                |\n";
    cout << "  | 7. Cancelar Cita (Solo Eliminar)   |\n";
    cout << "  | 8. Salir                           |\n";
    cout << "  +------------------------------------+\n";
    cout << "  Seleccione una opcion: ";
}

int RedMain::solicitarHoraValida() {
    int hora;
    while(true) {
        cin >> hora;
        if ((hora % 100 < 60) && (hora >= 0 && hora < 2400)) {
            return hora;
        } else {
            cout << "Hora invalida. Use formato militar (ej: 930, 1400, 0 para medianoche).\n";
            cout << "Intente de nuevo: ";
        }
    }
}

void RedMain::opcionBuscarPaciente() {
    int idBuscado;
    cout<<"\nIngrese el ID del paciente: ";
    cin>>idBuscado;
    Paciente encontrado = hash.buscar(idBuscado);
    if (encontrado.idPaciente != -1)
        cout<<"Paciente encontrado: "<<encontrado.nombre<<" (Urgencia: "<<encontrado.nivelUrgencia<<"), Estado: "<<encontrado.estado<<"\n";
    else
        cout<<"El Paciente con el ID:"<<idBuscado<<" no existe\n";
}

void RedMain::opcionAtenderN() {
    cout << "Ingrese la cantidad de pacientes a atender (ej: 2000): ";
    int cantidad;
    cin >> cantidad;
    cout << "\nIniciando atencion masiva...\n";
    for (int i = 0; i < cantidad && !heap.estaVacio(); i++) {
        atenderYAgendar();
    }
    cout << "\nAtencion masiva terminada.\n";
}

void RedMain::opcionReprogramarCita() {
    cout << "--- Reprogramacion de Cita ---\n";
    cout << "Ingrese el ID del paciente que desea reprogramar: ";
    int idPac;
    cin >> idPac;

    Cita citaActual = arbolCitas.buscarCitaPorPaciente(idPac);

    if (citaActual.horaDiaKey == -1) {
        cout << "Error: El paciente con ID " << idPac << " no tiene ninguna cita agendada.\n";
        return;
    }

    cout << "Cita encontrada:\n";
    cout << "  Paciente: " << citaActual.nombrePaciente << " (ID: " << citaActual.idPaciente << ")\n";
    cout << "  Dia: " << (citaActual.horaDiaKey / 10000) << ", Hora: " << (int)(citaActual.horaDiaKey % 10000) << "\n";

    while (true) {
        cout << "\nIngrese los datos de la NUEVA cita:\n";
        cout << "Ingrese el NUEVO Dia (ej: 2): ";
        int diaNuevo; cin >> diaNuevo;
        cout << "Ingrese la NUEVA Hora (ej: 1400 para 2:00 PM): ";
        int horaNueva = solicitarHoraValida();
        int llaveNueva = diaNuevo * 10000 + horaNueva;

        if (llaveNueva == citaActual.horaDiaKey) {
            cout << "Error: Esta intentando reprogramar a la misma hora. Intente de nuevo.\n";
            continue;
        }
        Cita nuevaCita(llaveNueva, citaActual.idPaciente, citaActual.nombrePaciente);

        if (arbolCitas.insertarCita(nuevaCita)) {
            cout << "Reprogramacion exitosa.\n";
            arbolCitas.cancelarCita(citaActual.horaDiaKey);
            break;
        } else {
            cout << "Por favor, elija otro horario.\n";
        }
    }
}

void RedMain::opcionCancelarCita() {
    cout << "--- Cancelacion de Cita ---\n";
    cout << "Ingrese el ID del paciente que desea CANCELAR su cita: ";
    int idPac;
    cin >> idPac;

    Cita citaActual = arbolCitas.buscarCitaPorPaciente(idPac);

    if (citaActual.horaDiaKey == -1) {
        cout << "Error: El paciente con ID " << idPac << " no tiene ninguna cita agendada.\n";
        return;
    }

    cout << "Cita encontrada y lista para cancelar:\n";
    cout << "  Paciente: " << citaActual.nombrePaciente << " (ID: " << citaActual.idPaciente << ")\n";
    cout << "  Dia: " << (citaActual.horaDiaKey / 10000) << ", Hora: " << (int)(citaActual.horaDiaKey % 10000) << "\n";

    arbolCitas.cancelarCita(citaActual.horaDiaKey);

    cout << "Cita cancelada exitosamente.\n";
}
