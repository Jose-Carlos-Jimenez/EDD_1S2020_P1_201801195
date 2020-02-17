#ifndef PILA_H
#define PILA_H

#include <string>
#include <ListaDoblementeEnlazada.h>

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
    Cambio *abajo;
};

class Pila
{
public:

    Pila();
    ~Pila();
    Cambio *first;
    Cambio *last;
    int tamanio;
    void push(string, string, bool, char, int, int);
    void push(Cambio*);
    Cambio* pop();
};

Pila::Pila()
{
    tamanio = 0;
    first = new Cambio();
    last = new Cambio();
    last->abajo = first;
}

Pila::~Pila(){
    Cambio *pointer = last;
    while(pointer->abajo != first)
    {
        Cambio *nd =pointer;
        pointer = pointer->abajo;
        delete  nd;
    }
}

void Pila::push(string palabraBuscada, string palabraReeemplazada, bool estado
                , char palabra, int posicion, int tipo)
{
    Cambio *nuevo = new Cambio();
    nuevo->palabraBuscada = palabraBuscada;
    nuevo->palabraReemplazada = palabraReeemplazada;
    nuevo->estado = estado;
    nuevo->palabra = palabra;
    nuevo->posicion = posicion;
    nuevo->tipo = tipo;

    if(tamanio > 0)
    {
        nuevo->abajo = last;
        last = nuevo;
    }
    else
    {
        nuevo->abajo = last;
        last = nuevo;
    }
    tamanio++;
}

void Pila::push(Cambio* nuevo)
{


    if(tamanio > 0)
    {
     nuevo->abajo = first;
     last = nuevo;
    }
    else
    {
     nuevo->abajo = last;
     last = nuevo;
    }
    tamanio++;
}

Cambio* Pila::pop()
{
    Cambio *referencia = last;
    last->abajo = last->abajo;
    return  referencia;
}


#endif // PILA_Hs
