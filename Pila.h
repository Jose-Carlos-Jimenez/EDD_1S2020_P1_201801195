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
    string getEstado();
    string getChar();
};

class Pila
{
public:

    ~Pila();
    ListaEnlazada *buscadas;
    Cambio *cima;
    Pila();
    int tamanio;
    void push(string, string, bool, char, int, int);
    void push(Cambio*);
    void emptyStack();
    Cambio* pop();
    void graph();
};

string Cambio::getEstado()
{
    if(estado)
    {
        return "Revertido";
    }
    return "No revertido";
}

string Cambio::getChar()
{
    if(palabra)
    {
        return  to_string(palabra);
    }
    return "<--NO-->";
}

Pila::Pila()
{
    buscadas= new ListaEnlazada();
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
        //reemplazadas->addWord(palabraBuscada,palabraReeemplazada);
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
        //reemplazadas->addWord(nuevo->palabraReemplazada,nuevo->palabraBuscada);
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

void Pila::graph()
{
    string grafo = "digraph A{node[shape=record fontname =Arial];\n";
    Cambio *nd = this->cima;
    int cont = 0;
    while(nd != NULL)
    {
        grafo+= "n" + to_string(cont) +
                "[label=\"Palabra buscada: "+nd->palabraBuscada
                +" \\lReemplazada por: "+nd->palabraReemplazada+
                +" \\lEstado: "+nd->getEstado()
                +" \\lPalabra: "+to_string(nd->palabra)+
                +" \\lPosicion: "+to_string(nd->posicion)
                +"\\l\"]\n";
        cont++;
        nd = nd->siguiente;
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
    archivo.open("C:/Users/jose5/pilaCambios.dot", ios::out);
    archivo << grafo;
    archivo.close();
    system("dot.exe  -Tpng C:/Users/jose5/pilaCambios.dot -o C:/Users/jose5/pilaCambios.png");
    system("start C:/Users/jose5/pilaCambios.png");
}

#endif // PILA_Hs
