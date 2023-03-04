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

//+-====-----===-----====-+ Funções de modificação de lista +-====-----===-----====-+/

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
        lista->inicio = NULL;
        lista->fim = NULL;

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

//+-====-----===-----====-+ Funções de exibição +-====-----===-----====-+/
// Função para limpar a tela:
void proxtela(){
    printf("\n\n");
    system("pause");
    system("cls");
}


// Função para mostrar apenas 1 moto:
void printBikeDetails(node *bike){
    printf("O========================================----------------------\n");
    printf("Bike Info:\n");
    printf("Número de cadastro da moto: %d.\n", bike->moto.cadNum);
    printf("Fabricante da moto: %s.\n", bike->moto.fabricante);
    printf("Modelo da moto: %s.\n", bike->moto.modelo);
    printf("Cilindradas da moto: %.2f.\n", bike->moto.cilindrada);
    printf("Cor da moto: %s.\n\n", bike->moto.cor);

    printf("More details:\n");
    printf("Nome do dono da moto: %s.\n", bike->moto.dono);
    printf("Problema que a moto apresentou: %s.\n\n", bike->moto.problema);
    printf("Data em que a moto entrou na oficina: %d/%d/%d.\n\n",  bike->moto.data.day, bike->moto.data.month, bike->moto.data.year);
}


// Função para imprimir uma lista inteira de motos:
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
                printf("O==========================================O\n| Você escolheu [1] Listar todas as motos. |\nO==========================================O\n\n");

                if(bikeList->inicio==NULL){
                    printf("Ainda não há motos na lista, portanto, não há nada para mostrar.");
                }else{
                    printList(bikeList);
                }

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