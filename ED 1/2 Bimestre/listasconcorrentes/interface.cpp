#include <stdio.h>
#include <conio2.h>
#include <ctype.h>
#include "tadpilhasmultiplas.h"
char menu(void)
{
    printf("1 - Inserir elemento\n");
    printf("2 - Remover elemento\n");
    printf("3 - Exibir pilhas multiplas\n");
    return toupper(getch());
}

int main(void)
{
    char op, elem;
    int np;
    Tppilham p;
    inicializa(p);
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
                    printf("Fila cheia \n");
                break;
            case 2:
                if(!cheia(p.topo1, p.topo2))
                {
                    printf("Digite o elemento que deseja inserir! (char)\n");
                    scanf(" %c", &elem);
                    PUSH(p, elem, np);
                }
                else
                    printf("Fila cheia \n");
                break;
            default:
                break;
            }
        break;
            
        case '2':
            printf("Em qual pilha deseja remover? [1 ou 2] \n");
            scanf("%d", &np);
            switch (np)
            {
            case 1:
                /* code */
                if(!vazia(p.topo1, np))
                {
                    elem = POP(p, np);
                    printf("elemento %c removido! \n", elem);
                }
                else
                    printf("Fila vazia! \n");
                break;
            case 2:
                if(!vazia(p.topo2, np))
                {
                    elem = POP(p, np);
                    printf("elemento %c removido! \n", elem);
                }
                else
                    printf("Fila vazia! \n");
                break;
            default:
                break;
            }
            
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
        
    } while (op != 27);
    
    return 0;
}