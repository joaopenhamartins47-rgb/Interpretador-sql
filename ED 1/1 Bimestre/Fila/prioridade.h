#define MAXFILA 10

struct elemento
{
    char info;
    int prioridade;
};

struct fila
{
    int fim;
    elemento f[MAXFILA];
};

void inicializa(fila &f);
char filavazia(int fim);
char filacheia(int fim);
void inserir(fila &f, elemento elem);
elemento remover(fila &f);
elemento elementoinicio(fila f);
elemento elementofim(fila f);
void exibir(fila f);

void inicializa(fila &f)
{
    f.fim = -1;
}

char filavazia(int fim)
{
    return fim == -1;
}
char filacheia(int fim)
{
    return fim == MAXFILA-1;
}

void inserir(fila &f, elemento elem)
{
    int i, achou=0;
    elemento aux;
    f.f[++f.fim] = elem;
    for(i = f.fim; i>0 && !achou; i--)
    {
        if(f.f[i].prioridade < f.f[i-1].prioridade) //1 - Alta 2 - Media 3 - Baixa
        {
            aux = f.f[i];
            f.f[i] = f.f[i-1];
            f.f[i-1] = aux;
        }
            
        else
            achou = 1;
    }
}

elemento remover(fila &f)
{
    elemento aux;
    aux = f.f[0];
    for(int i=0; i < f.fim; i++)
        f.f[i] = f.f[i+1];
    f.fim--;
    return aux;
}

elemento elementoinicio(fila f)
{
    return f.f[0];
}

elemento elementofim(fila f)
{
    return f.f[f.fim];
}

void exibir(fila f)
{
    elemento aux;
    while(!filavazia(f.fim))
    {
        aux = remover(f);
        printf("Info: %c, Prioridade: %d\n", aux.info, aux.prioridade);
    }
}



