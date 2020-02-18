#include <string.h>
#include <iostream>

using namespace std;

#ifndef LISTACIRCULARSIMPLE_H
#define LISTACIRCULARSIMPLE_H

class Ruta
{
public:
    string nombre;
    string ruta;
    Ruta *siguiente;
};

class ListaCircularSimple
{
public:
    Ruta *first;
    Ruta *last;
    int size;
    ListaCircularSimple();
    void add(string,string);
};

ListaCircularSimple::ListaCircularSimple()
{
    first = last = NULL;
    size = -1;
}
void ListaCircularSimple::add(string ruta, string nombre)
{
    Ruta *nuevo = new Ruta();
    nuevo->ruta = ruta;
    nuevo->nombre = nombre;
    if(last)
    {
        last->siguiente = nuevo;
        last = nuevo;
        last->siguiente = first;
    }
    else
    {
        first = new Ruta();
        first->siguiente = nuevo;
        last = nuevo;
        last->siguiente = first;
    }
    size++;
}

#endif // LISTACIRCULARSIMPLE_H
