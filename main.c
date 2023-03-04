#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

/*-------------------------------</> Structs </>-------------------------------*/

// Estrutura de data:
typedef struct
{
    int day;
    int month;
    int year;
}date;


// Estrutura de dados:
typedef struct
{
    int cadNum;
    int fabricante;
    int modelo;
    float cilindrada;
    char Dono[128];
    char problema[2048];
    date data;
}dados;


// Estrutura de node:
typedef struct NODE
{
    dados moto;

    struct NODE *proximo;
}node;


// Estrutura de lista:
typedef struct
{
    node *inicio;

    node *fim;
    
    int cont;
}list;


int main()
{
    setlocale(LC_ALL, "portuguese");
    


    return 0;
}
