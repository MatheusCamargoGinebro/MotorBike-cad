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


//+-====-----===-----====-+ Fun��es de exibi��o +-====-----===-----====-+/
// Fun��o para limpar a tela:
void proxtela()
{
    printf("\n");
    system("pause");
    system("cls");
}

// Fun��o para mostrar apenas 1 moto:
void printBikeDetails(node *bike)
{
    printf("O====================================================================O\n\n");
    printf(" Informa��es t�cnicas:\n");
    printf("  N�mero de cadastro da moto: %d.\n", bike->moto.cadNum);
    printf("  Fabricante da moto: %s.\n", bike->moto.fabricante);
    printf("  Modelo da moto: %s.\n", bike->moto.modelo);
    printf("  Ano de fabrica��o da moto: %d", bike->moto.ano);
    printf("  Cilindradas da moto: %.1f.\n", bike->moto.cilindrada);
    printf("  Cor da moto: %s.\n\n", bike->moto.cor);

    printf(" Mais detalhes:\n");
    printf("  Nome do dono da moto: %s.\n", bike->moto.dono);
    printf("  Problema que a moto apresentou: %s.\n\n", bike->moto.problema);
    printf("  Data em que a moto entrou na oficina: %d/%d/%d.\n\n", bike->moto.data.day, bike->moto.data.month, bike->moto.data.year);
    printf("O====================================================================O\n\n");
}

// Fun��o para imprimir uma lista inteira de motos:
void printList(list *lista)
{
    for (node *I = lista->inicio; I != NULL; I = I->proximo)
    {
        printBikeDetails(I);
    }
}

//+-====-----===-----====-+ Fun��es de modifica��o de lista +-====-----===-----====-+/

// Fun��o para criar uma lista din�micamente:
list *CreateList()
{

    // Tentando declarar uma lista din�micamente:
    list *lista = (list *)malloc(sizeof(list));

    // Testando se a lista foi realmente criada:
    if (lista == NULL)
    { // Houve erro.
        printf("Erro: problema no alocamento da mem�ria para a lista.\n");
        exit(1);
    }
    else
    { // N�o houve erro! :D
        // Definindo a lista como vazia.
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->cont = 0;
        return lista;
    }
}

// Fun��o para limpar a lista:
void ClearList(list *lista)
{
    node *bike;

    while (lista->inicio != NULL)
    {
        // Pegar o primeiro elemento da lista:
        bike = lista->inicio;

        // O pr�ximo elemento da lista se torna o primeiro.
        lista->inicio = bike->proximo;

        // Tirando da mem�ria.
        free(bike);
    }
    free(lista);
}

// Fun��o para adicionar uma mono � lista:
void addBike(list *lista, node *bike)
{
    // Alocar um espa�o na mem�ria para a nova moto cadastrada.
    node *newBike = (node *)malloc(sizeof(node));

    // Verificar se houve algum erro ao alocar a mem�ria:
    if (newBike == NULL)
    {
        printf("Erro ao alocar mem�ria para a nova moto.\n");
        proxtela();
        exit(1);
    }
    else
    {
        // Inserindo a nova moto no inicio da lista.
        newBike = bike;
        newBike->proximo = lista->inicio;

        // Testando se o elemento adicionado � o primeiro (lista vazia):
        if (lista->inicio == NULL)
        { // Sendo uma lista vazia, o primeiro elemento deve tamb�m ser o �ltimo.
            lista->fim = newBike;
        }

        lista->inicio = newBike;
        lista->cont++;
    }
}

// Fun��o para encontrar e modificar motos em uma lista:
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
            else if (mode == 2)
            {
                I->moto = biketoEdit->moto;
            }
            verif = 1;
            break;
        }
    }

    return verif;
}

