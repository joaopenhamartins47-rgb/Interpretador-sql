#include <stdio.h>
#include <ctype.h>
#include <conio2.h>

#include "tadprioridade.h"

char menu(void)
{
    char op;
    printf("1 - Inserir elemento\n");
    printf("2 - Remover elemento\n");
    printf("3 - Elemento do inicio\n");
    printf("4 - Elemento do fim\n");
    printf("5 - Exibir fila circular com prioridade\n");
    scanf(" %c", &op);
    return op;
}

void limpa_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void)
{
    char op;
    elemento elem;
    Tppriori f;
    inicializa(f);
    do
    {
        op = menu();
        switch (op)
        {
        case '1':
            if(!cheio(f.qtde))
            {
                printf("Digite o elemento que deseja inserir! (char) e a prioridade\n");
                scanf(" %c", &elem.info);
                printf("Digite a prioridade: \n");
                scanf("%d", &elem.priori);
                limpa_buffer();
                inserir(f, elem);
            }
            else
                printf("Fila cheia \n");
            break;
        case '2':
            if(!vazio(f.qtde)){
                elemento removido = retirar(f);
                printf("Elemento %c, prioridade %d removido!\n", removido.info, removido.priori);
            }
            else
                printf("Fila vazia! \n");
            break;

        case '3':
            if(!vazio(f.qtde))
            {
                elem = elementoinicio(f);
                printf("O elemento do inico eh: %c, prioridade: %d\n", elem.info, elem.priori);
            }
            else
                printf("Fila vazia! \n");
            break;

        case '4':
            if(!vazio(f.qtde))
            {
                elem = elementofim(f);
                printf("O elemento do fim eh: %c e a prioridade eh: %d\n", elem.info, elem.priori);
            }
            else
                printf("Fila vazia! \n");
            break;
        
        case '5':
            exibir(f);
            break;
                
        
        default:
            break;
        }
    } while (op != '0');
    

    return 0;
}