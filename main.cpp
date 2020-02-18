#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <iostream>
#include <string>
#include <direct.h>

#include <ListaDoblementeEnlazada.h>
#include <Pila.h>

#define ARRIBA 9
#define IZQUIERDA 10
#define DERECHA 12
#define ABAJO 11
#define CANCELAR 24
#define BORRAR 8
#define BUSCAR 23
#define DESHACER 26
#define REHACER 25
#define GUARDAR 19

using namespace std;

void AltEnter()
{
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
    return;
}

void gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void paintRectangle()
{
    int i = 2;
    while(i<165)//Pintar filas
    {
        gotoxy(i, 1);printf("%c",205);
        gotoxy(i,44);printf("%c",205);
        i++;
    }
    i = 2;
    while(i<44)//Pintar columnas.
    {
        gotoxy(2, i);printf("%c",186);
        gotoxy(165, i);printf("%c",186);
        i++;
    }
    //Pintar esquinas
    gotoxy(2,1);printf("%c",201);
    gotoxy(165,1);printf("%c",187);
    gotoxy(2,44);printf("%c",200);
    gotoxy(165,44);printf("%c",188);
}

void printThanks()
{
    system("color C");
    fstream archive("msg.txt");
    string line;
    if(!archive.is_open())
    {
        archive.open("C:/Users/jose5/Documents/EDD/msg.txt", ios::in);
    }
    while (getline(archive, line))
    {
        cout << line << "\n";
    }
    archive.close();
}

bool outSystem( bool backToMenu)
{
    bool back = backToMenu;
    system("cls");
    paintRectangle();
    return back;
};

void returnChange(ListaDoblementeEnlazada* letters , Pila *changes, Pila *reverts)
{
    if(reverts->tamanio > 0)
    {
        Cambio *last = reverts->pop();
        last->estado = false;
        if(last!=NULL)
        {
            changes->push(last);
            int tipo = last->tipo;
            if(tipo == 1)
            {
                int pos = last->posicion;
                char palabra = last->palabra;
                letters->addAt(pos-1, palabra);
            }
            else if(tipo == 2)
            {
                int pos = last->posicion;
                letters->deleteAt(pos);
            }
            else if(tipo == 3)
            {
                letters->replace(last->palabraBuscada, last->palabraReemplazada);
            }
        }
    }
}

void revertChange(ListaDoblementeEnlazada* letters , Pila *changes, Pila *reverts)
{
    if(changes->tamanio > 0)
    {
        Cambio *last = changes->pop();
        last->estado = true;
        reverts->push(last);
        if(last!=NULL)
        {
            int tipo = last->tipo;
            if(tipo == 1)
            {
                int pos = last->posicion;
                letters->deleteAt(pos);
            }
            else if(tipo == 2)
            {
                int pos = last->posicion;
                char palabra = last->palabra;
                letters->addAt(pos-1, palabra);
            }
            else if(tipo == 3)
            {
                letters->replace(last->palabraReemplazada, last->palabraBuscada);
            }
        }
    }
}

void paintMenu()
{
    paintRectangle();
    gotoxy(3,3);printf("UNIVERSIDAD DE SAN CARLOS DE GUATEMALA");
    gotoxy(3,4);printf("FACULTAD DE INGENIERIA");
    gotoxy(3,5);printf("ESTRUCTURA DE DATOS");
    gotoxy(3,6);printf("PRACTICA 1");
    gotoxy(3,7);printf("Jose Carlos Jimenez");
    gotoxy(3,8);printf("201801195");
    gotoxy(3,14);printf("MENU");
    gotoxy(3,16);printf("1. Crear archivo.");
    gotoxy(3,17);printf("2. Abrir archivo.");
    gotoxy(3,18);printf("3. Archivos recientes.");
    gotoxy(3,19);printf("4. Salir.");
}

