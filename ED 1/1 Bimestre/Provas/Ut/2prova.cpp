#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <conio2.h>
#include <stdlib.h>
#include <windows.h>

#include "fila.h"

//

void simulacao(Tpfila &f)
{
    FILE *Ptrarq = fopen("requisicao.txt", "r");
    sistema aux, request;
    
    if(Ptrarq == NULL)
        printf("Arquivo inexistente! \n");
    else
    {
        int ocupado = 0;
        int total_espera = 0;
        int qtd = 0;

        for(int ut = 0; !(feof(Ptrarq) && !ocupado && filavazia(f.fim)) ; ut++)
        {
            if(ut % 3 == 0 && ut != 0 && !feof(Ptrarq))
            {
                fscanf(Ptrarq, "%d, %[^,], %d, %d", &aux.id, aux.nome, &aux.prioridade, &aux.tempo);
                
                if(!filacheia(f.fim))
                {
                    aux.chegada = ut;
                    aux.tempototal = aux.tempo;
                    aux.iniciou = 0; //controla se já contou espera

                    inserir(f, aux);
                    printf("Tarefa requisitada!\n");
                }
            }

            if(!ocupado && !filavazia(f.fim))
            {
                request = remover(f);

                if(!request.iniciou)
                {
                    total_espera += (ut - request.chegada);
                    qtd++;
                    request.iniciou = 1;
                }

                printf("Inicio -> ID: %d, Nome: %s, Prioridade: %d\n",request.id, request.nome, request.prioridade);

                ocupado = 1;
            }

            if(ocupado && !filavazia(f.fim) && f.fila[0].prioridade < request.prioridade)
            {
                inserir(f, request);
                request = remover(f);

                if(!request.iniciou)
                {
                    total_espera += (ut - request.chegada);
                    qtd++;
                    request.iniciou = 1;
                }

                printf("Trocou para a tarefa %s, prioridade: %d\n",request.nome, request.prioridade);
            }

            if(ocupado)
            {
                request.tempo--;

                if(request.tempo == 0)
                {
                    printf("Tarefa terminada! \n");
                    printf("Tempo de execucao: %d\n", request.tempototal);

                    ocupado = 0;
                }
            }

            printf("%d\n", ut);
            Sleep(500);
        }
        fclose(Ptrarq);
        printf("Tempo medio de espera: %.2f\n", (float)total_espera / qtd);
    }
}



int main(void)
{
	Tpfila f;
    inicializa(f);
	simulacao(f);
    return 0;
}
