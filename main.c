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

    //Variável de resposta.
    int rUser;

    do
    {
        printf("O================================================O\n");
        printf("| Programa de administração da oficina do seu zé |\n");
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
                printf("| Você escolheu [1] Listar todas as motos. |\n");
                printf("O==========================================O");


            break;

            case 2:
                printf("O========================================O\n");
                printf("| Você escolheu [2] Cadastrar nova moto. |\n");
                printf("O========================================O\n");
                
            break;

            case 3:
                printf("O======================================O\n");
                printf("| Você escolheu [3] Buscar por modelo. |\n");
                printf("O======================================O\n");             
                
            break;

            case 4:
                printf("O=====================================O\n");
                printf("| Você escolheu [4] Sair do programa. |\n");
                printf("O=====================================O\n");
                
            break;
            
            default:
                printf("\n\nOpção inválida, escolha entre 1 e 4.");
                
            break;
        }
    
        proxtela();
    } while (rUser!=4);
    


    return 0;
}