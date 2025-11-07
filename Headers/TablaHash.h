#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <iostream>

using namespace std;

class TablaHash {
private:
    int* tabla;
    int tam;
    int colisiones;
    int elementos;

    int funcionHash(int clave);
    int funcionHashNegativa(int clave);
    int funcionHash2(int clave);

public:
    TablaHash(int t);
    ~TablaHash();

    float factorCarga();
    void insertar(int clave);
    int numeroColisiones();
    void imprimir();

};

#endif // TABLAHASH_H

