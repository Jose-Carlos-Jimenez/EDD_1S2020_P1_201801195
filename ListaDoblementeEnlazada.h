#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#ifndef LISTADOBLEMENTEENLAZADA_H
#define LISTADOBLEMENTEENLAZADA_H

class Nodo
{
    public:
        char letter;
        Nodo *next;
        Nodo *prev;
};

class ListaDoblementeEnlazada
{
    public:
        Nodo *first;
        Nodo *last;
        int cambios;
        int sizeElements;

        ListaDoblementeEnlazada();
        ~ListaDoblementeEnlazada();
        void addLast(char);
        void removeLast();
        string getText();
        Nodo* getAt(int);
        void addAt(int, int, char);
        void addAt(int,char);
        void deleteAt(int, int);
        void deleteAt(int);
        void splitWords();
        void replace(string , string );
        void refreshList(string);
        void graph();
};

ListaDoblementeEnlazada::ListaDoblementeEnlazada()
{
    sizeElements = 0;
    first = new Nodo();
    last = new Nodo();
    first->next = last;
    last->prev = first;
}

ListaDoblementeEnlazada::~ListaDoblementeEnlazada()
{
    while(first->next == last && last->prev == first)
    {
        removeLast();
    }
}

void ListaDoblementeEnlazada::addLast(char c)
{
    Nodo *nd = new Nodo();
    nd->letter = c;

    if(sizeElements > 0)
    {
        Nodo *aux3 = last->prev;
        aux3->next = nd;
        nd->next = last;
        last->prev = nd;
        nd->prev = aux3;

    }
    else
    {
        first->next = nd;
        nd->next = last;
        last->prev = nd;
        nd->prev = first;
    }
    sizeElements++;
}

void ListaDoblementeEnlazada::removeLast()
{
    if(sizeElements > 0)
    {
        Nodo *nd = last->prev->prev;
        nd->next = last;
        sizeElements--;
    }
}

string ListaDoblementeEnlazada::getText()
{
    string text;
    Nodo *nd = this->first->next;
    while(nd != last)
    {
        text += nd->letter;
        nd = nd->next;
    }
    return text;
}

Nodo* ListaDoblementeEnlazada::getAt(int pos)
{
    Nodo *nd = first;
    for(int i = 0; i < pos ; i++)
    {
        nd = nd->next;
    }
    return nd;
}

void ListaDoblementeEnlazada::addAt(int x, int y, char c)
{
    int pos = 166*y + x;
    Nodo *nd = getAt(pos);
    Nodo *nuevo = new Nodo();
    Nodo *siguiente = nd->next;

    nuevo->letter = c;//Añado el valor necesario.

    nd->next = nuevo;//nd->nuevo
    nuevo->next = siguiente;//nd->nuevo->siguiente
    siguiente->prev = nuevo;//nuevo<-siguiente
    nuevo->prev = nd;//nd<-nuevo<-prev
    sizeElements++;
}

void ListaDoblementeEnlazada::addAt(int pos, char c)
{
    Nodo *nd = getAt(pos);
    Nodo *nuevo = new Nodo();
    Nodo *siguiente = nd->next;

    nuevo->letter = c;//Añado el valor necesario.

    nd->next = nuevo;//nd->nuevo
    nuevo->next = siguiente;//nd->nuevo->siguiente
    siguiente->prev = nuevo;//nuevo<-siguiente
    nuevo->prev = nd;//nd<-nuevo<-prev
    sizeElements++;
}

void ListaDoblementeEnlazada::deleteAt(int x, int y)
{
    int pos = 166*y + x;
    Nodo *nd = getAt(pos);
    Nodo *ant = nd->prev;
    ant->next = nd->next;
    nd->next->prev = ant;
    sizeElements--;
    delete nd;
}

void ListaDoblementeEnlazada::deleteAt(int pos)
{
    Nodo *nd = getAt(pos);
    Nodo *ant = nd->prev;
    ant->next = nd->next;
    nd->next->prev = ant;
    sizeElements--;
    delete nd;
}

void ListaDoblementeEnlazada::replace(string buscada,string reemplazo)
{
    string texto = getText();
    int pos = texto.find(buscada);
    int countedWords = 0;
    while(pos != -1)
    {
        texto.replace(pos, buscada.size(), reemplazo);
        pos  = texto.find(buscada, pos + reemplazo.size());
        countedWords++;
    }
    cambios = countedWords;
    refreshList(texto);
}

void ListaDoblementeEnlazada::refreshList(string replaced)
{
    first->next = NULL;
    last->prev =  NULL;
    sizeElements = 0;
    for(int i = 0; i < int(replaced.size()); i++)
    {
        addLast(replaced[i]);
    }
}

void ListaDoblementeEnlazada::graph()
{
    string grafo = "digraph A{node[fontname =Arial];\n";
    Nodo *nd = this->first->next;
    int cont = 0;
    while(nd != last)
    {
        grafo+= "n" + to_string(cont) + "[label=\"" + nd->letter + "\"]\n";
        cont++;
        nd = nd->next;
    }
    int cont2 = 0;

    while (cont2  < cont)
    {
        if(cont - 1 != cont2)
        {
            grafo+="n"+to_string(cont - cont2 -1)+" -> ";
        }
        else
        {
            grafo+="n"+to_string(cont - cont2 -1)+"[dir=\"both\"]\n}";
        }
        cont2++;
    }
    fstream archivo;
    archivo.open("C:/Users/jose5/listaDoble.dot", ios::out);
    archivo << grafo;
    archivo.close();
    system("dot.exe  -Tpng C:/Users/jose5/listaDoble.dot -o C:/Users/jose5/grafo.png");
    system("start C:/Users/jose5/grafo.png");
}

#endif // LISTADOBLEMENTEENLAZADA_H
