#include "ArbolAVL.h" // Incluye el "menú"
#include <iostream>
#include <algorithm> // Para std::max

using namespace std;

// --- Implementación de Node ---
Node::Node(int n) {
    dato = n;
    altura = 1;
    izquierda = nullptr;
    derecha = nullptr;
}

// --- Implementación de ArbolAVL ---
ArbolAVL::ArbolAVL() {
    raiz = nullptr;
}

int ArbolAVL::altura(Node *nodo) {
    return nodo ? nodo->altura : 0;
}

int ArbolAVL::factorBalance(Node *nodo) {
    return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
}

void ArbolAVL::actualizarAltura(Node *nodo) {
    int alt = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));
    nodo->altura = alt;
}

Node* ArbolAVL::rotacionIzquierda(Node *actualRaiz) {
    Node *nuevaRaiz = actualRaiz->derecha;
    Node *subArbol = nuevaRaiz->izquierda;

    nuevaRaiz->izquierda = actualRaiz;
    actualRaiz->derecha = subArbol;

    actualizarAltura(actualRaiz);
    actualizarAltura(nuevaRaiz);

    return nuevaRaiz;
}

Node* ArbolAVL::rotacionDerecha(Node *actualRaiz) {
    Node *nuevaRaiz = actualRaiz->izquierda;
    Node *subArbol = nuevaRaiz->derecha;

    nuevaRaiz->derecha = actualRaiz;
    actualRaiz->izquierda = subArbol;

    actualizarAltura(actualRaiz);
    actualizarAltura(nuevaRaiz);

    return nuevaRaiz;
}

void ArbolAVL::insertar(Node*& nodo, int n) {
    if (nodo == nullptr) {
        nodo = new Node(n);
        return; // Añadido return para eficiencia
    }

    if (n < nodo->dato) {
        insertar(nodo->izquierda, n);
    } else { // Asumimos que no se permiten duplicados, o van a la derecha
        insertar(nodo->derecha, n);
    }

    actualizarAltura(nodo);
    int facBalance = factorBalance(nodo);

    // der - der
    if (facBalance < -1 && n > nodo->derecha->dato) {
        nodo = rotacionIzquierda(nodo);
    }
    // izq - izq
    if (facBalance > 1 && n < nodo->izquierda->dato) {
        nodo = rotacionDerecha(nodo);
    }
    // izq - der
    if (facBalance > 1 && n > nodo->izquierda->dato) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        nodo = rotacionDerecha(nodo);
    }
    // der - izq
    if (facBalance < -1 && n < nodo->derecha->dato) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        nodo = rotacionIzquierda(nodo);
    }
}

void ArbolAVL::inorder(Node* nodo) {
    if (nodo != nullptr) {
        inorder(nodo->izquierda);
        cout << nodo->dato << " ";
        inorder(nodo->derecha);
    }
}

void ArbolAVL::preorder(Node *nodo) {
    if (nodo != nullptr) {
        cout << nodo->dato << " ";
        preorder(nodo->izquierda);
        preorder(nodo->derecha);
    }
}

bool ArbolAVL::buscar(Node* nodo, int n) {
    if (nodo == nullptr)
        return false;
    if (n == nodo->dato)
        return true;
    if (n < nodo->dato)
        return buscar(nodo->izquierda, n);
    else
        return buscar(nodo->derecha, n);
}

// --- Funciones Públicas ---
void ArbolAVL::insertarR(int n) {
    insertar(raiz, n);
}

void ArbolAVL::inorderR() {
    inorder(raiz);
}

void ArbolAVL::preorderR() {
    preorder(raiz);
}

bool ArbolAVL::buscarR(int n) {
    return buscar(raiz, n);
}


