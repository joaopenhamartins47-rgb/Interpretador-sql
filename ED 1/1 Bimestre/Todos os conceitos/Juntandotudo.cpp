#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#include "pilha.h"
#include "fila.h"



//Pilha: Verificar se a quantidade de parenteses ta certa dada um arquivo texto
//Fila: Prioridade de atendimento num hospital
//Um arquivo pra pilha e outro arquivo pra fila

char menu(void)
{
    printf("1 - Inserir na pilha \n");
    printf("2 - Inserir na fila \n");
    printf("3 - Exibir pilha \n");
    printf("4 - Exibir fila \n");
    printf("5 - Remover elemento qualquer na pilha \n");
    printf("6 - Remover elemento qualquer na fila \n");
    printf("7 - Parenteses \n");
    printf("8 - Prioridade no hospital \n");
    return toupper(getche());
}

void inserirpilha(Tppilha &p)
{
    
    char elem;
    printf("Digite o elemento que deseja inserir (0 para sair)! \n");
    scanf(" %c", &elem);
    while(elem != '0')
    {
        if(!pilhacheia(p.topo))
            PUSH(p, elem);
        else
            printf("Fila cheia! \n");
        printf("Digite o elemento que deseja inserir (0 para sair)! \n");
        scanf(" %c", &elem);
    }
}

void inserirfila(Tpfila &f)
{
    int prioridade;
    atendimento dados;
    printf("Digite o elemento que deseja inserir (0 para sair)! \n");
    fflush(stdin);
    gets(dados.nome);
    
    while(strcmp(dados.nome, "\0") != 0)
    {
        printf("Digite a prioridade: \n");
        scanf("%d", &dados.priori);
        
        if(!filacheia(f.fim))
            inserir(f, dados);
        else
            printf("Fila cheia! \n");
        printf("Digite o elemento que deseja inserir (0 para sair)! \n");
        fflush(stdin);
        gets(dados.nome);
    }
}

int acharelem(Tppilha p, char elem)
{
    while(!pilhavazia(p.topo) && p.pilha[p.topo] != elem)
        POP(p);

    if(!pilhavazia(p.topo))
        return 1;
    else
        return 0;
}

void removerpilha(Tppilha &p)
{
    char elem;
    Tppilha aux;
    inicializapilha(aux);
    printf("Digite o elemento que deseja remover! \n");
    scanf(" %c", &elem);
    int op = acharelem(p, elem);
    if(op)
    {
        while(!pilhavazia(p.topo))
        {
            if(!pilhacheia(aux.topo) && p.pilha[p.topo] != elem)
                PUSH(aux, POP(p));
            else
                POP(p);
        }
        while(!pilhavazia(aux.topo))
            PUSH(p, POP(aux));

        printf("Elemento removido! \n");  
    }
    else
        printf("Elemento nao encontrado! \n");
}

int acharfila(Tpfila f, char elem[30])
{
    int achou = 0;
    atendimento aux; 

    while(!filavazia(f.fim) && !achou)
    {
        aux = remover(f);
        if(strcmp(aux.nome, elem) == 0)
            achou = 1;
    }
    if(achou)
        return 1;
    else
        return 0;
}
void removerfila(Tpfila &f)
{
    char elem[30];
    printf("Digite o elemento que deseja remover! \n");
    Tpfila aux;
    inicializafila(aux);
    fflush(stdin);
    gets(elem);
    if(acharfila(f, elem))
    {
        while(strcmp(f.fila[0].nome, elem) != 0)
            inserir(aux, remover(f));

        remover(f);
        while(!filavazia(aux.fim))
            inserir(f, remover(aux));

        printf("Elemento removido com sucesso! \n");
    }
    else
        printf("Elemento nao encontrado! \n");
}


void parenteses(Tppilha &p)
{
    FILE *Ptrarq = fopen("parenteses.txt", "r");
    char expresso[50];
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        fscanf(Ptrarq, "%s", &expresso);
        while(!feof(Ptrarq))
        {
            inicializapilha(p);
            int valid = 1;
            for(int i = 0; expresso[i] != '\0'; i++)
            {
                if(expresso[i] == '(')
                    PUSH(p, '(');
                else if(expresso[i] == ')')
                {
                    if(pilhavazia(p.topo))
                        valid = 0;
                    else
                        POP(p);
                }
            }
            if(!pilhavazia(p.topo))
                valid = 0;
            if(valid)
                printf("Expressao correta! \n");
            else
                printf("Expressao incorreta! \n");
            fscanf(Ptrarq, "%s", &expresso);
        }
        fclose(Ptrarq);
    }
}

 

void simulacao(Tpfila &f)
{
    FILE *Ptrarq = fopen("hospital.txt", "r");
    atendimento aux, atend;
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        fscanf(Ptrarq, "%[^,], %d", atend.nome, &atend.priori);
        while(!feof(Ptrarq))
        {
            inserir(f, atend);
            fscanf(Ptrarq, "%[^,], %d", atend.nome, &atend.priori);
        }
        printf("Inseriu");
        int ocupado = 0;
        int terminou;
        for(int ut = 0; !(filavazia(f.fim) && !ocupado); ut++)
        {
            if(!ocupado)
            {
                aux = remover(f);
                ocupado = 1;
                if(aux.priori == 1)
                    aux.tempo = 2;
                else if(aux.priori == 2)
                    aux.tempo = 4;
                else if(aux.priori == 3)
                    aux.tempo = 10;
                aux.temporestante = aux.tempo;
                aux.chegada = ut;
                printf("Paciente sendo atendido %s\n", aux.nome);
            }
            aux.temporestante--;
            if(aux.temporestante == 0)
            {
                ocupado = 0;
                printf("Paciente %s atendido!, Prioridade %d\n", aux.nome, aux.priori);
                printf("Tempo de %d\n", ut - aux.chegada);
            }
            
            printf("%d\n", ut);
            Sleep(500);
        }
        fclose(Ptrarq);
    }
}



int main(void)
{
    //Ler um arquivo texto, utilizar pilha pra um problema e fila pra outra e no final exibir
    Tppilha p;
    Tpfila f;

    char op;
    inicializapilha(p);
    inicializafila(f);
    do
    {
        op = menu();
        switch (op)
        {
        case '1':
            clrscr();
            inserirpilha(p); 
            clrscr(); 
            break;

        case '2':
            clrscr();
            inserirfila(f);
            clrscr();
            break;
        
        case '3':
            clrscr();
            exibe(p);
            getch();
            clrscr();
            
            break;
        
        case '4':
            clrscr();
            exibefila(f);
            getch();
            clrscr();
            break;

        case '5':
            clrscr();
            removerpilha(p);
            getch();
            break;

        case '6':
            clrscr();
            removerfila(f);
            getch();
            break;

        case '7':
            clrscr();
            parenteses(p);
            getch();
            break;
        case '8':
        	clrscr();
            simulacao(f);
            break;
        default:
            break;
        }
        
    } while (op != '27');
    
    return 0;
}
