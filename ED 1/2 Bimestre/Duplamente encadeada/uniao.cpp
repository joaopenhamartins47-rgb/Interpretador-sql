#include <stdio.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>

char menu(void)
{
    printf("\n*** Uniao/Intersecao/Diferenca ***\n");
    printf("[A] - Uniao\n");
    printf("[B] - Intersecao\n");
    printf("[C] - Diferenca\n");
    printf("[D] - Inserir elementos nas listas\n");
    return toupper(getche());
}

struct Tpno
{
    int info;
    Tpno *ant, *prox;
};

Tpno *criar_caixinha(int dado)
{
    Tpno *novo;
    novo = new Tpno;
    novo->info = dado;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

Tpno *Insercao_ordenada(Tpno *L)
{
    int elemento;
    Tpno *novo;
    printf("Digite o elemento (0 para sair): \n");
    scanf("%d", &elemento);
    while(elemento != 0)
    {
        Tpno *andador = L;
        novo = criar_caixinha(elemento);
        if(L == NULL) //Insere o primeiro elemento (1)
            L = novo;
        else
        {
            while(andador->prox != NULL && elemento > andador->info)
                andador = andador->prox;
            
            if(elemento < L->info) //Insere no comeco (2)
            {
                L->ant = novo;
                novo->prox = L;
                L = novo;
            }
            else if(andador->prox == NULL && elemento > andador->info) //Insere no final (3)
            {
                andador->prox = novo;
                novo->ant = andador;
            }
            else //Insere entre 2 (4)
            {
                novo->prox = andador;
                novo->ant = andador->ant;
                if(andador->ant != NULL)
                    andador->ant->prox = novo;
                else
                    L = novo;
                andador->ant = novo;
            }
        }
        printf("Digite o elemento (0 para sair): \n");
        scanf("%d", &elemento);
    }
    return L;
}
//Forma nao ordenada
Tpno *uniao(Tpno *L1, Tpno *L2)
{
    Tpno *novo, *andador, *L3 = NULL, *verificador;
    if(L1 == NULL)
        return L2;
    if(L2 == NULL)
        return L1;
    while(!(L1 == NULL && L2 == NULL))
    {
        if(L1 != NULL)
        {
            if(L3 == NULL)
            {
                novo = criar_caixinha(L1->info);
                L1 = L1->prox;
                L3 = novo;
                andador = L3;
            }
            else
            {
                verificador = L3; //Para nao repetir
                novo = criar_caixinha(L1->info);
                while(verificador != NULL && novo->info != verificador->info)
                    verificador = verificador->prox;
                if(verificador == NULL) //Siginifica que eh diferente de todos, entao insere
                {
                    andador->prox = novo;
                    novo->ant = andador;
                    L1 = L1->prox;
                    andador = andador->prox;
                }
                else
                {
                    delete novo;
                    L1 = L1->prox;
                }
                    
            }   
        }
        else
        {
            verificador = L3;
            novo = criar_caixinha(L2->info);
            while(verificador != NULL && novo->info != verificador->info)
                verificador = verificador->prox;
            if(verificador == NULL)
            {
                andador->prox = novo;
                novo->ant = andador;
                L2 = L2->prox;
                andador = andador->prox;
            }
            else
            {
                delete novo;
                L2 = L2->prox;
            }
        }
    }
    return L3;
}


int main(void)
{
    return 0;
}
