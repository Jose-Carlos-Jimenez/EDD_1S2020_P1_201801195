#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <ListaDoblementeEnlazada.h>
#include <iostream>
#include <string>

#define ARRIBA 9
#define IZQUIERDA 10
#define DERECHA 12
#define ABAJO 11
#define SALIR 18
#define BORRAR 8

using namespace std;


/*INICIO DE LOS MÉTODOS DEL PROGRAMA */
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

void pintarBR(ListaDoblementeEnlazada *letters)
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
    letters->replace(palabra1, palabra2);
    string numero = to_string(letters->cambios);
    cout<< "!SE HAN REEMPLAZADO "+ palabra1 +" POR "+ palabra2 +" "+ numero + " VECES!\n";
    system("pause");
    imprimirEnPantalla(letters);
}

void editArea(ListaDoblementeEnlazada* letters)
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
                    letters->deleteAt(x,y);
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
            }
            else if( c == 23)
            {
                pintarBR(letters);
            }
            else if ( c == SALIR )
            {
                /*SALIR AL MENÚ PRINCIPAL*/
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
            else/*AGREGAR CARACTERES*/
            {
                /*AGREGAR LOS CARACTERES NO DEFINIDOS*/
                if(letters->sizeElements ==0)
                {
                    letters->addLast(c);
                }
                else
                {
                    letters->addAt(x,y,c);
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

    while(running)
    {
         if(kbhit())
         {
             char c = getch();
             if(c == '1')
             {
                 system("cls");
                 editArea(&letters);
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
