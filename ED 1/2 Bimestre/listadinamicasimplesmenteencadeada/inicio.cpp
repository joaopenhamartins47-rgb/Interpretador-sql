#include <stdio.h>
#include <conio2.h>
#include "tadlista.h"

struct Tpno
{
    char id;
    Tpno *prox;
};

Tpno *NovoNo(char dado)
{
    Tpno *No;
    No = new Tpno;
    No->id = dado;
    No->prox = NULL;
    return No;
}

Tpno *InserirInicio(Tpno *L)
{
    Tpno *Novo;
    char elemento;
    printf("Inserir na lista\n");
    printf("Elemento: ");
    elemento = getche();
    while(elemento != 27)
    {
        Novo = NovoNo(elemento);
        if(L == NULL)
            L = Novo;
        else
        {
            Novo->prox = L;
            L = Novo;
        }
        elemento = getche();
    }
    return L;
}

void exibir(Tpno *L)
{
    if(L == NULL)
        printf("Lista vazia!\n");
    else
    {
        while(L != NULL)
        {
            printf("%c", L->id);
            L = L->prox;
        }
        getch();
    }
}

int main(void)
{
    Tpno *lista = NULL;
    
}