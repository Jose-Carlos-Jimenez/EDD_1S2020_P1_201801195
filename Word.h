#ifndef WORD_H
#define WORD_H
#include <string>

using namespace std;


class Word{
public:
    string word;
    Word *next;
};

class ListaEnlazada{
    Word first;
    Word last;

public:
    ListaEnlazada();
    void addWord(string);
    vo
};

#endif // WORD_H
