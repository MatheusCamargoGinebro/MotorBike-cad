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



/*-------------------------------</> Functions </>-------------------------------*/
void proxtela(){
    printf("\n\n");
    system("pause");
    system("cls");
}

int main()
{
    setlocale(LC_ALL, "portuguese");

    //Vari�vel de resposta.
    int rUser;

    do
    {
        printf("O================================================O\n");
        printf("| Programa de administra��o da oficina do seu z� |\n");
        printf("O================================================O\n");
        printf("|           [1] Listar todas as motos.           |\n");
        printf("|           [2] Cadastrar nova moto.             |\n");
        printf("|           [3] Buscar por modelo.               |\n");
        printf("|           [4] Sair do programa.                |\n");
        printf("O================================================O\n\nR: ");
    
        scanf("%d", &rUser);

        switch (rUser){
            case 1:
                printf("O==========================================O\n");
                printf("| Voc� escolheu [1] Listar todas as motos. |\n");
                printf("O==========================================O");


            break;

            case 2:
                printf("O========================================O\n");
                printf("| Voc� escolheu [2] Cadastrar nova moto. |\n");
                printf("O========================================O\n");
                
            break;

            case 3:
                printf("O======================================O\n");
                printf("| Voc� escolheu [3] Buscar por modelo. |\n");
                printf("O======================================O\n");             
                
            break;

            case 4:
                printf("O=====================================O\n");
                printf("| Voc� escolheu [4] Sair do programa. |\n");
                printf("O=====================================O\n");
                
            break;
            
            default:
                printf("\n\nOp��o inv�lida, escolha entre 1 e 4.");
                
            break;
        }
    
        proxtela();
    } while (rUser!=4);
    


    return 0;
}