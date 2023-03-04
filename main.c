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
}list;



/*-------------------------------</> Functions </>-------------------------------*/
void proxtela(){
    printf("\n\n");
    system("pause");
    system("cls");
}


// Fun��es de modifica��o de lista.

// Fun��o para criar uma lista din�micamente:
list *CreateList(){
    
    // Tentando declarar uma lista din�micamente:
    list *lista = (list *)malloc(sizeof(list));

    // Testando se a lista foi realmente criada:
    if(lista == NULL)
    { // Houve erro.
        printf("Erro: problema no alocamento da mem�ria para a lista.\n");
        exit(1);
    }else
    { // N�o houve erro! :D
        // Definindo a lista como vazia.
        lista->inicio == NULL;
        lista->fim == NULL;

        return lista;
    }
}

// Fun��o para limpar a lista:
void ClearList(list *lista){
    node *bike;

    while(lista->inicio != NULL)
    {
        // Pegar o primeiro elemento da lista:
        bike = lista->inicio;

        // O pr�ximo elemento da lista se torna o primeiro.
        lista->inicio= bike->proximo;

        // Tirando da mem�ria.
        free(bike);
    }
    free(lista);
}

int main()
{
    setlocale(LC_ALL, "portuguese");

    // Declarando a lista de motos:
    list *bikeList = CreateList();

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
                system("cls");
                printf("O==========================================O\n");
                printf("| Voc� escolheu [1] Listar todas as motos. |\n");
                printf("O==========================================O");


            break;

            case 2:
                system("cls");
                printf("O========================================O\n");
                printf("| Voc� escolheu [2] Cadastrar nova moto. |\n");
                printf("O========================================O\n");
                
            break;

            case 3:
                system("cls");
                printf("O======================================O\n");
                printf("| Voc� escolheu [3] Buscar por modelo. |\n");
                printf("O======================================O\n");             
                
            break;

            case 4:
                printf("\nVoc� escolheu sair do programa.\n\nlimpando a lista.\n\n");

                ClearList(bikeList);

                printf("Lista limpa.");
                
            break;
            
            default:
                printf("\nOp��o inv�lida, escolha entre 1 e 4.");
            break;
        }
    
        proxtela();
    } while (rUser!=4);

    return 0;
}