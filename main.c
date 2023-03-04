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
    char fabricante[128];
    char modelo[128];
    float cilindrada;
    char cor[64];
    date data;
    int ano;
    char dono[128];
    char problema[2048];
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

//+-====-----===-----====-+ Fun��es de modifica��o de lista +-====-----===-----====-+/

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
        lista->inicio = NULL;
        lista->fim = NULL;

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

//+-====-----===-----====-+ Fun��es de exibi��o +-====-----===-----====-+/
// Fun��o para limpar a tela:
void proxtela(){
    printf("\n\n");
    system("pause");
    system("cls");
}


// Fun��o para mostrar apenas 1 moto:
void printBikeDetails(node *bike){
    printf("O========================================----------------------\n");
    printf("Bike Info:\n");
    printf("N�mero de cadastro da moto: %d.\n", bike->moto.cadNum);
    printf("Fabricante da moto: %s.\n", bike->moto.fabricante);
    printf("Modelo da moto: %s.\n", bike->moto.modelo);
    printf("Cilindradas da moto: %.2f.\n", bike->moto.cilindrada);
    printf("Cor da moto: %s.\n\n", bike->moto.cor);

    printf("More details:\n");
    printf("Nome do dono da moto: %s.\n", bike->moto.dono);
    printf("Problema que a moto apresentou: %s.\n\n", bike->moto.problema);
    printf("Data em que a moto entrou na oficina: %d/%d/%d.\n\n",  bike->moto.data.day, bike->moto.data.month, bike->moto.data.year);
}


// Fun��o para imprimir uma lista inteira de motos:
void printList(list *lista)
{
    for(node *I = lista->inicio; I != NULL; I = I->proximo)
    {
        printBikeDetails(I);
    }
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
                printf("O==========================================O\n| Voc� escolheu [1] Listar todas as motos. |\nO==========================================O\n\n");

                if(bikeList->inicio==NULL){
                    printf("Ainda n�o h� motos na lista, portanto, n�o h� nada para mostrar.");
                }else{
                    printList(bikeList);
                }

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