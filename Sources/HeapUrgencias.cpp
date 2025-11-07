#include "HeapUrgencias.h"
#include "Paciente.h"

HeapUrgencias::HeapUrgencias(int cap) {
    capacidad = cap;
    heap = new Paciente[capacidad];
    size = 0;
}





void HeapUrgencias::swap(Paciente &a, Paciente &b) {
    Paciente temp = a;
    a = b;
    b = temp;
}

void HeapUrgencias::subir(int i) {
    while (i > 0) {
        int padre = (i - 1) / 2;
        if (heap[i].nivelUrgencia > heap[padre].nivelUrgencia) {
            swap(heap[i], heap[padre]);
            i = padre;
        } else break;
    }
}


void HeapUrgencias::bajar(int i) {
    int mayor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    if (izq < size && heap[izq].nivelUrgencia > heap[mayor].nivelUrgencia)
        mayor = izq;
    if (der < size && heap[der].nivelUrgencia > heap[mayor].nivelUrgencia)
        mayor = der;

    if (mayor != i) {
        swap(heap[i], heap[mayor]);
        bajar(mayor);
    }
}

void HeapUrgencias::insertar(const Paciente& p) {
    if (size >= capacidad) {
        cout << " Heap lleno. No se puede insertar más pacientes.\n";
        return;
    }

    heap[size] = p;
    subir(size);
    size++;
}

Paciente HeapUrgencias::extraerMax() {
    if (size == 0) {
        cout << " No hay pacientes en espera.\n";
        return {-1, "Ninguno", -1};
    }

    Paciente maximo = heap[0];
    heap[0] = heap[size - 1];
    size--;
    bajar(0);
    return maximo;
}


Paciente HeapUrgencias::verMax() const {
    if (size == 0)
        return {-1, "Ninguno", -1};
    return heap[0];
}

bool HeapUrgencias::estaVacio() const {
    return size == 0;
}


int HeapUrgencias::getSize() const {
    return size;
}

void HeapUrgencias::imprimir() const {
    for (int i = 0; i < size; i++) {
        cout << heap[i].nombre << " (" << heap[i].nivelUrgencia << ")";
        if (i < size - 1) cout << " - ";
    }
    cout << endl;
}

