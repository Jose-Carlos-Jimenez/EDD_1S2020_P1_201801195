#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <string>

using namespace std;

class Word{
    public:
    string word;
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
    this->first = new Word();
    size = 0;
}

ListaEnlazada::~ListaEnlazada()
{
    this->first->next = last;
}

void ListaEnlazada::addWord(string newWord)
{
    Word *nd = new Word();
    nd->word = newWord;
    if(size == 0)
    {
        first->next = nd;
    }
    else
    {
        Word *pointer = first;
        while(pointer->next != last)
        {
            pointer = pointer->next;
        }
        pointer->next = nd;
        nd->next = last;
    }
    size++;
}

#endif // LISTAENLAZADA_H
