#include <stdio.h>


#include "tadpilhasmultiplas.h"

char menu(void)
{
    char op;
    printf("1 - Inserir na pilha\n");
    printf("2 - Remover elemento desejado\n");
    printf("3 - Exibir pilhas\n");
    scanf(" %c", &op);
    return op;
}

void exclusao(Tppilham &p, char elem, int np)
{
    Tppilham aux;
    inicializa(aux);
    int achou = 0;
    if(np == 1)
    {
        while(!vazia(p.topo1, np) && p.pilha[p.topo1] != elem)
            PUSH(aux, POP(p, np), np);
        if(!vazia(p.topo1, np))
        {
            achou = 1;
            POP(p, np);
        }
            
        while(!vazia(aux.topo1, np))
            PUSH(p, POP(aux, np), np);
        if (achou)
            printf("Elemento excluido com sucesso!\n");
        else
            printf("Elemento nao encontrado! \n");
    }
    else
    {
        while(!vazia(p.topo2, np) && p.pilha[p.topo2] != elem)
            PUSH(aux, POP(p, np), np);
        if(!vazia(p.topo2, np))
        {
            achou = 1;
            POP(p, np);
        }
            
        while(!vazia(aux.topo2, np))
            PUSH(p, POP(aux, np), np);
        if (achou)
            printf("Elemento excluido com sucesso!\n");
        else
            printf("Elemento nao encontrado! \n");
    }
}

int main(void)
{
    Tppilham p;
    inicializa(p);
    int np;
    char elem, op;
    do
    {
        op = menu();
        switch (op)
        {
            case '1':
                printf("Em qual pilha deseja inserir? [1 ou 2] \n");
                scanf("%d", &np);
                switch (np)
                {
                case 1:
                    if(!cheia(p.topo1, p.topo2))
                    {
                        printf("Digite o elemento que deseja inserir! (char)\n");
                        scanf(" %c", &elem);
                        PUSH(p, elem, np);
                    }
                    else
                        printf("pilha cheia \n");
                    break;
                case 2:
                    if(!cheia(p.topo1, p.topo2))
                    {
                        printf("Digite o elemento que deseja inserir! (char)\n");
                        scanf(" %c", &elem);
                        PUSH(p, elem, np);
                    }
                    else
                        printf("pilha cheia \n");
                    break;
                default:
                    break;
                }
            break;
        
            case '2':
                printf("Digite qual elemento deseja excluir: \n");
                scanf(" %c", &elem);
                printf("Em qual pilha: [1 ou 2] \n");
                scanf("%d", &np);
                exclusao(p, elem, np);
            break;
        
            case '3':
                printf("Qual pilha deseja exibir? [1 ou 2] \n");
                scanf("%d", &np);
                switch (np)
                {
                case 1:
                    exibe(p, np);
                    break;
                case 2:
                    exibe(p, np);
                    break;
            
                default:
                    break;
                }
                break;

        }
    } while (op != '0');
    
    
    return 0;
}