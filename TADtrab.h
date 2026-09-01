struct Campos
{
    struct valor_caixa *Patual;
    char campo[30];
    char tipo;
    char pk;
    struct Campos *fk;
    struct valor_caixa *Pdados;
    struct Campos *prox;
};typedef struct Campos campos;

union valor
{
    int valorI;
    char valorT[20];
    char valorD[10];
    float valorN;
    char valorC;
};

struct valor_caixa
{
    union valor dado;
    struct valor_caixa *prox;
};typedef struct valor_caixa valorc;

struct Tabela
{
    struct Tabela *ant, *prox;
    campos *pcampos;
    char nome_tabela[30];
};typedef struct Tabela tabela;

struct banco_de_dados
{
    char nome_banco[30];
    tabela *ptabelas;
};typedef struct banco_de_dados db;

struct pontdb
{
    db *pbanco;
};typedef struct pontdb pondb;


/*
Banco_Dados *criar_banco(...);
tabela *criar_tabela(...);
campos *criar_campo(...);
valor *criar_valor(...);
*/

void inicializa_ponteiro_banco(pondb **inicio)
{
    *inicio = NULL;
}


void criar_banco(pondb **inicio, char *nome)
{
    pondb *novo_pon = (pondb*)malloc(sizeof(pondb));
    db *novo = (db*)malloc(sizeof(db));
    strcpy(novo->nome_banco, nome);
    novo->ptabelas = NULL;
    novo_pon->pbanco = novo;
    *inicio= novo_pon; 
}

char tabelas_vazias(tabela *inicio)
{
    return inicio == NULL;
}

tabela *criar_tabela(char *nome)
{
    tabela *novo = (tabela*)malloc(sizeof(tabela));
    novo->ant = NULL;
    novo->prox = NULL;
    novo->pcampos = NULL;
    strcpy(novo->nome_tabela, nome);
    return novo;
}

campos *criar_campo(char *nome, char tipo, char pk)
{
    campos *novo = (campos*)malloc(sizeof(campos));
    strcpy(novo->campo, nome);
    novo->pk = pk;
    novo->tipo = tipo;
    novo->prox = NULL;
    novo->fk = NULL;
    novo->Patual = NULL;
    novo->Pdados = NULL;
    return novo;
}

valorc *criar_valor(void)
{
    valorc *novo = malloc(sizeof(valorc));
    novo->prox = NULL;
    return novo;
}



/*
void inserir_tabela(...);
void inserir_campo(...);
void inserir_valor(...);
*/

tabela *inserir_tabela(tabela **inicio, char *nome)
{
    tabela *novo = criar_tabela(nome);
    if(tabelas_vazias(*inicio))
        *inicio = novo;
    
    else{
        tabela *aux = *inicio;
        while(aux->prox != NULL)
            aux = aux->prox;
        novo->ant = aux;
        aux->prox = novo;
    }
    return novo;
}

campos *inserir_campo(tabela *aux, char *nome, char tipo, char pk)
{
    campos *novo = criar_campo(nome, tipo, pk);
    if(aux->pcampos == NULL)
        aux->pcampos = novo;
    else
    {
        campos *and = aux->pcampos;
        while(and->prox != NULL)
            and = and->prox;
        and->prox = novo;
    }
    return novo;
}

