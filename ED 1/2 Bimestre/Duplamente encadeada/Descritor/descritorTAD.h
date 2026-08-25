
struct Tpno 
{
    char info;
    Tpno *ant, *prox;
};

struct Tpdesc
{
    Tpno *inicio, *fim;
};

void inicializar(Tpdesc &d)
{
    d.inicio = d.fim = NULL;
}

char vazia(Tpdesc &d)
{
    return d.inicio == NULL && d.fim == NULL;
}

void Inserir_inicio(Tpdesc &d, char info)
{
    Tpno *novo;
    novo = new Tpno;
    novo->info = info;
    novo->prox = NULL;
    novo->ant = NULL;
    if(!vazia(d))
    {
        novo->prox = d.inicio;
        d.inicio->ant = novo;
        d.inicio = novo;
    }
    else
        d.inicio = d.fim = novo;
}

void Inserir_final(Tpdesc &d, char info)
{
    Tpno *novo;
    novo = new Tpno;
    novo->info = info;
    novo->prox = NULL;
    novo->ant = NULL;
    if(!vazia(d))
    {
        novo->ant = d.fim;
        d.fim->prox = novo;
        d.fim = novo;
    }
    else
        d.inicio = d.fim = novo;
}

char retirar_inicio(Tpdesc &d)
{
    char elemento = d.inicio->info;
    Tpno *deletar = d.inicio;
    if(d.inicio->prox != NULL)
    {
        d.inicio = d.inicio->prox;
        d.inicio->ant = NULL;
    }
    else
        d.inicio = d.fim = NULL;
    delete deletar;
    return elemento;
}

char retirar_final(Tpdesc &d)
{
    char elemento = d.fim->info;
    Tpno *deletar = d.fim;
    if(d.fim->ant != NULL)
    {
        d.fim = d.fim->ant;
        d.fim->prox = NULL;
    }
    else
        d.inicio = d.fim = NULL;
    delete deletar;
    return elemento;
}

Tpno *acesso_inicio(Tpdesc &d)
{
    return d.inicio;
}

Tpno *acesso_fim(Tpdesc &d)
{
    return d.fim;
}

void exibir(Tpdesc d)
{
    while(d.inicio != NULL)
    {
        printf("%c ->", d.inicio->info);
        d.inicio = d.inicio->prox;
    }
}