void imprimirEnPantalla(ListaDoblementeEnlazada *letters)
{
    system("cls");
    string text = letters->getText();
    int x = 0;
    int y = 0;

    for(int i = 0; i < letters->sizeElements; i++)
    {
        char c = text[i];
        gotoxy(x,y);
        printf("%c",c);
        if(x == 165)
        {
            x= 0;
            y++;
        }
        else
        {
            x++;
        }
    }
    for(int z = 0; z<y+8; z++)
    {
        gotoxy(166,z);
        printf("%c",186);
    }
    gotoxy(0,y+8);
    for( int i = 0; i<166;i++){
        printf("%c",205);
    }
    gotoxy(166,y+8);
    printf("%c",188);
    gotoxy(45,y+9);
    cout << "^w (Buscar y reemplazar)      ^c (Reportes)       ^s (Guardar)";
    gotoxy(x, y);
}

void printCoordinates(int x, int y)
{
    gotoxy(x,y);
    cout << "x: "<<x<<" y:"<<y;
}

int altura(int x, int y)
{
    int k = 0;
    if(y >= 0)
    {
        k = 166*(y) + x;
    }
    return k;
}

void partirCaracteres(ListaDoblementeEnlazada * letters)
{
    string letras = letters->getText();

}

void pintarBR(ListaDoblementeEnlazada *letters, Pila *changes)
{
    string remp;
    system("cls");
    cout<<"Ingrese la palabra a reemplazar y el reemplazo con el fomato: <PalabraBuscada>;<PalabraReemplazada>\n";
    cin>>remp;
    bool p1, p2;
    p1 = true;
    p2 = false;
    string palabra1;
    string palabra2;
    int size = remp.length();
    for(int i = 0; i < size  ; i++)
    {
        if( p1 == true && remp[i] != ';' )
        {
            palabra1 += remp[i];
        }
        else if( remp[i] == ';' )
        {
            p1 = false;
            p2 = true;
        }
        else if( p2 == true)
        {
            palabra2 += remp[i];
        }
    }
    changes->push(palabra1, palabra2,false,0,0,3);
    letters->replace(palabra1, palabra2);
    string numero = to_string(letters->cambios);
    cout<< "!SE HAN REEMPLAZADO "+ palabra1 +" POR "+ palabra2 +" "+ numero + " VECES!\n";
    system("pause");
    imprimirEnPantalla(letters);
}

/*void save(ListaDoblementeEnlazada *letters)
{
    system("cls");
    cout<<"Nombre del archivo :";
    string directory;
    getline(cin, directory);
    //__________________________________________________________________________

    ofstream archivo;
    archivo.open("C:/prueba.txt",ios::out);

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo.";
    }
    archivo << letters->getText();
    archivo.close();
    //__________________________________________________________________________
    cout << "SE HA FINALIZADO LA ESCRITURA DE ARCHIVOS";
    Sleep(1000);
    imprimirEnPantalla(letters);
}*/

