#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#include "prioridade.h"

char menu(void)
{
    printf("1 - Inicializar\n");
    printf("2 - Inserir elemento \n");
    printf("3 - Remover elemento\n");
    printf("4 - Elemento do inicio\n");
    printf("5 - Elemento do fim\n");
    printf("6 - Exibe\n");
    return toupper(getch());
}

int main(void)
{
    char op;
    fila f;
    elemento elem;
    do
    {
        op = menu();
        switch (op)
        {
        case '1':
            inicializa(f);
            break;
        case '2':
            printf("Digite o elemento que deseja inserir \n");
            scanf(" %c", &elem.info);
            while(elem.info != '0')
            {
                printf("Digite a prioridade: [1] - Alta [2] - Media [3] - Baixa\n");
                scanf("%d", &elem.prioridade);
                while(elem.prioridade > 3 || elem.prioridade < 1)
                {
                    printf("Prioridade fora do range permitido, digite novamente! [1] - Alta [2] - Media [3] \n");
                    scanf("%d", &elem.prioridade);
                }
                if(!filacheia(f.fim))
                {
                    inserir(f, elem);
                    printf("Elemento inserido \n");
                    printf("Digite o elemento que deseja inserir \n");
                    scanf(" %c", &elem.info);
                }
                else
                {
                    printf("Fila cheia \n");
                    elem.info = ' ';
                } 
            }
            break;
        case '3':
            elemento removido;
            if(!filavazia(f.fim))
            {
                removido = remover(f);
                printf("Elemento %c removido, prioridade %d \n", removido.info, removido.prioridade);
            }
            else
                printf("Fila vazia\n");
            
            break;
        case '4':
            elemento inicio;
            if(!filavazia(f.fim)){
                inicio = elementoinicio(f);
                printf("Elemento do inicio %c, prioridade: %d\n", inicio.info, inicio.prioridade);
            }
            else
                printf("Fila vazia! \n");
            
            break;
        case '5':
            elemento fim;
            if(!filavazia(f.fim))
            {
                fim = elementofim(f);
                printf("Elemento do inicio %c, prioridade: %d\n", fim.info, fim.prioridade);
            }
            else
                printf("Fila vazia! \n");
            
            break;
        case '6':
            exibir(f);
            break;
            
            
            
        default:
            break;
        }
    } while (op != 27);
    
    return 0;
}