int main()
{
    setlocale(LC_ALL, "portuguese");

    // Declarando a lista de motos:
    list *bikeList = CreateList();

    // Vari�vel de resposta.
    int rUser, verif;

    do
    {
        printf("O================================================O\n| Programa de administra��o da oficina do seu z� |\nO================================================O\n|           [1] Listar todas as motos.           |\n|           [2] Cadastrar nova moto.             |\n|           [3] Buscar por modelo.               |\n|           [4] Sair do programa.                |\nO================================================O\n\nR: ");

        scanf("%d", &rUser);

        switch (rUser)
        {
        case 1:
            system("cls");
            printf("O==========================================O\n| Voc� escolheu [1] Listar todas as motos. |\nO==========================================O\n\n");

            if (bikeList->inicio == NULL)
            {
                printf("Ainda n�o h� motos na lista, portanto, n�o h� nada para mostrar.\n");
            }
            else
            {
                printList(bikeList);
            }

            break;

        case 2:
            system("cls");
            printf("O========================================O\n| Voc� escolheu [2] Cadastrar nova moto. |\nO========================================O\n");

            node *newbike = (node *)malloc(sizeof(node));

            printf("\nDigite o nome da fabricante da moto.\nR: ");
            setbuf(stdin, NULL);
            fgets(newbike->moto.fabricante, 128, stdin);

            for (int I = 0; I < 128; I++)
            {
                if (newbike->moto.fabricante[I] == '\n' || I == 127)
                {
                    newbike->moto.fabricante[I] = '\0';
                    break;
                }
            }

            do
            {
                verif = 0;
                printf("\nDigite o modelo da moto.\nR: ");
                setbuf(stdin, NULL);
                fgets(newbike->moto.modelo, 128, stdin);

                for (int I = 0; I < 128; I++)
                {
                    if (newbike->moto.modelo[I] == '\n' || I == 127)
                    {
                        newbike->moto.modelo[I] = '\0';
                        break;
                    }
                }

                if (modelFinder(bikeList, newbike->moto.modelo, newbike, 0) == 1)
                {
                    printf("\nModelo j� cadastrado. Escolha outro modelo.\n");
                    verif = 1;
                }
            } while (verif);

            printf("\nDigite a cor da sua moto.\nR: ");
            setbuf(stdin, NULL);
            fgets(newbike->moto.cor, 64, stdin);

            for (int I = 0; I < 64; I++)
            {
                if (newbike->moto.cor[I] == '\n' || I == 64)
                {
                    newbike->moto.cor[I] = '\0';
                    break;
                }
            }

            printf("\nDigite o nome do dono da moto.\nR: ");
            setbuf(stdin, NULL);
            fgets(newbike->moto.dono, 128, stdin);

            for (int I = 0; I < 128; I++)
            {
                if (newbike->moto.dono[I] == '\n' || I == 127)
                {
                    newbike->moto.dono[I] = '\0';
                    break;
                }
            }

            printf("\nDigite o problema que a moto deu.\nR: ");
            setbuf(stdin, NULL);
            fgets(newbike->moto.problema, 2048, stdin);

            for (int I = 0; I < 2048; I++)
            {
                if (newbike->moto.problema[I] == '\n' || I == 2048)
                {
                    newbike->moto.problema[I] = '\0';
                    break;
                }
            }

            printf("\nDigite o ano da moto.\nR: ");
            scanf("%d", &newbike->moto.ano);

            printf("\nDigite o n�mero de cadastro da moto.\nR: ");
            scanf("%d", &newbike->moto.cadNum);

            printf("\nDigite quantas cilindradas a moto tem.\nR: ");
            scanf("%f", &newbike->moto.cilindrada);

            printf("\nDigite o dia em que a moto foi entregue na oficina.\nR: ");
            scanf("%d", &newbike->moto.data.day);

            printf("\nDigite o m�s em que a moto foi entregue na oficina.\nR: ");
            scanf("%d", &newbike->moto.data.month);

            printf("\nDigite o ano em que a moto foi entregue na oficina.\nR: ");
            scanf("%d", &newbike->moto.data.year);

            addBike(bikeList, newbike);
            break;

        case 3:
            system("cls");
            printf("O======================================O\n| Voc� escolheu [3] Buscar por modelo. |\nO======================================O\n");

            node *bikeEditor = (node *)malloc(sizeof(node));
            char modelToFind[128];
            printf("Digite o modelo da moto que voc� quer encontrar na oficina.\nR: ");
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
                printf("\nMoto encontrada:\n\n");
                printBikeDetails(bikeEditor);
                char rDecision;

                do
                {
                    printf("\nDeseja editar as informa��es da moto? [Y/N].\nR: ");
                    setbuf(stdin, NULL);
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
                        printf("\nOp��o inv�lida. escolha entre [Y/N].\n");
                        verif = 0;
                    }
                } while (verif == 0);


                if (verif == 1)
                {
                    int rUser2;

                    do
                    {
                        system("cls");
                        printf("O=====================================O\n|     Escolha o que deseja editar.    |\nO=====================================O\t -Informa��es atuais da moto: \n|   [1] N�mero de cadastro.           |\t   N�mero de cadastro da moto: %d.\n|   [2] Fabricante.                   |\t   Fabricante da moto: %s.\n|   [3] Modelo.                       |\t   Modelo da moto: %s.\n|   [4] Cilindradas.                  |\t   Cilindradas da moto: %.1f.\n|   [5] Cor.                          |\t   Cor da moto: %s.\n|   [6] Data de entrega na oficina.   |\t   Data em que a moto entrou na oficina: %d/%d/%d.\n|   [7] Ano.                          |\t   Ano de fabrica��o da moto: %d\n|   [8] Nome do dono.                 |\t   Nome do dono da moto: %s.\n|   [9] Problemas apresentados.       |\t   Problema que a moto apresentou: %s.\n|   [10] Sair da edi��o.              |\t\nO=====================================O\n\nR: ", bikeEditor->moto.cadNum, bikeEditor->moto.fabricante, bikeEditor->moto.modelo, bikeEditor->moto.cilindrada, bikeEditor->moto.cor, bikeEditor->moto.data.day, bikeEditor->moto.data.month, bikeEditor->moto.data.year, bikeEditor->moto.ano, bikeEditor->moto.dono, bikeEditor->moto.problema);

                        scanf("%d", &rUser2);

                        switch (rUser2)
                        {
                        case 1:
                            printf("\nDigite um novo n�mero de cadastro.\nR: ");
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
                            do
                            {
                                verif=0;
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
                                for (node *I = bikeList->inicio; I != NULL; I = I->proximo)
                                {
                                    if (strcmp(bikeEditor->moto.modelo, I->moto.modelo) == 0)
                                    {
                                        printf("\nModelo j� cadastrado. Escolha outro modelo.\n");
                                        verif=1;
                                    }
                                }
                            } while (verif);

                            break;

                        case 4:
                            printf("\nDigite a nova quantidade de cilindradas da moto.\nR: ");
                            scanf("%f", &bikeEditor->moto.cilindrada);
                            break;

                        case 5:
                            printf("\nDigite a nova cor da moto.\nR: ");
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
                            printf("\nDigite o novo dia em que a moto foi entregue na oficina.\nR: ");
                            scanf("%d", &bikeEditor->moto.data.day);

                            printf("\nDigite o novo m�s em que a moto foi entregue na oficina.\nR: ");
                            scanf("%d", &bikeEditor->moto.data.month);

                            printf("\nDigite o novo amp em que a moto foi entregue na oficina.\nR: ");
                            scanf("%d", &bikeEditor->moto.data.year);
                            break;

                        case 7:
                            printf("\nDigite o novo ano da moto.\nR: ");
                            scanf("%d", &bikeEditor->moto.ano);
                            break;

                        case 8:
                            printf("\nDigite o novo nome do dono da moto.\nR: ");
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
                            printf("\nDigite o novo problema da moto.\nR: ");
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
                            printf("\nVoc� escolheu parar de editar. as informa��es modificadas ser�o salvas.\n");
                            proxtela();
                            break;

                        default:
                            printf("\nOp��o inv�lida. tente algo entre 9 e 10.\n");
                            proxtela();
                            break;
                        }
                    } while (rUser2 != 10);

                    modelFinder(bikeList, modelToFind, bikeEditor, 2);
                }
            }
            else
            {
                printf("\nMoto n�o encontrada.\n");
            }

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
    } while (rUser != 4);

    return 0;
}