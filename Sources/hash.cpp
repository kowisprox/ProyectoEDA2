#include "TablaHash.h"
#include <iostream>
#include <cmath> // Para las funciones matemáticas

using namespace std;

TablaHash::TablaHash(int t) {
    colisiones = 0;
    tam = t;
    tabla = new int[tam]; // Pides memoria
    elementos = 0;
    for (int i = 0; i < tam; i++)
        tabla[i] = -1; // -1 significa vacío
}

// ¡Importante! Si usas 'new', debes usar 'delete'
TablaHash::~TablaHash() {
    delete[] tabla; // Liberas la memoria
}

int TablaHash::funcionHash(int clave) {
    return clave % tam;
}

int TablaHash::funcionHashNegativa(int clave) {
    int r = clave % tam;
    if (r < 0)
        r = r + tam;
    return r;
}

int TablaHash::funcionHash2(int clave) {
    double A = 0.6180339887;
    double fraccion = (clave * A) - int(clave * A);
    int hash = int(tam * fraccion);
    return hash;
}

float TablaHash::factorCarga() {
    float carga = (float)elementos / tam;
    return carga;
}

void TablaHash::insertar(int clave) {
    // Usas sondeo lineal
    int pos = funcionHash2(clave);
    int intentos = 0;
    while (tabla[pos] != -1 && intentos < tam) { // -1 es vacío
        pos = (pos + 1) % tam;
        intentos++;
        if (intentos > 1) { // Solo cuenta si no es el primer intento
           colisiones++;
        }
    }

    if (intentos < tam) {
        tabla[pos] = clave;
        elementos++;
    } else {
        cout << "La tabla esta llena" << endl;
    }
}

int TablaHash::numeroColisiones() {
    return colisiones;
}

void TablaHash::imprimir() {
    for (int i = 0; i < tam; i++) {
        cout << i << ": ";
        if (tabla[i] == -1)
            cout << " Vacio" << endl;
        else
            cout << tabla[i] << endl;
    }
}

// ¡¡NO HAY MAIN AQUÍ!!

