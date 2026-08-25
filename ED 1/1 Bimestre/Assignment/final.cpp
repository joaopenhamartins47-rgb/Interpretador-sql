#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "TAD.h"

/*
PARTICIPANTES:
* ALANA MAXIMO PEREIRA
* ANDRESSA FELISBERTO FERREIRA DINIZ
* CAMILA NERIS DOS SANTOS
* JOAO VITOR PENHA MARTINS
*/

// =====================================================================
//  INTERFACE
// =====================================================================

void newClearScr(int LI, int CI, int LF, int CF){
    for(int i = LI; i <= LF; i++){
        for(int j = CI; j <= CF; j++){
            gotoxy(j, i);
            printf("%c", 32);
        }
    }
}

void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF){
    int i;
    textcolor(CorT);
    textbackground(CorF);
    gotoxy(CI, LI); printf("%c", 201);
    gotoxy(CI, LF); printf("%c", 200);
    gotoxy(CF, LI); printf("%c", 187);
    gotoxy(CF, LF); printf("%c", 188);
    for(i = CI + 1; i < CF; i++){
        gotoxy(i, LI); printf("%c", 205);
        gotoxy(i, LF); printf("%c", 205);
    }
    for(i = LI + 1; i < LF; i++){
        gotoxy(CI, i); printf("%c", 186);
        gotoxy(CF, i); printf("%c", 186);
    }
    textcolor(7);
    textbackground(0);
}

void MolduraSimples(int CI, int LI, int CF, int LF, int CorT){
    int i;
    textcolor(CorT);
    gotoxy(CI, LI); printf("%c", 218);
    gotoxy(CI, LF); printf("%c", 192);
    gotoxy(CF, LI); printf("%c", 191);
    gotoxy(CF, LF); printf("%c", 217);
    for(i = CI + 1; i < CF; i++){
        gotoxy(i, LI); printf("%c", 196);
        gotoxy(i, LF); printf("%c", 196);
    }
    for(i = LI + 1; i < LF; i++){
        gotoxy(CI, i); printf("%c", 179);
        gotoxy(CF, i); printf("%c", 179);
    }
    textcolor(7);
}

void limparArea(int CI, int LI, int CF, int LF){
    for(int i = LI; i <= LF; i++){
        for(int j = CI; j <= CF; j++){
            gotoxy(j, i);
            putchar(' ');
        }
    }
}

const char* nomeTarefa(char tipo){
    switch(tipo){
        case 'G': return "Grav.Interna";
        case 'E': return "Grav.Externa";
        case 'L': return "Leitura     ";
        case 'I': return "Impressao   ";
        default:  return "Desconhecida";
    }
}

int prioridadeTipo(char tipo){
    switch(tipo){
        case 'G': return 1;
        case 'E': return 2;
        case 'L': return 3;
        case 'I': return 4;
        default:  return 9;
    }
}

// Largura útil: cols 2..99 = 98 cols (moldura externa menor)
// Cada bloco de processador calculado dinamicamente
void calcBloco(int n, int idx, int &CI, int &CF){
    int larguraUtil = 97; // de col 2 a col 99
    int larguraBloco = larguraUtil / n;
    CI = 2 + idx * larguraBloco;
    CF = CI + larguraBloco - 2;
}

