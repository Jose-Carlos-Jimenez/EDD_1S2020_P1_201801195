#ifndef PILA_H
#define PILA_H

#include <string>
#include <ListaEnlazada.h>

using namespace std;

class Cambio
{
public:
    string palabraBuscada;
    string palabraReemplazada;
    bool estado;
    char palabra;
    int posicion;
    int tipo;
    Cambio *siguiente;
};

class Pila
{
public:

    Pila(): cima(NULL){};
    ~Pila();
    Cambio *cima;
    int tamanio;
    void push(string, string, bool, char, int, int);
    void push(Cambio*);
    void emptyStack();
    Cambio* pop();
};

Pila::~Pila(){
    while(cima)
    {
        pop();
    }
}

void Pila::emptyStack()
{
    cima = NULL;
}

void Pila::push(string palabraBuscada, string palabraReeemplazada, bool estado
                , char palabra, int posicion, int tipo)
{
    Cambio *nuevo = new Cambio();
    /* Crear un nodo nuevo */
    nuevo->palabraBuscada = palabraBuscada;
    nuevo->palabraReemplazada = palabraReeemplazada;
    nuevo->estado = estado;
    nuevo->palabra = palabra;
    nuevo->posicion = posicion;
    nuevo->tipo = tipo;
    /* Ahora, el comienzo de nuestra pila es en nuevo nodo */
    if(!cima)
    {
        cima = nuevo;
    }
    else
    {
        Cambio *referencia = cima;
        nuevo->siguiente = referencia;
        cima = nuevo;
        tamanio++;
    }
}

void Pila::push(Cambio *nuevo)
{
    if(!cima)
    {
        cima = nuevo;
    }
    else
    {
        Cambio *puntero = cima;
        nuevo->siguiente = puntero;
        cima = nuevo;
    }
    tamanio++;
}

Cambio* Pila::pop()
{
    if(tamanio > 0)
    {
        Cambio *nodo = cima;
        cima = nodo->siguiente;
        tamanio--;
        return nodo;
    }
    return cima;
}


#endif // PILA_Hs
