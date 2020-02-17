#include <string>
#include <iostream>
#include <ListaEnlazada.h>

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
        ListaEnlazada *words;

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
};

ListaDoblementeEnlazada::ListaDoblementeEnlazada()
{
    this->words = new ListaEnlazada();
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

void ListaDoblementeEnlazada::splitWords()
{
    Nodo *nd = first->next;
    string aux;
    while(nd != last)
    {
        if(nd->letter != ' ')
        {
            aux += nd->letter;
        }
        else
        {
            words->addWord(aux);
            aux = "";
        }
        nd = nd->next;
    }
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

#endif // LISTADOBLEMENTEENLAZADA_H