void desenharProcessador(int n, int idx, TpProcessador &core, TpFila &f){
    int CI, CF;
    calcBloco(n, idx, CI, CF);

    // ---- Card processador (linhas 6..14) ----
    MolduraSimples(CI, 6, CF, 14, 13);
    textcolor(11);
    gotoxy(CI + 2, 6);
    printf(" Processador %d ", idx + 1);

    limparArea(CI + 1, 7, CF - 1, 13);

    if(core.ocupado){
        // Linha de destaque: nome da tarefa em verde
        textcolor(10);
        gotoxy(CI + 2, 8);
        printf("[%d] %s", prioridadeTipo(core.TarefaAtual.tipo), nomeTarefa(core.TarefaAtual.tipo));
        textcolor(11);
        gotoxy(CI + 2, 9);
        printf("Restante : %d ut ", core.TarefaAtual.tempo_restante);
        gotoxy(CI + 2, 10);
        printf("Chegada  : %d ut ", core.TarefaAtual.tempo_chegada);
        gotoxy(CI + 2, 11);
        printf("Total    : %d ut ", core.TarefaAtual.tempo_total);
    } else {
        textcolor(8);
        gotoxy(CI + 2, 10);
        printf("  [ ocioso ]  ");
    }

    // Exec no rodapé do card
    textcolor(14);
    gotoxy(CI + 2, 13);
    printf("Exec: %d tar.", core.tarefas_executadas);
    textcolor(7);

    // ---- Card fila (linhas 16..38) ----
    MolduraSimples(CI, 16, CF, 38, 9);
    textcolor(14);
    gotoxy(CI + 2, 16);
    printf(" Fila (%d) ", f.FIM + 1); // mostra quantidade

    limparArea(CI + 1, 17, CF - 1, 37);

    int maxLin = 37;
    int lin = 17;

    if(filavazia(f.FIM)){
        textcolor(8);
        gotoxy(CI + 2, lin);
        printf("fila vazia");
    } else {
        for(int k = 0; k <= f.FIM && lin <= maxLin; k++, lin++){
            TpTarefa t = f.FILA[k];

            if(k == 0){
                // Próxima a executar: destaque ciano
                textcolor(11);
                gotoxy(CI + 2, lin);
                printf("> [%d] %s %dut", prioridadeTipo(t.tipo), nomeTarefa(t.tipo), t.tempo_restante);
            } else {
                // Verifica se essa tarefa tem prioridade maior que a anterior
                // (indica que chegou e "furou" alguém na fila)
                TpTarefa anterior = f.FILA[k - 1];
                if(t.prioridade < anterior.prioridade){
                    // Não ocorre pois a fila já está ordenada, mas mantemos a lógica
                    textcolor(12);
                } else {
                    textcolor(7);
                }
                gotoxy(CI + 2, lin);
                printf("  [%d] %s %dut", prioridadeTipo(t.tipo), nomeTarefa(t.tipo), t.tempo_restante);
            }
        }
        if(f.FIM + 1 > maxLin - 17 + 1){
            textcolor(8);
            gotoxy(CI + 2, maxLin);
            printf("... +%d na fila", (f.FIM + 1) - (maxLin - 17));
        }
    }
    textcolor(7);
}

void desenharTodosProcessadores(int n, TpProcessador core[], TpFila f[]){
    for(int i = 0; i < n; i++)
        desenharProcessador(n, i, core[i], f[i]);
}

void atualizarTimer(int tempo){
    int min = tempo / 60;
    int seg = tempo % 60;
    textcolor(15);
    gotoxy(78, 3);
    printf("TEMP UT: %02d:%02d", min, seg);
    textcolor(7);
}

void exibirAlerta(const char* msg){
    newClearScr(39, 2, 39, 99);
    textcolor(14);
    gotoxy(3, 39);
    // Trunca para caber na moldura (max ~95 chars)
    char buf[96];
    strncpy(buf, msg, 95);
    buf[95] = '\0';
    printf("%s", buf);
    textcolor(7);
}

void application(void){
    system("cls");
    // Moldura externa menor: cols 1..100, linhas 1..40
    Moldura(1, 1, 100, 40, 13, 0);
    // Cabeçalho título
    Moldura(2, 2, 74, 4, 15, 5);
    textcolor(11);
    gotoxy(22, 3);
    printf("FILA DE PROCESSADORES");
    // Caixa timer
    Moldura(75, 2, 99, 4, 15, 4);
    textcolor(15);
    gotoxy(78, 3);
    printf("TEMP UT: 00:00");
    textcolor(7);
}

// =====================================================================
//  ESTRUTURAS DO PROGRAMA
// =====================================================================

void geraraleatorio(void){
    int i, op;
    FILE *Ptrarq = fopen("tarefas.txt", "w");
    for(i = 0; i < 1000; i++){
        op = rand() % 4 + 1;
        switch(op){
            case 1: fprintf(Ptrarq, "G,1,5\n"); break;
            case 2: fprintf(Ptrarq, "E,2,8\n"); break;
            case 3: fprintf(Ptrarq, "L,3,4\n"); break;
            case 4: fprintf(Ptrarq, "I,4,3\n"); break;
        }
    }
    fclose(Ptrarq);
}

