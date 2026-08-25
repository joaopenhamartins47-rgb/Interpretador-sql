#define MAXPILHA 10

struct pilha
{
    int topo;
    int PILHA[MAXPILHA];
};

void inicializar(pilha &p);
void PUSH(pilha &p, int elemento);
int POP(pilha &p);
int elementotopo(pilha p);
char vazia(int topo);
char cheia(int topo);
void exibe(pilha p);

void inicializar(pilha &p)
{
    p.topo = -1;
}

void PUSH(pilha &p, int elemento)
{
    p.PILHA[++p.topo] = elemento;
}

int POP(pilha &p)
{
    return p.PILHA[p.topo--];
}

int elementotopo(pilha p)
{
    return p.PILHA[p.topo];
}

char cheia(int topo)
{
    return topo == MAXPILHA-1;
}

char vazia(int topo)
{
    return topo == -1;
}

void exibe(pilha p)
{
    while(!vazia(p.topo))
        printf("[%d]", POP(p));
} 




     