valorc  *inserir_valor_int(campos *inicio, int valor)
{
    valorc *novo = criar_valor();
    novo->dado.valorI = valor;
    if(inicio->Patual == NULL){
        inicio->Patual = novo;
        inicio->Pdados = novo;
    }
    else
    {
        valorc *aux = inicio->Patual;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return novo;
}

valorc  *inserir_valor_float(campos *inicio, float valor)
{
    valorc *novo = criar_valor();
    novo->dado.valorN = valor;
    if(inicio->Patual == NULL){
        inicio->Patual = novo;
        inicio->Pdados = novo;
    }
    else
    {
        valorc *aux = inicio->Patual;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return novo;
}

valorc  *inserir_valor_data(campos *inicio, char *data)
{
    valorc *novo = criar_valor();
    strcpy(novo->dado.valorD, data);
    if(inicio->Patual == NULL){
        inicio->Patual = novo;
        inicio->Pdados = novo;
    }
    else
    {
        valorc *aux = inicio->Patual;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return novo;
}

valorc  *inserir_valor_texto(campos *inicio, char *texto)
{
    valorc *novo = criar_valor();
    strcpy(novo->dado.valorT, texto);
    if(inicio->Patual == NULL){
        inicio->Patual = novo;
        inicio->Pdados = novo;
    }
    else
    {
        valorc *aux = inicio->Patual;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return novo;
}

valorc  *inserir_valor_char(campos *inicio, char valor)
{
    valorc *novo = criar_valor();
    novo->dado.valorC = valor;
    if(inicio->Patual == NULL){
        inicio->Patual = novo;
        inicio->Pdados = novo;
    }
    else
    {
        valorc *aux = inicio->Patual;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return novo;
}

/*
tabela *buscar_tabela(...);
campos *buscar_campo(...);
*/

tabela *buscar_tabela(tabela *inicio, char *nome)
{
    tabela *aux = inicio;
    while(aux != NULL && strcmp(aux->nome_tabela, nome) != 0)
        aux = aux->prox;
    return aux;
}

campos *buscar_campo(campos *inicio, char *nome)
{
    campos *aux = inicio;
    while(aux != NULL && strcmp(aux->campo, nome) != 0)
        aux = aux->prox;
    return aux;
}

int tipo_valido(char tipo)
{
    return tipo == 'I' || tipo == 'N' || tipo == 'D' || tipo == 'C' || tipo == 'T';
}
/*
Criar uma função para imprimir o banco, tabelas, campos e dados
*/

void imprimir_banco(pondb *banco)
{
    if(!banco)
        printf("Banco não existente!\n");
    else
    {
        
        printf("Banco: %s\n", banco->pbanco->nome_banco);
        tabela *aux = banco->pbanco->ptabelas;
        while(aux)
        {

            printf("Tabela: %s \t", aux->nome_tabela);
            campos *aux_cam = aux->pcampos;
            printf("Campos da tabela: \n");
            while(aux_cam)
            {

                printf("Campo: %s \t Tipo: %c \t PK: %c\t", aux_cam->campo, aux_cam->tipo, aux_cam->pk);
                printf("\nValores:");
                valorc *aux_valor = aux_cam->Pdados;
                while(aux_valor)
                {
                    if(aux_cam->tipo == 'I')
                        printf("Valor: %d\n", aux_valor->dado.valorI);
                    else if(aux_cam->tipo == 'D')
                        printf("Valor: %s\n", aux_valor->dado.valorD);
                    else if(aux_cam->tipo == 'T')
                        printf("Valor: %s\n", aux_valor->dado.valorT);
                    else if(aux_cam->tipo == 'N')
                        printf("Valor: %.2f\n", aux_valor->dado.valorN);
                    else if(aux_cam->tipo == 'C')
                        printf("Valor: %c\n", aux_valor->dado.valorC);

                    aux_valor = aux_valor->prox;
                }
                printf("\n");
                aux_cam = aux_cam->prox;
            }
            printf("-------------------------\n");
            aux = aux->prox;
        }
    }
}


void imprimir_tabela(tabela *inicio)
{
    while(inicio)
    {
        printf("Tabela: %s\n", inicio->nome_tabela);
        inicio = inicio->prox;
    }
}

void imprimir_campos(campos *inicio)
{
    while(inicio)
    {
        printf("Campo: %s \t Tipo: %c \t PK: %c\n", inicio->campo, inicio->tipo, inicio->pk);
        inicio = inicio->prox;
    }
}

void imprimir_valores(campos *inicio)
{
    valorc *aux_valor = inicio->Pdados;
    while(aux_valor)
    {
        if(inicio->tipo == 'I')
            printf("Valor: %d\n", aux_valor->dado.valorI);
        else if(inicio->tipo == 'D')
            printf("Valor: %s\n", aux_valor->dado.valorD);
        else if(inicio->tipo == 'T')
            printf("Valor: %s\n", aux_valor->dado.valorT);
        else if(inicio->tipo == 'N')
            printf("Valor: %.2f\n", aux_valor->dado.valorN);
        else if(inicio->tipo == 'C')
            printf("Valor: %c\n", aux_valor->dado.valorC);

        aux_valor = aux_valor->prox;
    }
}

/*
Para o delete e update
buscar_valor(...)
remover_valor(...)
alterar_valor(...)
*/

/*
Conferir os Parsers dos comandos sql ex: INSERT INTO cliente (id_cliente, nome) VALUES (1, 'Joao');

Se torna:
buscar_tabela("cliente")
        ↓
buscar_campo("id_cliente")
        ↓
inserir_valor_int(...)

buscar_campo("nome")
        ↓
inserir_valor_texto(...)
*/

/*
executar_insert(...) - Funcao pra extrair os dados do parser e realizar a insercao
*/

/*
Resumo do que falta:
SUPORTE
├── tipo_valido
├── comparar_valor
├── alterar_valor
└── remover_valor

INSERT
└── executar_insert

UPDATE
├── avaliar_condicao
└── executar_update

DELETE
├── avaliar_condicao
└── executar_delete

FK
└── criar_fk

SELECT
├── executar_select
├── avaliar_where
├── avaliar_between
└── executar_join
*/

