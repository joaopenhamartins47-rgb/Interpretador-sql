#define MAXFILA 10

struct elemento
{
    char info;
    int priori;
};

struct Tppriori
{
    int inicio, fim, qtde;
    elemento fila[MAXFILA];
};

void inicializa(Tppriori &f)
{
    f.fim = -1;
    f.qtde = 0;
    f.inicio = 0;
}

void inserir(Tppriori &f, elemento elem)
{
    if(f.fim == MAXFILA -1)
        f.fim = 0;
    else
        f.fim++;
    f.fila[f.fim] = elem;

    int i = f.fim;
    f.qtde++;
    elemento aux;
    int achou = 0;
    while (i != f.inicio && !achou) //remanejamento
    {
        int ant; 
        if (i == 0)
            ant = MAXFILA - 1;
        else
            ant = i - 1;
        
        if (f.fila[i].priori < f.fila[ant].priori)
        {
            aux = f.fila[i];
            f.fila[i] = f.fila[ant];
            f.fila[ant] = aux;

            i = ant;
        }
        else
            achou = 1;
    }
    
}

elemento retirar(Tppriori &f)
{  
    f.qtde--;    
    elemento aux = f.fila[f.inicio];
    if (f.inicio == MAXFILA -1)
        f.inicio = 0;
    else
        f.inicio++;
    return aux;
}

char cheio(int cont)
{
    return cont == MAXFILA;
}

char vazio(int cont)
{
    return cont == 0;
}

elemento elementoinicio(Tppriori f)
{
    return f.fila[f.inicio];
}

elemento elementofim(Tppriori f)
{
    return f.fila[f.fim];
}

void exibir(Tppriori f)
{
    elemento aux;
    while(!vazio(f.qtde))
    {
        aux = retirar(f);
        printf("Info: %c, Prioridade: %d\n", aux.info, aux.priori);
    }
}