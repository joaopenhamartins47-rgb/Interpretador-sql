#define MAXFILA 10

struct atendimento
{
    char nome[30];
    int priori, tempo, temporestante, chegada;
}; 

struct Tpfila
{
    int fim;
    atendimento fila[MAXFILA];
};

void inicializafila(Tpfila &f)
{
    f.fim = -1;
}

void inserir(Tpfila &f, atendimento elem)
{
    f.fila[++f.fim] = elem;
    atendimento aux;
    int achou = 0;
    for(int i = f.fim; i>0 && !achou; i--)
    {
        if(f.fila[i].priori < f.fila[i-1].priori)
        {
            aux = f.fila[i];
            f.fila[i] = f.fila[i-1];
            f.fila[i-1] = aux;
        }
        else 
            achou = 1;
    }
}

atendimento remover(Tpfila &f)
{
    atendimento removido = f.fila[0];
    for(int i=0; i<f.fim; i++)
    {
        f.fila[i] = f.fila[i+1];
    }
    f.fim--;
    return removido;
}

char filacheia(int fim)
{
    return fim == MAXFILA-1;
}

char filavazia(int fim)
{
    return fim == -1;
}

atendimento elementofinal(Tpfila f)
{
    return f.fila[f.fim];
}

atendimento elementoinicio(Tpfila f)
{
    return f.fila[0];
}

void exibefila(Tpfila f)
{
    while(!filavazia(f.fim))
    {
        atendimento aux = remover(f);
        printf("%s, prioridade: %d\n", aux.nome, aux.priori);
    }
}