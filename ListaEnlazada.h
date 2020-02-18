#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <string>

using namespace std;

class Word{
    public:
    string word;
    int pos;
    Word *next;
};


class ListaEnlazada{

public:
    Word* first;
    Word* last;
    int size;
    ListaEnlazada();
    ~ListaEnlazada();
    void addWord(string newWord);
};


ListaEnlazada::ListaEnlazada()
{
    first = last = NULL;
    size = 0;
}

ListaEnlazada::~ListaEnlazada()
{
    this->first->next = last;
}

void ListaEnlazada::addWord(string newWord)
{
    Word *nuevaPalabra = new Word();
    nuevaPalabra->word = newWord;
    nuevaPalabra->pos = size;


    if(size == 0)
    {
        first->next = nuevaPalabra;
        nuevaPalabra->next = last;
    }
    else
    {
        Word *aux = first->next;
        while(aux->word[0] > newWord[0])
        {
            aux = aux->next;
        }
        Word *refGuardada = aux->next;
        aux->next = nuevaPalabra;
        nuevaPalabra->next = refGuardada;
    }
}

#endif // LISTAENLAZADA_H
