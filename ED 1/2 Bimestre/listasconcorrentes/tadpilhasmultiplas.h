#define MAXPILHAM 10

struct Tppilham
{
    int topo1, topo2;
    char pilha[MAXPILHAM];
};

void inicializa(Tppilham &p)
{
    p.topo1 = -1;
    p.topo2 = MAXPILHAM;
}

void PUSH(Tppilham &p, char elem, int np)
{
    if (np == 1)
        p.pilha[++p.topo1] = elem;
    else
        p.pilha[--p.topo2] = elem;
}

char POP(Tppilham &p, int np)
{
    if (np == 1)
        return p.pilha[p.topo1--];
    return p.pilha[p.topo2++];
}

char vazia(int topo, int np)
{
    if(np == 1)
        return topo == -1;
    return topo == MAXPILHAM;
}

char cheia(int topo1, int topo2)
{
    return topo1+1 == topo2;
}

char elementotopo(Tppilham p, int np)
{
    if (np == 1)
        return p.pilha[p.topo1];
    return p.pilha[p.topo2];
}

void exibe(Tppilham p, int np)
{
    if (np == 1)
    {
        while(!vazia(p.topo1, np))
        {
            printf("%c", POP(p, np));
        }
    }
    else
    {
        while(!vazia(p.topo2, np))
            printf("%c", POP(p, np));
    }
}
