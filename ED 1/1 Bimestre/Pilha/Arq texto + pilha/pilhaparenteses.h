#define MAX_PILHA 10000


struct pilha
{
    int topo;
    char pilha[MAX_PILHA];
};

void inicializa(pilha &p);
void PUSH(pilha &p, char elem);
char POP(pilha &p);
char cheia(int topo);
char vazia(int topo);
char elementotopo(pilha p);
void exibe(pilha p);

void inicializa(pilha &p)
{
    p.topo = -1;
}

void PUSH(pilha &p, char elem)
{
    p.pilha[++p.topo] = elem;
}

char POP(pilha &p)
{
    return p.pilha[p.topo--];
}

char cheia(int topo)
{
    return topo == MAX_PILHA-1;
}
char vazia(int topo)
{
    return topo == -1;
}
char elementotopo(pilha p)
{
    return p.pilha[p.topo];
}
void exibe(pilha p)
{
    while(!vazia(p.topo))
        printf("%c\n", POP(p));
}