#include <stdio.h>
#include <conio2.h>
#include <ctype.h>
#include <cstdlib>

char menu(void)
{
    system("cls");

    printf("========================================\n");
    printf("         LISTA ENCADEADA MENU\n");
    printf("========================================\n");
    printf("\n");

    printf("[A] Inserir no inicio\n");
    printf("[B] Contar elementos\n");
    printf("[C] Exibir recursivo inverso\n");
    printf("[D] Consultar indice\n");
    printf("[E] Concatenar listas\n");
    printf("[F] Excluir duplicatas\n");
    printf("[G] Inverter lista\n");
    printf("[ESC] Sair\n");

    printf("\n");
    printf("Opcao: ");

    return toupper(getche());
}


struct Tpno
{
    char id;
    Tpno *prox;
};

Tpno *criar_caixinha(char dado)
{
    Tpno *novo;
    novo = new Tpno;
    novo->id = dado;
    novo->prox = NULL;
    return novo;
}

//Inserir no inicio
Tpno *Inserir_no_inicio(Tpno *L)
{
    Tpno *novo = NULL;
    char elemento;
    elemento = getche();
    while(elemento != 27)
    {
        novo = criar_caixinha(elemento);
        if(L == NULL)
            L = novo;
        else
        {
            novo->prox = L;
            L = novo;
        }
        elemento = getche();
    }
    return L;
}

//Implemente int contar_elementos(Tpno *L) que retorna o número de nós na lista, iterativamente.
int contar_elementos(Tpno *L)
{
    int cont = 0;

    while(L != NULL)
    {
        cont++;
        L = L->prox;
    }

    return cont;
}

// Implemente void exibir_recursivo_inverso(Tpno *L) que exibe todos os elementos da lista na ordem inversa, usando recursão (sem criar lista auxiliar).
void exibir_recursivo(Tpno *L)
{
    if(L == NULL)
        return;
    else
    {
        exibir_recursivo(L->prox);
        printf("%c", L->id);
    }
}

//Modifique consulta para retornar a posição (índice começando em 0) do elemento encontrado em vez do ponteiro. Retorne -1 se não encontrado.
int consulta_indice(Tpno *L, char elemento)
{
    int indice = 0;
    int pos = -1;
    while(L != NULL && pos == -1)
    {
        if(L->id == elemento)
            pos = indice;

        indice++;
        L = L->prox;
    }

    return pos;
}

// Implemente Tpno *concatenar(Tpno *L1, Tpno *L2) que une L2 ao final de L1 e retorna o ponteiro para o início da lista resultante. Atenção: não crie nós novos.
Tpno *concatenar(Tpno *L1, Tpno *L2)
{
    if(L1 == NULL)
        return L2;
    if(L2 == NULL)
        return L1;
  
    Tpno *aux = L1;
    while(aux->prox != NULL) //Percorre a lista 1
        aux = aux->prox;
    aux->prox = L2;
    return L1;
}

// Implemente Tpno *excluir_duplicatas(Tpno *L) que percorre a lista e remove todos os nós com id repetido, mantendo apenas a primeira ocorrência.
Tpno *excluir_duplicatas(Tpno *L)
{
    if(L == NULL)
        return NULL;

    Tpno *aux = L;

    while(aux != NULL)
    {
        Tpno *p2 = aux;

        while(p2->prox != NULL)
        {
            if(aux->id == p2->prox->id)
            {
                Tpno *duplicata = p2->prox;
                p2->prox = duplicata->prox;
                delete duplicata;
            }
            else
                p2 = p2->prox;
        }
        aux = aux->prox;
    }
    return L;
}

Tpno *inverter_lista(Tpno *L)
{
    Tpno *anterior = NULL; // No início, não há ninguém antes do primeiro
    Tpno *atual = L;       // Começamos pelo início da lista
    Tpno *proximo = NULL;  // Ponteiro auxiliar para não perder a lista

    while (atual != NULL)
    {
        // 1. Salva o próximo endereço (o elo da frente)
        proximo = atual->prox;

        // 2. Inverte o sentido: o atual aponta para quem vinha antes
        atual->prox = anterior;

        // 3. Move os ponteiros uma casa para a frente
        anterior = atual;   // O atual vira o anterior da próxima iteração
        atual = proximo;    // O próximo vira o atual da próxima iteração
    }

    // No fim, 'anterior' estará apontando para o que era o último nó,
    // que agora é o novo início da lista.
    return anterior;
}


int main(void)
{
    Tpno *L1 = NULL;
    Tpno *L2 = NULL;

    char op;
    char elemento;

    do
    {
        op = menu();

        switch(op)
        {
            case 'A':
                printf("\n\nDigite os elementos da lista (ESC para parar): ");
                L1 = Inserir_no_inicio(L1);
                break;

            case 'B':
                printf("\n\nQuantidade de elementos: %d",
                       contar_elementos(L1));
                break;

            case 'C':
                printf("\n\nLista em ordem inversa: ");
                exibir_recursivo(L1);
                break;

            case 'D':
                printf("\n\nDigite o elemento para buscar: ");
                elemento = getche();

                printf("\nIndice: %d",
                       consulta_indice(L1, elemento));
                break;

            case 'E':
                printf("\n\nDigite os elementos da segunda lista (ESC para parar): ");
                L2 = Inserir_no_inicio(L2);

                L1 = concatenar(L1, L2);

                printf("\nListas concatenadas com sucesso!");
                break;

            case 'F':
                L1 = excluir_duplicatas(L1);

                printf("\n\nDuplicatas removidas!");
                break;

            case 'G':
                L1 = inverter_lista(L1);

                printf("\n\nLista invertida com sucesso!");
                break;

            case 'H':
                printf("\n\nEncerrando...");
                break;

            default:
                printf("\n\nOpcao invalida!");
        }

        if(op != 'H')
        {
            printf("\n\n");
            system("pause");
        }

    }while(op != 27);

    return 0;
}