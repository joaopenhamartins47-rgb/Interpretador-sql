#define MAXFILA 10

struct sistema
{
    int prioridade, id, chegada, tempo, tempototal, iniciou;
    char nome[30];
};

struct Tpfila
{
    int fim;
    sistema fila[MAXFILA];
};

void inicializa(Tpfila &f);
void inserir(Tpfila &f, sistema elem);
sistema remover(Tpfila &f);
sistema elementofim(Tpfila f);
sistema elementoinicio(Tpfila);
char filacheia(int fim);
char filavazia(int fim);
void exibe(Tpfila f);

void inicializa(Tpfila &f)
{
    f.fim = -1;
}

void inserir(Tpfila &f, sistema elem)
{
    sistema aux;
    int achou=0;
    f.fila[++f.fim] = elem;
    for(int i = f.fim; i>0 && !achou;i--)
    {
        if(f.fila[i].prioridade < f.fila[i-1].prioridade)
        {
            aux = f.fila[i];
            f.fila[i] = f.fila[i-1];
            f.fila[i-1] = aux;
        }
    }
}

sistema remover(Tpfila &f)
{
    sistema removido = f.fila[0];
    for(int i = 0; i<f.fim; i++)
    {
        f.fila[i] = f.fila[i+1];
    }
    f.fim--;
    return removido;
}

char filacheia(int fim)
{
    return fim == MAXFILA -1;
}

char filavazia(int fim)
{
    return fim == -1;
}

sistema elementoinicio(Tpfila f)
{
    return f.fila[0];
}

sistema elementofim(Tpfila f)
{
    return f.fila[f.fim];
}

void exibe(Tpfila f)
{
    sistema aux;
    while(!filavazia(f.fim))
    {
        aux = remover(f);
        printf("Nome: %s, Prioridade: %d\n", aux.nome, aux.prioridade);
    }
}