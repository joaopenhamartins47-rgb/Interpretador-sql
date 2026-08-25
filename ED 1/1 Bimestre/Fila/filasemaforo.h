#define MAXFILA 20

struct carro
{
    char info;
    int tempo_chegada;
};
struct fila
{
    int fim;
    carro f[MAXFILA];
};

void inicializa(fila &f);
char filacheia(int fim);
char filavazia(int fim);
void inserir(fila &f, carro car);
carro remover(fila &f);
carro elementotopo(fila f);
carro elementofim(fila f);
void exibir(fila f);

void inicializa(fila &f)
{
    f.fim= -1;
}

char filacheia(int fim)
{
    return fim == MAXFILA-1;
}

char filavazia(int fim)
{
    return fim == -1;
}

void inserir(fila &f, carro car)
{
    f.f[++f.fim] = car;       
}

carro remover(fila &f)
{
    carro aux;
    aux = f.f[0];
    for(int i=0; i<f.fim; i++)
        f.f[i] = f.f[i+1];
    f.fim--;
    return aux;
}

carro elementotopo(fila f)
{
    return f.f[f.fim];
}

carro elementofim(fila f)
{
    return f.f[0];
}

void exibe(fila f)
{
    carro aux;
    while(!filavazia(f.fim))
    {
        aux = remover(f);
        printf("%c, %d", aux.info, aux.tempo_chegada);
    }  
}

