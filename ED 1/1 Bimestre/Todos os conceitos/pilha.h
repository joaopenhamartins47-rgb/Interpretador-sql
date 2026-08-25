#define MAXPILHA 10

struct Tppilha
{
    int topo;
    char pilha[MAXPILHA];
};

void inicializapilha(Tppilha &p)
{
    p.topo = -1;
}

void PUSH(Tppilha &p, char elem)
{
    p.pilha[++p.topo] = elem;
}

char POP(Tppilha &p)
{
    return p.pilha[p.topo--];
}

char pilhavazia(int topo)
{
    return topo == -1;
}
char pilhacheia(int topo)
{
    return topo == MAXPILHA-1;
}
char elementotopo(Tppilha p)
{
    return p.pilha[p.topo];
}
char elementoinicio(Tppilha p)
{
    return p.pilha[0];
}
void exibe(Tppilha p)
{
    while(!pilhavazia(p.topo))
        printf("%c ", POP(p));
}