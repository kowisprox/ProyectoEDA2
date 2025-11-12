#include "ArbolCitas.h"
#include <iostream>
#include <algorithm>

using namespace std;

Cita ArbolCitas::CITA_NO_ENCONTRADA = Cita(-1, -1, "No Encontrada");

Node::Node(Cita n) {
    datosCita = n;
    altura = 1;
    izquierda = nullptr;
    derecha = nullptr;
}

ArbolCitas::ArbolCitas() {
    raiz = nullptr;
}

int ArbolCitas::altura(Node *nodo) { return nodo ? nodo->altura : 0; }
int ArbolCitas::factorBalance(Node *nodo) { return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0; }
void ArbolCitas::actualizarAltura(Node *nodo) { nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha)); }
Node* ArbolCitas::rotacionIzquierda(Node *actualRaiz) {
    Node *nuevaRaiz = actualRaiz->derecha; Node *subArbol = nuevaRaiz->izquierda;
    nuevaRaiz->izquierda = actualRaiz; actualRaiz->derecha = subArbol;
    actualizarAltura(actualRaiz); actualizarAltura(nuevaRaiz); return nuevaRaiz;
}
Node* ArbolCitas::rotacionDerecha(Node *actualRaiz) {
    Node *nuevaRaiz = actualRaiz->izquierda; Node *subArbol = nuevaRaiz->derecha;
    nuevaRaiz->derecha = actualRaiz; actualRaiz->izquierda = subArbol;
    actualizarAltura(actualRaiz); actualizarAltura(nuevaRaiz); return nuevaRaiz;
}

bool ArbolCitas::insertar(Node*& nodo, Cita nuevaCita) {
    if (nodo == nullptr) {
        nodo = new Node(nuevaCita); return true;
    }
    bool exito;

    if (nuevaCita.horaDiaKey < nodo->datosCita.horaDiaKey) {
        exito = insertar(nodo->izquierda, nuevaCita);
    } else if (nuevaCita.horaDiaKey > nodo->datosCita.horaDiaKey) {
        exito = insertar(nodo->derecha, nuevaCita);
    } else {

        cout << "\n>> ERROR: Choque de horario. La cita " << nuevaCita.horaDiaKey
             << " ya esta ocupada por " << nodo->datosCita.nombrePaciente << ".\n";
        return false;
    }
    if (!exito) return false;

    actualizarAltura(nodo);
    int facBalance = factorBalance(nodo);
    if (facBalance < -1 && nuevaCita.horaDiaKey > nodo->derecha->datosCita.horaDiaKey) { nodo = rotacionIzquierda(nodo); }
    if (facBalance > 1 && nuevaCita.horaDiaKey < nodo->izquierda->datosCita.horaDiaKey) { nodo = rotacionDerecha(nodo); }
    if (facBalance > 1 && nuevaCita.horaDiaKey > nodo->izquierda->datosCita.horaDiaKey) { nodo->izquierda = rotacionIzquierda(nodo->izquierda); nodo = rotacionDerecha(nodo); }
    if (facBalance < -1 && nuevaCita.horaDiaKey < nodo->derecha->datosCita.horaDiaKey) { nodo->derecha = rotacionDerecha(nodo->derecha); nodo = rotacionIzquierda(nodo); }
    return true;
}

// Función de eliminación 
Node* ArbolCitas::encontrarMin(Node* nodo) {
    while (nodo->izquierda != nullptr) { nodo = nodo->izquierda; }
    return nodo;
}
void ArbolCitas::eliminar(Node*& nodo, int horaDiaKey) { 
    if (nodo == nullptr) return;
    if (horaDiaKey < nodo->datosCita.horaDiaKey) { eliminar(nodo->izquierda, horaDiaKey); }
    else if (horaDiaKey > nodo->datosCita.horaDiaKey) { eliminar(nodo->derecha, horaDiaKey); }
    else {
        if (nodo->izquierda == nullptr || nodo->derecha == nullptr) {
            Node* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
            if (temp == nullptr) { temp = nodo; nodo = nullptr; } else { *nodo = *temp; }
            delete temp;
        } else {
            Node* temp = encontrarMin(nodo->derecha);
            nodo->datosCita = temp->datosCita;
            eliminar(nodo->derecha, temp->datosCita.horaDiaKey);
        }
    }
    if (nodo == nullptr) return;
    actualizarAltura(nodo);
    int facBalance = factorBalance(nodo);
    if (facBalance > 1 && factorBalance(nodo->izquierda) >= 0) { nodo = rotacionDerecha(nodo); return; }
    if (facBalance > 1 && factorBalance(nodo->izquierda) < 0) { nodo->izquierda = rotacionIzquierda(nodo->izquierda); nodo = rotacionDerecha(nodo); return; }
    if (facBalance < -1 && factorBalance(nodo->derecha) <= 0) { nodo = rotacionIzquierda(nodo); return; }
    if (facBalance < -1 && factorBalance(nodo->derecha) > 0) { nodo->derecha = rotacionDerecha(nodo->derecha); nodo = rotacionIzquierda(nodo); }
}

// Funciones públicas
bool ArbolCitas::insertarCita(Cita nuevaCita) { return insertar(raiz, nuevaCita); }
void ArbolCitas::cancelarCita(int horaDiaKey) { eliminar(raiz, horaDiaKey); }

// Funciones de impresión
void ArbolCitas::inorder(Node* nodo) {
    if (nodo != nullptr) {
        inorder(nodo->izquierda);

        int llave = nodo->datosCita.horaDiaKey;
        int dia = llave / 10000;
        int hora = llave % 10000;

        cout << "  - Dia " << dia << ", Hora " << hora
             << " | Paciente: " << nodo->datosCita.nombrePaciente
             << " (ID: " << nodo->datosCita.idPaciente << ")\n";

        inorder(nodo->derecha);
    }
}
void ArbolCitas::mostrarCitasOrdenadas() {
    cout << "\n--- Citas Programadas (En Orden) --- \n";
    if(raiz == nullptr) { cout << "  (No hay citas en la agenda)\n"; return; }
    inorder(raiz);
    cout << "------------------------------------ \n";
}

// Búsqueda por ID 
void ArbolCitas::buscarRecursivo(Node* nodo, int idPaciente, Cita& resultado) {
    if (nodo == nullptr || resultado.horaDiaKey != -1) { return; }
    if (nodo->datosCita.idPaciente == idPaciente) { resultado = nodo->datosCita; return; }
    buscarRecursivo(nodo->izquierda, idPaciente, resultado);
    buscarRecursivo(nodo->derecha, idPaciente, resultado);
}
Cita ArbolCitas::buscarCitaPorPaciente(int idPaciente) {
    Cita resultado = CITA_NO_ENCONTRADA;
    buscarRecursivo(raiz, idPaciente, resultado);
    return resultado;
}
