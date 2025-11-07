#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <iostream>

using namespace std;

// Lo llamo "TablaHash" para que coincida con tu código
class TablaHash {
private:
    int* tabla;
    int tam;
    int colisiones;
    int elementos;

    // Funciones privadas
    int funcionHash(int clave);
    int funcionHashNegativa(int clave);
    int funcionHash2(int clave); // Esta es la que usas (multiplicación)

public:
    TablaHash(int t); // Constructor
    ~TablaHash(); // Destructor (¡importante!)

    float factorCarga();
    void insertar(int clave);
    int numeroColisiones();
    void imprimir();

    // Necesitarás una función de búsqueda para tu proyecto
    // bool buscar(int clave);
};

#endif // TABLAHASH_H

