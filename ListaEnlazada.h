#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <string>
#include <iostream>

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
        cout << pointer->buscada;
        pointer = pointer->next;
    }
}

#endif // LISTAENLAZADA_H
