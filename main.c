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


// Funções de modificação de lista.

// Função para criar uma lista dinâmicamente:
list *CreateList(){
    
    // Tentando declarar uma lista dinâmicamente:
    list *lista = (list *)malloc(sizeof(list));

    // Testando se a lista foi realmente criada:
    if(lista == NULL)
    { // Houve erro.
        printf("Erro: problema no alocamento da memória para a lista.\n");
        exit(1);
    }else
    { // Não houve erro! :D
        // Definindo a lista como vazia.
        lista->inicio == NULL;
        lista->fim == NULL;

        return lista;
    }
}

// Função para limpar a lista:
void ClearList(list *lista){
    node *bike;

    while(lista->inicio != NULL)
    {
        // Pegar o primeiro elemento da lista:
        bike = lista->inicio;

        // O próximo elemento da lista se torna o primeiro.
        lista->inicio= bike->proximo;

        // Tirando da memória.
        free(bike);
    }
    free(lista);
}

int main()
{
    setlocale(LC_ALL, "portuguese");

    // Declarando a lista de motos:
    list *bikeList = CreateList();

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
                system("cls");
                printf("O==========================================O\n");
                printf("| Você escolheu [1] Listar todas as motos. |\n");
                printf("O==========================================O");


            break;

            case 2:
                system("cls");
                printf("O========================================O\n");
                printf("| Você escolheu [2] Cadastrar nova moto. |\n");
                printf("O========================================O\n");
                
            break;

            case 3:
                system("cls");
                printf("O======================================O\n");
                printf("| Você escolheu [3] Buscar por modelo. |\n");
                printf("O======================================O\n");             
                
            break;

            case 4:
                printf("\nVocê escolheu sair do programa.\n\nlimpando a lista.\n\n");

                ClearList(bikeList);

                printf("Lista limpa.");
                
            break;
            
            default:
                printf("\nOpção inválida, escolha entre 1 e 4.");
            break;
        }
    
        proxtela();
    } while (rUser!=4);

    return 0;
}