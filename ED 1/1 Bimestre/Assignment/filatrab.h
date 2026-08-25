#define MAXFILA 1000

struct TpTarefa{
    char tipo;			 // 1º)grav. interna, 2º)grav. externa, 3º)leitura, 4º)impressao;
	int prioridade; 
    int tempo_total;  	 // tempo necessario -> (ut)
    int tempo_restante;   // tempo restante
    int tempo_chegada;    // quando entrou na fila
};

struct TpFila{
    int FIM;
    TpTarefa FILA[MAXFILA];
};

struct TpProcessador{
    TpTarefa TarefaAtual;
    int ocupado;
    int tarefas_executadas;
};

void Inserir(TpFila &f, TpTarefa t){
	f.FILA[++f.FIM] = t;
	int i = f.FIM;
	while(i > 0 && f.FILA[i].prioridade < f.FILA[i-1].prioridade){
		TpTarefa aux = f.FILA[i];
		f.FILA[i] = f.FILA[i-1];
		f.FILA[i-1] = aux;
		i--;
	}
}

void inicializa(TpFila &f){
	f.FIM = -1;
}

char filavazia(int fim){
	return fim == -1;
}

char filacheia(int fim){
	return fim == MAXFILA -1;
}

TpTarefa Retirar(TpFila &f){
	TpTarefa retirado = f.FILA[0];
	for(int i = 0; i < f.FIM; i++)
		f.FILA[i] = f.FILA[i+1];
	f.FIM --;
	return retirado;
}

TpTarefa ElementoInicio(TpFila f){
	return f.FILA[0];
}

TpTarefa ElementoFim(TpFila f){
	return f.FILA[f.FIM];
}

void exibe(TpFila f)
{
    TpTarefa aux;
    while(!filavazia(f.FIM))
    {
        aux = Retirar(f);
        printf("%c | pri: %d | tempo: %d\n", aux.tipo, aux.prioridade, aux.tempo_total);    }     
}