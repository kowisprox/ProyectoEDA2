#ifndef ARBOLCITAS_H
#define ARBOLCITAS_H

#include <iostream>
#include <string>
#include <algorithm>
#include "Paciente.h"

using namespace std;

struct Cita {
    int horaDiaKey;
    int idPaciente;
    string nombrePaciente;

    Cita() : horaDiaKey(0), idPaciente(-1), nombrePaciente("") {}
    Cita(int key, int id, string nombre) {
        horaDiaKey = key;
        idPaciente = id;
        nombrePaciente = nombre;
    }
};


class Node {
private:
    Cita datosCita;
    int altura;
    Node * izquierda;
    Node * derecha;
public:
    Node(Cita n);
    friend class ArbolCitas;
};


class ArbolCitas {
private:
    Node* raiz;
    int altura(Node *nodo);
    int factorBalance(Node *nodo);
    void actualizarAltura(Node *nodo);
    Node* rotacionIzquierda(Node *actualRaiz);
    Node* rotacionDerecha(Node *actualRaiz);
    bool insertar(Node*& nodo, Cita nuevaCita);
    void inorder(Node* nodo);
    Node* encontrarMin(Node* nodo);
    void eliminar(Node*& nodo, int horaDiaKey);

    void buscarRecursivo(Node* nodo, int idPaciente, Cita& resultado);

public:
    static Cita CITA_NO_ENCONTRADA;
    ArbolCitas();
    bool insertarCita(Cita nuevaCita);
    void cancelarCita(int horaDiaKey);
    void mostrarCitasOrdenadas();
    Cita buscarCitaPorPaciente(int idPaciente);
};

#endif
