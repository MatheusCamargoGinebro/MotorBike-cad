#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

/*-------------------------------</> Structs </>-------------------------------*/

// Estrutura de data:
typedef struct
{
    int day;
    int month;
    int year;
} date;

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
} dados;

// Estrutura de node:
typedef struct NODE
{
    dados moto;

    struct NODE *proximo;
} node;

// Estrutura de lista:
typedef struct
{
    node *inicio;

    node *fim;

    int cont;
} list;

/*-------------------------------</> Functions </>-------------------------------*/
void formater(node *stringer)
{
    int checker[5];
    for (int I = 0; I < 5; I++)
    {
        checker[I] = 0;
    }
    for (int I = 0; I < 2048; I++)
    {
        if (checker[0] == 0 && (stringer->moto.fabricante[I] == '\n' || I == 127))
        {
            stringer->moto.fabricante[I] = '\0';
            checker[0] = 1;
        }
        if (checker[1] == 0 && (stringer->moto.modelo[I] == '\n' || I == 127))
        {
            stringer->moto.modelo[I] = '\0';
            checker[1] = 1;
        }
        if (checker[2] == 0 && (stringer->moto.cor[I] == '\n' || I == 63))
        {
            stringer->moto.cor[I] = '\0';
            checker[2] = 1;
        }
        if (checker[3] == 0 && (stringer->moto.dono[I] == '\n' || I == 127))
        {
            stringer->moto.dono[I] = '\0';
            checker[3] = 1;
        }
        if (checker[4] == 0 && (stringer->moto.problema[I] == '\n' || I == 2047))
        {
            stringer->moto.problema[I] = '\0';
            checker[4] = 1;
        }

        if (checker[0] == 1 && checker[1] == 1 && checker[2] == 1 && checker[3] == 1 && checker[4] == 1)
        {
            break;
        }
    }
}

//+-====-----===-----====-+ Funções de exibição +-====-----===-----====-+/
// Função para limpar a tela:
void proxtela()
{
    printf("\n");
    system("pause");
    system("cls");
}

// Função para mostrar apenas 1 moto:
void printBikeDetails(node *bike)
{
    printf("O====================================================================O\n\n");
    printf(" Informações técnicas:\n");
    printf("  Número de cadastro da moto: %d.\n", bike->moto.cadNum);
    printf("  Fabricante da moto: %s.\n", bike->moto.fabricante);
    printf("  Modelo da moto: %s.\n", bike->moto.modelo);
    printf("  Ano de fabricação da moto: %d", bike->moto.ano);
    printf("  Cilindradas da moto: %.1f.\n", bike->moto.cilindrada);
    printf("  Cor da moto: %s.\n\n", bike->moto.cor);

    printf(" Mais detalhes:\n");
    printf("  Nome do dono da moto: %s.\n", bike->moto.dono);
    printf("  Problema que a moto apresentou: %s.\n\n", bike->moto.problema);
    printf("  Data em que a moto entrou na oficina: %d/%d/%d.\n\n", bike->moto.data.day, bike->moto.data.month, bike->moto.data.year);
    printf("O====================================================================O\n\n");
}

// Função para imprimir uma lista inteira de motos:
void printList(list *lista)
{
    for (node *I = lista->inicio; I != NULL; I = I->proximo)
    {
        printBikeDetails(I);
    }
}

//+-====-----===-----====-+ Funções de modificação de lista +-====-----===-----====-+/

// Função para criar uma lista dinâmicamente:
list *CreateList()
{

    // Tentando declarar uma lista dinâmicamente:
    list *lista = (list *)malloc(sizeof(list));

    // Testando se a lista foi realmente criada:
    if (lista == NULL)
    { // Houve erro.
        printf("Erro: problema no alocamento da memória para a lista.\n");
        exit(1);
    }
    else
    { // Não houve erro! :D
        // Definindo a lista como vazia.
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->cont = 0;
        return lista;
    }
}

// Função para limpar a lista:
void ClearList(list *lista)
{
    node *bike;

    while (lista->inicio != NULL)
    {
        // Pegar o primeiro elemento da lista:
        bike = lista->inicio;

        // O próximo elemento da lista se torna o primeiro.
        lista->inicio = bike->proximo;

        // Tirando da memória.
        free(bike);
    }
    free(lista);
}

// Função para adicionar uma mono à lista:
void addBike(list *lista, node *bike)
{
    // Alocar um espaço na memória para a nova moto cadastrada.
    node *newBike = (node *)malloc(sizeof(node));

    // Verificar se houve algum erro ao alocar a memória:
    if (newBike == NULL)
    {
        printf("Erro ao alocar memória para a nova moto.\n");
        proxtela();
        exit(1);
    }
    else
    {
        // Inserindo a nova moto no inicio da lista.
        newBike = bike;
        newBike->proximo = lista->inicio;

        // Testando se o elemento adicionado é o primeiro (lista vazia):
        if (lista->inicio == NULL)
        { // Sendo uma lista vazia, o primeiro elemento deve também ser o último.
            lista->fim = newBike;
        }

        lista->inicio = newBike;
        lista->cont++;
    }
}