void inicializaproc(TpProcessador core[], int n){
    for(int i = 0; i < n; i++){
        core[i].ocupado = 0;
        core[i].tarefas_executadas = 0;
    }
}

int escolher_fila(TpFila f[], int n){
    int menor = 0;
    for(int i = 1; i < n; i++){
        if(f[i].FIM < f[menor].FIM)
            menor = i;
    }
    return menor;
}

void inicializafila(TpFila f[], int n){
    for(int i = 0; i < n; i++)
        inicializa(f[i]);
}

void simulacao(TpTarefa &taref)
{
    int n, tempo = 0, intervalo = 4, valid = 0, i, indice;
    char alertaMsg[200];
    FILE *Ptrarq = fopen("tarefas.txt", "r");

    // Pede processadores antes de montar tela
    system("cls");
    textcolor(11);
    gotoxy(5, 5);
    printf("Digite a quantidade de processadores (1 a 6): ");
    textcolor(15);
    scanf("%d", &n);
    if(n < 1) n = 1;
    if(n > 6) n = 6;

    system("mode con cols=102 lines=42");
    application();
    atualizarTimer(0);

    TpProcessador core[n];
    TpFila f[n];

    if(Ptrarq == NULL)
    {
        exibirAlerta("ERRO: nao foi possivel abrir tarefas.txt!");
        getch();
        return;
    }

    inicializaproc(core, n);
    inicializafila(f, n);
    desenharTodosProcessadores(n, core, f);

    exibirAlerta("Simulacao iniciada! Pressione [1-9] para alterar o intervalo de chegada de tarefas.");

    while(!(feof(Ptrarq) && !valid))
    {

        // Chegada de nova tarefa
        if(tempo % intervalo == 0 && tempo != 0 && !feof(Ptrarq))
        {
            fscanf(Ptrarq, " %c,%d,%d", &taref.tipo, &taref.prioridade, &taref.tempo_total);
            indice = escolher_fila(f, n);
            taref.tempo_restante = taref.tempo_total;
            taref.tempo_chegada = tempo;
            if(!filacheia(f[indice].FIM))
            {
                Inserir(f[indice], taref);
                sprintf(alertaMsg,"t=%d | Nova tarefa [%d-%s] -> fila %d (%d na fila) | intervalo: %d ut | [1-9] altera",tempo, prioridadeTipo(taref.tipo),                  nomeTarefa(taref.tipo),indice + 1, f[indice].FIM + 1, intervalo);
                exibirAlerta(alertaMsg);
            } 
            else
            {
                sprintf(alertaMsg, "t=%d | Fila %d CHEIA! Tarefa descartada", tempo, indice + 1);
                exibirAlerta(alertaMsg);
            }       
        }
        valid = 0;
        for(i = 0; i < n; i++)
        {
            if(!core[i].ocupado && !filavazia(f[i].FIM))
            {
                core[i].TarefaAtual = Retirar(f[i]);
                core[i].ocupado = 1;
            }
            if(core[i].ocupado)
            {
                core[i].TarefaAtual.tempo_restante--;
                valid = 1;
                if(core[i].TarefaAtual.tempo_restante == 0)
                {
                    core[i].ocupado = 0;
                    core[i].tarefas_executadas++;
                    sprintf(alertaMsg,"t=%d | Processador %d CONCLUIU '%s' | Total executadas: %d | [1-9] altera intervalo",tempo, i + 1, nomeTarefa(core[i].TarefaAtual.tipo), core[i].tarefas_executadas);
                    exibirAlerta(alertaMsg);
                }
            }
        }

        desenharTodosProcessadores(n, core, f);
        atualizarTimer(tempo);

        if(kbhit())
        {
            int num = getch();
            if(num >= 49 && num <= 57){
                intervalo = num - '0';
                sprintf(alertaMsg,"t=%d | Intervalo alterado para %d ut | [1-9] altera intervalo",tempo, intervalo);
                exibirAlerta(alertaMsg);
            }
        }

        Sleep(1000);
        tempo++;
    }

    fclose(Ptrarq);
    exibirAlerta("Simulacao concluida! Pressione qualquer tecla para sair...");
    getch();
}

int main(void){
    system("mode con cols=102 lines=42");
    srand(time(NULL));
    geraraleatorio();

    TpTarefa taref;
    simulacao(taref);

    return 0;
}