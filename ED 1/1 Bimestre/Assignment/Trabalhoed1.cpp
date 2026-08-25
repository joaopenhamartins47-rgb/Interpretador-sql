#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>


#include "filatrab.h"

/*simule e exiba a execução de tarefas solicitadas a um “processador”. As tarefas que este pode executar são:

    Impressão à 3 ut;
    Gravação em dispositivo interno à 5 ut;
    Leitura à 4 ut;
    Gravação em dispositivo externo à 8 ut.

    Observacoes:

    Construir um arquivo texto com, no mínimo, 1000 registros de solicitações de tarefas;
    Definir, no início da simulação, a quantidade de processadores que serão utilizados;
    Ut = Unidades de tempo;
    A cada 4 ut uma tarefa é solicitada, mas esse tempo pode ser alterado durante a execução da simulação;

    As prioridades para execução das tarefas são:
    [1º] Gravação em dispositivo interno;
    [2º] Gravação em dispositivo externo;
    [3º] Leitura;
    [4º] Impressão.

    Desenvolver uma interface intuitiva e “amigável” para entendimento do que “está acontecendo”;
    As tarefas executadas, após o tempo determinado, deverão deixar a Fila;
    Qual o tempo médio que cada processador, em ut’s, dispende para atender uma      tarefa?
    Qual o tempo médio, que se leva, para atender cada tipo de tarefa?
    Quantos processos, cada processador executou?
*/

void geraraleatorio(void)
{
    int i, op;
    FILE *Ptrarq = fopen("tarefas.txt", "w");
    for(i = 0; i<1000; i++)
    {
        op = rand()%4+1;
        switch (op)
        {
        case 1:
            fprintf(Ptrarq, "G,1,5\n");
            break;
        case 2:
            fprintf(Ptrarq, "E,2,8\n");
            break;
        case 3:
            fprintf(Ptrarq, "L,3,4\n");
            break;
        case 4:
            fprintf(Ptrarq, "I,4,3\n");
            break;
        }
    }
    fclose(Ptrarq);
}

void inicializaproc(TpProcessador core[], int n)
{
    for(int i = 0; i < n; i++) 
    {
        core[i].ocupado = 0;
        core[i].tarefas_executadas = 0;
    }
}


int escolher_fila(TpFila f[], int n) //Pega o indice da fila que tem a menor quantidade de registros
{
    int menor=0;

    for(int i=1; i<n; i++)
    {
        if(f[i].FIM < f[menor].FIM)
            menor = i;       
    }
    return menor;
}

void inicializafila(TpFila f[], int n)
{
    for(int i=0; i<n; i++)
        inicializa(f[i]);
}

void simulacao(TpTarefa &taref)
{
    int n, tempo=0, intervalo=4, valid = 0, i, indice;
    FILE *Ptrarq = fopen("tarefas.txt", "r");
    printf("Digite a quantidade de processadores \n");
    scanf("%d", &n);
    TpProcessador core[n];
    TpFila f[n];
    inicializafila(f, n);
    
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        inicializaproc(core, n);
        while(!(feof(Ptrarq) &&  !valid))
        {
            if(tempo % intervalo == 0 && tempo != 0 && !feof(Ptrarq))
            {
                fscanf(Ptrarq, " %c,%d,%d", &taref.tipo, &taref.prioridade, &taref.tempo_total);
                /*switch (taref.tipo)
                {
                case 'G':
                    taref.prioridade = 1;
                    taref.tempo_total = 5;
                    break;
                case 'E':
                    taref.prioridade = 2;
                    taref.tempo_total = 8;
                    break;
                case 'L':
                    taref.prioridade = 3;
                    taref.tempo_total = 4;
                    break;
                case 'I':
                    taref.prioridade = 4;
                    taref.tempo_total = 3;
                    break;   
                } 
                */
                indice = escolher_fila(f, n);
                taref.tempo_restante = taref.tempo_total;
                taref.tempo_chegada = tempo;
                Inserir(f[indice], taref);
                printf("Inserido na fila %d\n", indice);
            }
            valid = 0;
            for(i=0; i<n; i++) //Atualizacao dos processadores
            {
                if(!core[i].ocupado && !filavazia(f[i].FIM))
                {
                    core[i].TarefaAtual = Retirar(f[i]);
                    core[i].ocupado = 1;
                    printf("Processador %d recebeu a tarefa\n", i);
                }
                if(core[i].ocupado)
                { 
                    core[i].TarefaAtual.tempo_restante--;
                    valid = 1;
                    if(core[i].TarefaAtual.tempo_restante == 0)
                    {
                        core[i].ocupado = 0;
                        core[i].tarefas_executadas++;
                        printf("Processador %d terminou a tarefa\n", i);
                    }
                    
                }
            }
            if(kbhit())
            {
                int num = getch();
                if(num >= 48 && num <= 57)
                    intervalo = num - '0'; //Como ele pega tabela ASCII, subtrai o char do numero digitado (48 - 57) pela tabela ascii do zero (48) resultando no numero digitado
            }
            
            printf("%d\n", tempo);
            Sleep(1000); 
            tempo++;
        }   
    }
    fclose(Ptrarq);
}

 

int main(void){
    TpFila f;
    TpTarefa taref;
    srand(time(NULL));
    geraraleatorio();
    printf("Arquivo gerado! \n");
    simulacao(taref);


    return 0;
}