// Função para encontrar e modificar motos em uma lista:
int modelFinder(list *lista, char bikeToFind[], node *biketoEdit, int mode)
{
    int verif = 0;

    for (node *I = lista->inicio; I != NULL; I = I->proximo)
    {
        if (strcmp(I->moto.modelo, bikeToFind) == 0)
        {
            if (mode == 1)
            {
                biketoEdit->moto = I->moto;
            }
            else
            {
                I->moto = biketoEdit->moto;
            }
            verif = 1;
        }
    }

    return verif;
}

int main()
{
    setlocale(LC_ALL, "portuguese");

    // Declarando a lista de motos:
    list *bikeList = CreateList();

    // Variável de resposta.
    int rUser, verif;

    do
    {
        printf("O================================================O\n| Programa de administração da oficina do seu zé |\nO================================================O\n|           [1] Listar todas as motos.           |\n|           [2] Cadastrar nova moto.             |\n|           [3] Buscar por modelo.               |\n|           [4] Sair do programa.                |\nO================================================O\n\nR: ");

        scanf("%d", &rUser);

        switch (rUser)
        {
        case 1:
            system("cls");
            printf("O==========================================O\n| Você escolheu [1] Listar todas as motos. |\nO==========================================O\n\n");

            if (bikeList->inicio == NULL)
            {
                printf("Ainda não há motos na lista, portanto, não há nada para mostrar.\n");
            }
            else
            {
                printList(bikeList);
            }

            break;

        case 2:
            system("cls");
            printf("O========================================O\n| Você escolheu [2] Cadastrar nova moto. |\nO========================================O\n");

            node *newbike = (node *)malloc(sizeof(node));

            printf("\nDigite o nome da fabricante da moto.\nR: ");
            setbuf(stdin, NULL);
            fgets(newbike->moto.fabricante, 128, stdin);

            printf("\nDigite o modelo da moto.\nR: ");
            setbuf(stdin, NULL);
            fgets(newbike->moto.modelo, 128, stdin);

            printf("\nDigite a cor da sua moto.\nR: ");
            setbuf(stdin, NULL);
            fgets(newbike->moto.cor, 64, stdin);

            printf("\nDigite o nome do dono da moto.\nR: ");
            setbuf(stdin, NULL);
            fgets(newbike->moto.dono, 128, stdin);

            printf("\nDigite o problema que a moto deu.\nR: ");
            setbuf(stdin, NULL);
            fgets(newbike->moto.problema, 2048, stdin);

            formater(newbike);

            printf("\nDigite o número de cadastro da moto.\nR: ");
            scanf("%d", &newbike->moto.cadNum);

            printf("\nDigite quantas cilindradas a moto tem.\nR: ");
            scanf("%f", &newbike->moto.cilindrada);

            printf("\nDigite o dia em que a moto foi entregue na oficina.\nR: ");
            scanf("%d", &newbike->moto.data.day);

            printf("\nDigite o mês em que a moto foi entregue na oficina.\nR: ");
            scanf("%d", &newbike->moto.data.month);

            printf("\nDigite o ano em que a moto foi entregue na oficina.\nR: ");
            scanf("%d", &newbike->moto.data.year);

            addBike(bikeList, newbike);
            break;

        case 3:
            system("cls");
            printf("O======================================O\n| Você escolheu [3] Buscar por modelo. |\nO======================================O\n");

            node *bikeEditor = (node *)malloc(sizeof(node));
            char modelToFind[128];
            printf("Digite o modelo da moto que você quer encontrar na oficina.\nR: ");
            setbuf(stdin, NULL);
            fgets(modelToFind, 128, stdin);

            for (int I = 0; I < 128; I++)
            {
                if (modelToFind[I] == '\n' || I == 127)
                {
                    modelToFind[I] = '\0';
                    break;
                }
            }

            if (modelFinder(bikeList, modelToFind, bikeEditor, 1) == 1)
            {
                printf("\nMoto encontrada.\n");
                char rDecision;

                do
                {
                    proxtela();
                    printf("Deseja editar as informações da moto? [Y/N]\nR: ");
                    scanf("%c", &rDecision);

                    if (rDecision == 'Y' || rDecision == 'y' || rDecision == 'S' || rDecision == 's')
                    {
                        verif = 1;
                    }
                    else if (rDecision == 'N' || rDecision == 'n')
                    {
                        verif = -1;
                    }
                    else
                    {
                        printf("Opção inválida. escolha entre [Y/N].\n");
                        verif = 0;
                    }
                } while (verif == 0);

                if (verif == 1)
                {
                    int rUser2;

                    do
                    {
                        printf("O=====================================O\n");
                        printf("|     Escolha o que deseja editar.    |\n");
                        printf("O=====================================O\t Informações atuais da moto: \n");
                        printf("|   [1] Número de cadastro.           |\t  Número de cadastro da moto: %d.\n", bikeEditor->moto.cadNum);
                        printf("|   [2] Fabricante.                   |\t  Fabricante da moto: %s.\n", bikeEditor->moto.fabricante);
                        printf("|   [3] Modelo.                       |\t  Modelo da moto: %s.\n", bikeEditor->moto.modelo);
                        printf("|   [4] Cilindradas.                  |\t  Cilindradas da moto: %.1f.\n", bikeEditor->moto.cilindrada);
                        printf("|   [5] Cor.                          |\t  Cor da moto: %s.\n", bikeEditor->moto.cor);
                        printf("|   [6] Data de entrega na oficina.   |\t  Data em que a moto entrou na oficina: %d/%d/%d.\n", bikeEditor->moto.data.day, bikeEditor->moto.data.month, bikeEditor->moto.data.year);
                        printf("|   [7] Ano.                          |\t  Ano de fabricação da moto: %d", bikeEditor->moto.ano);
                        printf("|   [8] Nome do dono.                 |\t  Nome do dono da moto: %s.\n", bikeEditor->moto.dono);
                        printf("|   [9] Problemas apresentados.       |\t  Problema que a moto apresentou: %s.\n", bikeEditor->moto.problema);
                        printf("|   [10] Sair da edição.              |\t\n");
                        printf("O=====================================O\n\nR: ");

                        scanf("%d", &rUser2);

                        switch (rUser2)
                        {
                        case 1:
                            printf("\nDigite um novo número de cadastro.\nR: ");
                            scanf("%d", &bikeEditor->moto.cadNum);
                            break;

                        case 2:
                            printf("\nDigite uma nova fabricante.\nR: ");
                            setbuf(stdin, NULL);
                            fgets(bikeEditor->moto.fabricante, 128, stdin);

                            for (int I = 0; I < 128; I++)
                            {
                                if (bikeEditor->moto.fabricante[I] == '\n' || I == 127)
                                {
                                    bikeEditor->moto.fabricante[I] = '\0';
                                    break;
                                }
                            }
                            break;

                        case 3:
                            printf("\nDigite o novo modelo da moto.\nR: ");
                            setbuf(stdin, NULL);
                            fgets(bikeEditor->moto.modelo, 128, stdin);

                            for (int I = 0; I < 128; I++)
                            {
                                if (bikeEditor->moto.modelo[I] == '\n' || I == 127)
                                {
                                    bikeEditor->moto.modelo[I] = '\0';
                                    break;
                                }
                            }
                            break;

                        case 4:
                            printf("Digite a nova quantidade de cilindradas da moto.\nR: ");
                            scanf("%f", &bikeEditor->moto.cilindrada);
                            break;

                        case 5:
                            printf("Digite a nova cor da moto.\nR: ");
                            setbuf(stdin, NULL);
                            fgets(bikeEditor->moto.cor, 64, stdin);

                            for (int I = 0; I < 64; I++)
                            {
                                if (bikeEditor->moto.cor[I] == '\n' || I == 63)
                                {
                                    bikeEditor->moto.cor[I] = '\0';
                                    break;
                                }
                            }
                            break;

                        case 6:
                            printf("Digite o novo dia em que a moto foi entregue na oficina.\nR: ");
                            scanf("%d", bikeEditor->moto.data.day);

                            printf("Digite o novo mês em que a moto foi entregue na oficina.\nR: ");
                            scanf("%d", bikeEditor->moto.data.month);

                            printf("Digite o novo amp em que a moto foi entregue na oficina.\nR: ");
                            scanf("%d", bikeEditor->moto.data.year);
                            break;

                        case 7:
                            printf("Digite o novo ano da moto.\nR: ");
                            scanf("%d", bikeEditor->moto.ano);
                            break;

                        case 8:
                            printf("Digite o novo nome do dono da moto.\nR: ");
                            setbuf(stdin, NULL);
                            fgets(bikeEditor->moto.dono, 128, stdin);

                            for (int I = 0; I < 128; I++)
                            {
                                if (bikeEditor->moto.dono[I] == '\n' || I == 127)
                                {
                                    bikeEditor->moto.dono[I] = '\0';
                                    break;
                                }
                            }
                            break;

                        case 9:
                            printf("Digite o novo problema da moto.\nR: ");
                            setbuf(stdin, NULL);
                            fgets(bikeEditor->moto.problema, 2048, stdin);

                            for (int I = 0; I < 2048; I++)
                            {
                                if (bikeEditor->moto.problema[I] == '\n' || I == 2047)
                                {
                                    bikeEditor->moto.problema[I] = '\0';
                                    break;
                                }
                            }
                            break;

                        case 10:
                            printf("\nVocê escolheu parar de editar. as informações modificadas serão salvas.\n");
                            break;

                        default:
                            printf("\nOpção inválida. tente algo entre 9 e 10.\n");
                            break;
                        }
                        proxtela();
                    } while (rUser != 10);

                    modelFinder(bikeList, modelToFind, bikeEditor, 2);
                }

                proxtela();
            }
            else
            {
                printf("\nMoto não encontrada.\n");
            }

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
    } while (rUser != 4);

    return 0;
}