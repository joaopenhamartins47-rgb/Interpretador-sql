#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#include "filasemaforo.h"

#Task: Simulate a traffic light using a queue.
#Output: Time of cars that passed in the traffic light and the time the cars spent stopped

void simulacao(fila &f, carro car)
{
    inicializa(f);
    int tempo, veiculos_passaram=0, tempo_parado=0, verde=0;
    for(tempo =0; !kbhit(); tempo++)
    {
        if(rand() % 3 == 0) //gera carros aleatorios
        {
            if(!filacheia(f.fim))
            {
                car.info = 'C';
                car.tempo_chegada = tempo;
                inserir(f, car);
                printf("Chegou carro\n");
            }
        }
        if(tempo % 10 < 5) //Define o semaforo
            verde=1;
        else
            verde=0;
        if(verde)
        {
            printf("Verde! %d\n", tempo);
            if(!filavazia(f.fim)) //Se tiver verde e ja tiver carro na fila, eles passam, remove e adiciona o tempo que ficaram parado tempo-tempodechegada
            {
                veiculos_passaram++;
                car = remover(f);
                tempo_parado += tempo - car.tempo_chegada;
                exibe(f);
            }
            else
                printf("Nenhum carro passando!\n");
                
        }
        else
            printf("Vermelho! %d\n", tempo);
        
        Sleep(500);
    }
    printf("%d veiculos passaram pelo semaforo com %d tempo de veiculos parados\nTempo do semaforo: %d\n", veiculos_passaram, tempo_parado, tempo);
    getch();
}


int main(void)
{
    fila f;
    carro car;
    simulacao(f, car);
    return 0;
}
