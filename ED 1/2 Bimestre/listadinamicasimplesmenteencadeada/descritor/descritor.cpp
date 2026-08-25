#include <stdio.h>
#include <conio2.h>
#include <ctype.h>

struct Tpno
{
    char id;
    Tpno *prox;
};

struct Tpdesc
{
    Tpno *inicio, *fim; //Pode-se ter mais ponteiros e mais variaveis
    int qtde;
};

void inicializar(Tpdesc &desc)
{
    desc.inicio = desc.fim = NULL;
    desc.qtde = 0;
}

void InsOrdenado(Tpdesc &d) //descritor vai no lugar do cabeca de lista
{
    Tpno *novo;
    char elemento;
    elemento = getche();
    while(elemento != 27)
    {
        novo = new Tpno;
        novo->id = elemento;
        novo->prox = NULL;
        if(d.qtde == 0)
            d.inicio = d.fim = novo; //Primeira insercao (1)

        else if(novo->id <= d.inicio->id) //Insercao no inicio, ja com elementos (2)
        {
            novo->prox = d.inicio;
            d.inicio = novo;
        }
        else if(novo->id >= d.fim->id) //Insere no final (3)
        {
            d.fim->prox = novo;
            d.fim = novo;
        }
        else
        {
            Tpno *andador = d.inicio->prox, *ant = d.inicio;
            while(andador->prox != NULL && novo->id >= andador->id)
            {
                ant = andador;
                andador = andador->prox;
            }
            novo->prox = andador;
            ant->prox = novo;
        }
        d.qtde++;
        elemento = getche();
    }
}






int main(void)
{

    return 0;
}