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

    ~Pila();
    ListaEnlazada *buscadas;
    ListaEnlazada *reemplazadas;
    Cambio *cima;
    Pila();
    int tamanio;
    void push(string, string, bool, char, int, int);
    void push(Cambio*);
    void emptyStack();
    Cambio* pop();
};

Pila::Pila()
{
    buscadas= new ListaEnlazada();
    reemplazadas = new ListaEnlazada();
    cima = NULL;
}

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

    if(nuevo->estado == true && palabraBuscada != "NULL")
    {
        reemplazadas->addWord(palabraBuscada,palabraReeemplazada);
    }
    else
    {
        if(palabraBuscada!= "NULL")
        {
            buscadas->addWord(palabraBuscada, palabraReeemplazada);
        }
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
    if(nuevo->estado == true && nuevo->palabraBuscada != "NULL")
    {
        reemplazadas->addWord(nuevo->palabraBuscada,nuevo->palabraReemplazada);
    }
    else
    {
        if(nuevo->palabraBuscada!= "NULL")
        {
            buscadas->addWord(nuevo->palabraBuscada, nuevo->palabraReemplazada);
        }
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
