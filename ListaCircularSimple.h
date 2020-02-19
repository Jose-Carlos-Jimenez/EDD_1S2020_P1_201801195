#include <string.h>
#include <iostream>
#include <fstream>

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
    void graph();
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

void ListaCircularSimple::graph()
{
    string grafo = "digraph A{node[fontname =Arial];";
    Ruta *nd = this->first->siguiente;
    int cont = 0;
    while(nd != first || cont == 0)
    {
        grafo+= "n" + to_string(cont) + " [label=\""+nd->nombre+"\\lRuta: " + nd->ruta + "\\l\"]\n";
        cont++;
        nd = nd->siguiente;
    }
    int cont2 = 0;

    while (cont2  < cont)
    {
        grafo+="n"+to_string(cont2)+" -> ";
        cont2++;
    }
    grafo+=" n0}";
    fstream archivo;
    archivo.open("C:/Users/jose5/listaCircular.dot", ios::out);
    archivo << grafo;
    archivo.close();
    system("dot.exe  -Tpng C:/Users/jose5/listaCircular.dot -o C:/Users/jose5/listaCircular.png");
    system("start C:/Users/jose5/listaCircular.png");
}

#endif // LISTACIRCULARSIMPLE_H
