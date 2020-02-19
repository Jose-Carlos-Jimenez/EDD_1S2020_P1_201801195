#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Word{
    public:
    string buscada;
    string reemplazada;
    int pos;
    Word *next;
};


class ListaEnlazada{

public:
    Word* first;
    int size;
    ListaEnlazada();
    ~ListaEnlazada();
    void addWord(string, string);
    void print();
    void printInvert();
    void graph();
    void graphOther();
};


ListaEnlazada::ListaEnlazada()
{
    first = NULL;
    size = 0;
}

ListaEnlazada::~ListaEnlazada()
{

}

void ListaEnlazada::addWord(string newWord, string replacedWord)
{
    Word *nuevaPalabra = new Word();
    nuevaPalabra->buscada = newWord;
    nuevaPalabra->reemplazada = replacedWord;
    nuevaPalabra->pos = size;


    if(first ==  NULL)
    {
        first = nuevaPalabra;
    }
    else
    {
        if(newWord[0] < first->buscada[0])
        {
            nuevaPalabra->next = first;
            first = nuevaPalabra;
        }
        else
        {
            Word *reco = first;
            Word *back = first;
            while(newWord[0] >= reco->buscada[0] && reco->next != NULL)
            {
                back = reco;
                reco = reco->next;
            }
            if(newWord[0] >= reco->buscada[0])
            {
                reco->next = nuevaPalabra;
            }
            else
            {
                nuevaPalabra->next = reco;
                back->next = nuevaPalabra;
            }
        }
    }
    size++;
}

void ListaEnlazada::print()
{
    Word *pointer = this->first;
    while (pointer != NULL)
    {
        cout << pointer->buscada + " -> ";
        pointer = pointer->next;
    }
}

void ListaEnlazada::printInvert()
{
    Word *pointer = this->first;
    while (pointer != NULL)
    {
        cout << pointer->reemplazada+ " -> ";
        pointer = pointer->next;
    }
}

void ListaEnlazada::graph()
{
    string grafo = "digraph A{rankdir=LR node[shape=box3d fontname =Arial];\n";
    Word *nd = this->first;
    int cont = 0;
    while(nd != NULL)
    {
        grafo+= "n" + to_string(cont) + "[label=\"" + nd->buscada+"\\lReemplazada por: "+nd->reemplazada + "\\l\"]\n";
        cont++;
        nd = nd->next;
    }
    int cont2 = 0;

    while (cont2  < cont)
    {
        if(cont - 1 != cont2)
        {
            grafo+="n"+to_string(cont2)+" -> ";
        }
        else
        {
            grafo+="n"+to_string(cont2)+"\n}";
        }
        cont2++;
    }
    fstream archivo;
    archivo.open("C:/Users/jose5/listaSimple.dot", ios::out);
    archivo << grafo;
    archivo.close();
    system("dot.exe  -Tpng C:/Users/jose5/listaSimple.dot -o C:/Users/jose5/listaSimple.png");
    system("start C:/Users/jose5/listaSimple.png");
}

void ListaEnlazada::graphOther()
{
    string grafo = "digraph A{rankdir=LR node[shape=box3d fontname =Arial];\n";
    Word *nd = this->first;
    int cont = 0;
    while(nd != NULL)
    {
        if(nd->buscada != "NULL")
        {
            grafo+= "n" + to_string(cont) + "[label=\"" + nd->reemplazada+"\\lReemplazo a: "+nd->buscada+ "\\l\"]\n";
            cont++;
            nd = nd->next;
        }
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
            grafo+="n"+to_string(cont - cont2 -1)+"\n}";
        }
        cont2++;
    }
    fstream archivo;
    archivo.open("C:/Users/jose5/listaSimple.dot", ios::out);
    archivo << grafo;
    archivo.close();
    system("dot.exe  -Tpng C:/Users/jose5/listaSimple.dot -o C:/Users/jose5/listaSimple.png");
    system("start C:/Users/jose5/listaSimple.png");
}

#endif // LISTAENLAZADA_H