void editArea(ListaDoblementeEnlazada* letters, Pila* changes, Pila* reverts)
{
    system("color F0");
    int x = 0; int y = 0;
    bool editando = true;

    //Hilo para movimiento
    while (editando){

        if(kbhit())
        {
            char c = getch();//CARACTER QUE ES PULSADO
            if ( c == BORRAR)
            {
                /*¡BOOORRRAR!*/
                if(letters->sizeElements > 0 && (x!=0 || y != 0))
                {
                    int posicion = 166*y+x;
                    char borrado = letters->getAt(posicion)->letter;
                    changes->push("NULL","NULL",false,borrado,posicion,2);
                    letters->deleteAt(x,y);
                }
                imprimirEnPantalla(letters);
                if(x==0 && y>0)
                {
                    x = 166;
                    y--;
                }
                else
                {
                    x--;
                }
                gotoxy(x,y);
            }
            else if( c == BUSCAR)/*BUSCAR Y REEMPLAZAR*/
            {
                pintarBR(letters, changes);
            }
            else if( c == REHACER )/*<----------------------REHACER LA ULTIMA ACCIÓN DESECHA---------------------------->*/
            {
                int tamanio = reverts->tamanio;
                if(tamanio > 0 && reverts->cima != NULL)
                {
                    int tipo = reverts->cima->tipo;

                    if(tipo == 1)
                    {
                        if( x == 165 )
                        {
                            x = 0;
                            y++;
                        }
                        else
                        {
                            x++;
                        }
                        gotoxy(x,y);
                    }
                    else if(tipo == 2)
                    {
                        if(x==0 && y>0)
                        {
                            x = 166;
                            y--;
                        }
                        else
                        {
                            x--;
                        }
                        gotoxy(x,y);
                    }
                    returnChange(letters,changes, reverts);
                    imprimirEnPantalla(letters);
                }
            }
            else if( c == DESHACER)/*<-----------------------DESHACER LA ULTIMA ACCIÓN---------------------------------->*/
            {
                if(changes->tamanio > 0 && letters->sizeElements > 0)
                {
                    int tipo = changes->cima->tipo;

                    if(tipo== 1)/*SI VOY A BORRAR DISMINUYO COORDENADS.*/
                    {
                        if(x==0 && y>0)
                        {
                            x = 166;
                            y--;
                        }
                        else
                        {
                            x--;
                        }
                        gotoxy(x,y);
                    }

                    else if( tipo == 2)/*SI VOY A AGREGAR AUMENTO COORDENADAS*/
                    {
                        if( x == 165 )
                        {
                            x = 0;
                            y++;
                        }
                        else
                        {
                            x++;
                        }
                        gotoxy(x,y);
                    }

                    revertChange(letters, changes, reverts);
                    imprimirEnPantalla(letters);
                }
            }
            else if ( c == CANCELAR )
            {
                /*SALIR AL MENÚ PRINCIPAL*/
                letters->first->next = letters->last;
                letters->last->prev = letters->first;
                letters->sizeElements = 0;
                changes->emptyStack()   ;
                reverts->emptyStack();
                system("color 5F");
                editando = false;
                system("cls");
                paintMenu();
            }
            else if ( c == ARRIBA)
            {
                if(y >0)
                {
                    y--;
                    gotoxy(x,y);
                }
            }
            else if( c == ABAJO)
            {
                if((166*(y+1) + x) < letters->sizeElements)
                {
                    y++;
                    gotoxy(x,y);
                }
            }
            else if( c == IZQUIERDA )
            {
                /*IZQUIERDA*/

                if(x == 0)
                {
                    if(y > 0)
                    {
                        y--;
                        x = 165;
                        gotoxy(x,y);
                    }
                    if(x == 0)
                    {
                        gotoxy(x,y);
                    }
                }
                else
                {
                    x--;
                    gotoxy(x,y);
                }
            }
            else if ( c == DERECHA)
            {
                /*DERECHA*/
                if(altura(x,y) < letters->sizeElements)
                {
                    if(x<165)
                    {
                        x++;gotoxy(x,y);
                    }
                    else
                    {
                        x=0;
                        y++;
                        gotoxy(x,y);
                    }
                }
            }
            else if(c == GUARDAR)
            {
                save(letters);
            }
            else/*AGREGAR CARACTERES*/
            {
                int pos = 166*y + x + 1;

                /*AGREGAR LOS CARACTERES NO DEFINIDOS*/
                if(letters->sizeElements ==0)
                {
                    letters->addLast(c);
                    changes->push("NULL", "NULL", false, c, pos, 1);
                    reverts->emptyStack();
                }
                else
                {
                    letters->addAt(x,y,c);
                    changes->push("NULL", "NULL", false, c, pos, 1);
                    reverts->emptyStack();
                }

                /*CONTROLADOR DE POSICION DEL PUNTERO*/
                if( x == 165 )
                {
                    x = 0;
                    y++;
                }
                else
                {
                    x++;
                }
                imprimirEnPantalla(letters);
                gotoxy(x,y);
            }
        }
    }
}

int main() {
    bool running = true;
    AltEnter();
    paintMenu();
    system("Color 5F");
    ListaDoblementeEnlazada letters = ListaDoblementeEnlazada();
    Pila changes = Pila();
    Pila reverts = Pila();

    while(running)
    {
         if(kbhit())
         {
             char c = getch();
             if(c == '1')
             {
                 system("cls");
                 imprimirEnPantalla(&letters);
                 editArea(&letters, &changes, &reverts);
             }
             else if(c == '2')
             {

             }
             else if(c == '3')
             {

             }
             else if(c == '4')
             {
                system("cls");
                printThanks();
                Sleep(1000);
                exit(0);
             }
             else
             {

             }
         }
         Sleep(50);
    }
    return 0;
}
