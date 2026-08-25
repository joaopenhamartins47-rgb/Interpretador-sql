#include <stdlib.h> 
#include <time.h> 
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "pilhateste.h"

void gerararq(void)
{
	FILE *Ptrarq = fopen("dados.txt", "w");
	for(int i=0; i<2000;i ++)
	{
		int num = rand()%2000+1;
		fprintf(Ptrarq, "%d\n", num);
	}
	fclose(Ptrarq);
}

void pegarnum(pilha &p)
{
	int num, op, cheio=0, soma=0;
	inicializar(p);
	FILE *Ptrarq = fopen("dados.txt", "r");
	if(Ptrarq == NULL)
	{
		printf("Erro ao abrir arquivo!\n");
	}
	else
	{
		while(!feof(Ptrarq))
		{
			if(fscanf(Ptrarq, "%d", &num) == 1)
			{
				op = rand()%2+1;
				if(op == 1)
				{
					if(!cheia(p.topo))
					{
						PUSH(p, num);
						printf("Elemento adicionado! \n");
					
					}
					else
					{
						printf("Pilha cheia! \n");
						cheio++;
					}
						
						
				}
				else
				{
					if(!vazia(p.topo))
					{
						soma += POP(p);
						printf("Elemento removido! \n");
					}
					else
						printf("Pilha vazia! \n");
						
				}
				exibe(p);
				Sleep(1);
			}
		}
		printf("\n%d vezes a pilha esteve cheia e a soma dos elementos retirados foi de: %d\n", cheio, soma);
		fclose(Ptrarq);
	}
	
		
}



int main(void)
{
	pilha p;
	srand(time(NULL));
	gerararq();
	pegarnum(p);
	return 0;
}
