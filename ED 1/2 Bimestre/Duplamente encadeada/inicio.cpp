#include <stdio.h>
#include <conio2.h>
struct Tpno
{
    char info;
    Tpno *ant, *prox;
};

Tpno *criar_caixinha(char dado)
{
    Tpno *novo;
    novo = new Tpno;
    novo->info = dado;
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

Tpno *Inserir_ordenado(Tpno *L)
{
    char elemento;
    Tpno *novo;

    elemento = getche();

    while(elemento != 27)
    {
        novo = criar_caixinha(elemento);

        // CASO 1 -> lista vazia
        if(L == NULL)
        {
            L = novo;
        }
        else
        {
            // CASO 2 -> inserir no início
            if(elemento <= L->info)
            {
                novo->prox = L;
                L->ant = novo;
                L = novo;
            }
            else
            {
                Tpno *andador = L;

                // PARA NO PRIMEIRO MAIOR
                while(andador->prox != NULL && elemento > andador->info)
                    andador = andador->prox;
                

                // CASO 3 -> inserir no final
                if(andador->prox == NULL && elemento > andador->info)
                {
                    andador->prox = novo;
                    novo->ant = andador;
                }
                else
                {

                    novo->prox = andador;
                    novo->ant = andador->ant;

                    andador->ant->prox = novo;
                    andador->ant = novo;
                }
            }
        }

        elemento = getche();
    }

    return L;
}


int main(void)
{

    return 0;
}