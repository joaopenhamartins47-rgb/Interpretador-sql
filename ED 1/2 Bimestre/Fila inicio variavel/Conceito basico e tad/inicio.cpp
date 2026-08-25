#include <stdio.h>
#include <conio2.h>
#include <ctype.h>
#include "filainiciovariavel.h"
char menu(void)
{
    printf("1 - Inserir elemento\n");
    printf("2 - Remover elemento\n");
    printf("3 - Elemento do inicio\n");
    printf("4 - Elemento do fim\n");
    printf("5 - Exibir fila com inicio variavel\n");
    return toupper(getch());
}

int main(void)
{
    char op, elem;
    Tpfila f;
    inicializa(f);
    do
    {
        op = menu();
        switch (op)
        {
        case '1':
            if(!cheio(f.inicio, f.fim))
            {
                printf("Digite o elemento que deseja inserir! (char)\n");
                scanf("%c", &elem);
                getchar();
                inserir(f, elem);
            }
            else
                printf("Fila cheia \n");
            break;
        case '2':
            if(!vazio(f.inicio, f.fim)){
                elem = remover(f);
                printf("elemento %c removido! \n", elem);
            }
            else
                printf("Fila vazia! \n");
            break;

        case '3':
            if(!vazio(f.inicio, f.fim))
            {
                elem = elementoinicio(f);
                printf("O elemento do inico eh: %c\n", elem);
            }
            else
                printf("Fila vazia! \n");
            break;

        case '4':
            if(!vazio(f.inicio, f.fim))
            {
                elem = elementofim(f);
                printf("O elemento do fim eh: %c\n", elem);
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
    } while (op != 27);
    

    return 0;
}