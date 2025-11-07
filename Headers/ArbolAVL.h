#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <iostream>
#include <algorithm> // Para std::max

using namespace std;

// --- Clase Nodo ---
// Es buena práctica definir la clase Node aquí mismo
class Node {
private:
    int dato;
    int altura;
    Node * izquierda;
    Node * derecha;

public:
    Node(int n); // Constructor

    // Hacemos "friend" a la clase ArbolAVL para que pueda acceder a los datos
    friend class ArbolAVL;
};

// --- Clase ArbolAVL ---
class ArbolAVL {
private:
    Node* raiz;

    // --- Funciones privadas de ayuda (las "recursivas") ---
    int altura(Node *nodo);
    int factorBalance(Node *nodo);
    void actualizarAltura(Node *nodo);
    Node* rotacionIzquierda(Node *actualRaiz);
    Node* rotacionDerecha(Node *actualRaiz);

    // Funciones recursivas
    void insertar(Node*& nodo, int n);
    void inorder(Node* nodo);
    void preorder(Node *nodo);
    bool buscar(Node* nodo, int n);

public:
    ArbolAVL(); // Constructor

    // --- Funciones públicas (las que llamará el main) ---
    void insertarR(int n);
    void inorderR();
    void preorderR();
    bool buscarR(int n);
};

#endif // ARBOLAVL_H

