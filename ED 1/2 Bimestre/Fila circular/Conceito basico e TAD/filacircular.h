#define MAXFILA 5

struct Tpfilacircular
{
    int inicio, fim, qtde;
    char fila[MAXFILA];
};

void inicializa(Tpfilacircular &f)
{
    f.fim = -1;
    f.inicio = 0;
    f.qtde = 0;
}

void inserir(Tpfilacircular &f, char elem)
{
    if(f.fim == MAXFILA - 1)
        f.fim = 0;
    else
        f.fim++;
    f.qtde++;
    f.fila[f.fim] = elem;
    
}

char remover(Tpfilacircular &f)
{
    char removido = f.fila[f.inicio++];
    if(f.inicio == MAXFILA)
        f.inicio = 0;
    f.qtde--;
    return removido;
}

char vazio(int qtde)
{
    return qtde == 0;
}

char cheio(int qtde)
{
    return qtde == MAXFILA;
}

char elementoinicio(Tpfilacircular f)
{
    return f.fila[f.inicio];
}

char elementofim(Tpfilacircular f)
{
    return f.fila[f.fim];
}

void exibir(Tpfilacircular f)
{
    while(!vazio(f.qtde))
        printf("%c", remover(f));
}