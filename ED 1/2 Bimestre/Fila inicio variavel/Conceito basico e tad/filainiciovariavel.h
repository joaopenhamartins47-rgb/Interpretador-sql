#define MAXFILA 10

struct Tpfila
{
    int inicio, fim;
    char fila[MAXFILA];
};

void inicializa(Tpfila &f)
{
    f.inicio = 0;
    f.fim = -1;
}

void inserir(Tpfila &f, char elem)
{
    f.fila[++f.fim] = elem;
    if(f.fim == MAXFILA - 1)
    {
        int qtde = f.fim - f.inicio + 1;

        for(int i = 0; i < qtde; i++)
            f.fila[i] = f.fila[f.inicio + i];
        

        f.inicio = 0;
        f.fim = qtde - 1;
    }
}

char remover(Tpfila &f)
{
    char removido = f.fila[f.inicio++];
    if(f.inicio > f.fim)
        inicializa(f);
    return removido;
    
}

char vazio(int inicio, int fim)
{
    return inicio > fim;
}

char cheio(int inicio, int fim)
{
    return fim-inicio+1 == MAXFILA;
}

char elementoinicio(Tpfila f)
{
    return f.fila[f.inicio];
}

char elementofim(Tpfila f)
{
    return f.fila[f.fim];
}

void exibir(Tpfila f)
{
    while(!vazio(f.inicio, f.fim))
        printf("[%c] ", remover(f));
}