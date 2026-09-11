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

struct filap
{
    char info[20];
    struct filap *prox;
};typedef struct filap fila;

char isEmpty(fila *f)
{
    return f == NULL;
}

void enqueue(fila **f, char *info)
{
    fila *novo = (fila*)malloc(sizeof(fila));
    strcpy(novo->info, info);
    novo->prox = NULL;
    if(!*f)
        *f = novo;
    else
    {
        fila *aux = *f;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

void dequeue(fila **f, char info[])
{
    fila *aux = *f;
    strcpy(info, (*f)->info);
    *f = (*f)->prox;
    free(aux);
}

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
executar_insert(...) - Funcao pra extrair os dados do parser e realizar a insercao
*/
void executar_insert(tabela *ptab, fila **f1, fila **f2, fila **f3)
{
    char info[20];
    tabela *nt;
    campos *nc;
    valorc *novo, *aux;
    if(!isEmpty(*f1))
    {
        dequeue(&*f1, info);

        nt = buscar_tabela(ptab, info);

        if(nt)
        {
            campos *aux = nt->pcampos;

            while(!isEmpty(*f2) && !isEmpty(*f3))
            {
                dequeue(&*f2, info);

                nc = buscar_campo(aux, info);

                if(nc)
                {
                    dequeue(&*f3, info);

                    novo = criar_valor();
                    novo->prox = NULL;

                    if(nc->tipo == 'I')
                        novo->dado.valorI = atoi(info);

                    else if(nc->tipo == 'T')
                        strcpy(novo->dado.valorT, info);

                    else if(nc->tipo == 'D')
                        strcpy(novo->dado.valorD, info);

                    else if(nc->tipo == 'N')
                        novo->dado.valorN = atof(info);

                    else if(nc->tipo == 'C')
                        novo->dado.valorC = info[0];

                    if(!nc->Patual)
                        nc->Pdados = nc->Patual = novo;
                    else
                    {
                        aux = nc->Patual;

                        while(aux->prox != NULL)
                            aux = aux->prox;

                        aux->prox = novo;
                    }
                    
                }
            }
        }
    }
}

int buscar_posicao(campos *inicio, char *operador, char *valor)
{
    int pos = 0;
    valorc *aux = inicio->Pdados;

    while(aux)
    {
        if(inicio->tipo == 'I')
        {
            if(strcmp(operador, "=") == 0 &&
               aux->dado.valorI == atoi(valor))
                return pos;
        }
        else if(inicio->tipo == 'N')
        {
            if(strcmp(operador, "=") == 0 &&
               aux->dado.valorN == atof(valor))
                return pos;
        }
        else if(inicio->tipo == 'D')
        {
            if(strcmp(operador, "=") == 0 &&
               strcmp(aux->dado.valorD, valor) == 0)
                return pos;
        }
        else if(inicio->tipo == 'T')
        {
            if(strcmp(operador, "=") == 0 &&
               strcmp(aux->dado.valorT, valor) == 0)
                return pos;
        }
        else if(inicio->tipo == 'C')
        {
            if(strcmp(operador, "=") == 0 &&
               aux->dado.valorC == valor[0])
                return pos;
        }

        aux = aux->prox;
        pos++;
    }

    return -1;
}

valorc *buscar_valor_posicao(campos *inicio, int pos) //Retorna o valor da posicao encontrada
{
    int i = 0;
    valorc *aux = inicio->Pdados;

    while(aux && i < pos)
    {
        aux = aux->prox;
        i++;
    }

    return aux;
}

void parser_where(char *campo, char *operador, char *valor, char *entrada)
{
    int i, j =0;
    char palavra[30];
    for(i=0; entrada[i] != ' '; i++)
    {
        palavra[i] = entrada[i];
    }
    palavra[i] = '\0';
    strcpy(campo, palavra);
    i++;
    while(entrada[i] != ' ')
        palavra[j++] = entrada[i++]; 

    palavra[j] = '\0';
    strcpy(operador, palavra);
    i++;
    j=0;
    while(entrada[i] != '\0')
        valor[j++]= entrada[i++];
    valor[j] = '\0';
}

int compara_valor(campos *campo, valorc *aux, char *operador, char *valor)
{
    int v;

    if(campo->tipo == 'I')
    {
        v = atoi(valor);

        if(strcmp(operador, ">") == 0)
            return aux->dado.valorI > v;
        else if(strcmp(operador, "<") == 0)
            return aux->dado.valorI < v;
        else if(strcmp(operador, ">=") == 0)
            return aux->dado.valorI >= v;
        else if(strcmp(operador, "<=") == 0)
            return aux->dado.valorI <= v;
        else if(strcmp(operador, "!=") == 0 || strcmp(operador, "<>") == 0)
            return aux->dado.valorI != v;
    }

    else if(campo->tipo == 'N')
    {
        float v;

        v = atof(valor);

        if(strcmp(operador, ">") == 0)
            return aux->dado.valorN > v;
        else if(strcmp(operador, "<") == 0)
            return aux->dado.valorN < v;
        else if(strcmp(operador, ">=") == 0)
            return aux->dado.valorN >= v;
        else if(strcmp(operador, "<=") == 0)
            return aux->dado.valorN <= v;
        else if(strcmp(operador, "!=") == 0 || strcmp(operador, "<>") == 0)
            return aux->dado.valorN != v;
    }

    else if(campo->tipo == 'D')
    {
        if(strcmp(operador, ">") == 0)
            return strcmp(aux->dado.valorD, valor) > 0;
        else if(strcmp(operador, "<") == 0)
            return strcmp(aux->dado.valorD, valor) < 0;
        else if(strcmp(operador, ">=") == 0)
            return strcmp(aux->dado.valorD, valor) >= 0;
        else if(strcmp(operador, "<=") == 0)
            return strcmp(aux->dado.valorD, valor) <= 0;
        else if(strcmp(operador, "!=") == 0 || strcmp(operador, "<>") == 0)
            return strcmp(aux->dado.valorD, valor) != 0;
    }

    else if(campo->tipo == 'T')
    {
        if(strcmp(operador, ">") == 0)
            return strcmp(aux->dado.valorT, valor) > 0;
        else if(strcmp(operador, "<") == 0)
            return strcmp(aux->dado.valorT, valor) < 0;
        else if(strcmp(operador, ">=") == 0)
            return strcmp(aux->dado.valorT, valor) >= 0;
        else if(strcmp(operador, "<=") == 0)
            return strcmp(aux->dado.valorT, valor) <= 0;
        else if(strcmp(operador, "!=") == 0 || strcmp(operador, "<>") == 0)
            return strcmp(aux->dado.valorT, valor) != 0;
    }

    else if(campo->tipo == 'C')
    {
        if(strcmp(operador, ">") == 0)
            return aux->dado.valorC > valor[0];
        else if(strcmp(operador, "<") == 0)
            return aux->dado.valorC < valor[0];
        else if(strcmp(operador, ">=") == 0)
            return aux->dado.valorC >= valor[0];
        else if(strcmp(operador, "<=") == 0)
            return aux->dado.valorC <= valor[0];
        else if(strcmp(operador, "!=") == 0 || strcmp(operador, "<>") == 0)
            return aux->dado.valorC != valor[0];
    }

    return 0;
}

void executar_update(tabela *ptab, fila **f1, fila **f2, fila **f3, fila **f4)
{
    char info[50], valor[50];
    char campo_where[30], operador[5], valor_where[30];
    tabela *nt;
    if(!isEmpty(*f1))
    {
        dequeue(f1, info);

        nt = buscar_tabela(ptab, info);

        if(nt)
        {
            campos *campo_w = NULL;

            if(!isEmpty(*f4))
            {
                dequeue(f4, info);

                parser_where(campo_where, operador, valor_where, info);

                campo_w = buscar_campo(nt->pcampos, campo_where);
            }

            if(campo_w)
            {
                while(!isEmpty(*f2) && !isEmpty(*f3))
                {
                    dequeue(f2, info);   // coluna a alterar
                    dequeue(f3, valor);  // valor novo

                    campos *nc = buscar_campo(nt->pcampos, info);

                    if(nc)
                    {
                        /* OPERADOR = */
                        if(strcmp(operador, "=") == 0)
                        {
                            int pos = buscar_posicao(campo_w, operador, valor_where);

                            if(pos != -1)
                            {
                                valorc *alvo = buscar_valor_posicao(nc, pos);

                                if(alvo)
                                {
                                    if(nc->tipo == 'I')
                                        alvo->dado.valorI = atoi(valor);

                                    else if(nc->tipo == 'N')
                                        alvo->dado.valorN = atof(valor);

                                    else if(nc->tipo == 'D')
                                        strcpy(alvo->dado.valorD, valor);

                                    else if(nc->tipo == 'T')
                                        strcpy(alvo->dado.valorT, valor);

                                    else if(nc->tipo == 'C')
                                        alvo->dado.valorC = valor[0];
                                }
                            }
                        }

                        else
                        {
                            valorc *aux_w = campo_w->Pdados;
                            valorc *aux_nc = nc->Pdados;

                            while(aux_w && aux_nc)
                            {
                                if(compara_valor(campo_w, aux_w, operador, valor_where))
                                {
                                    if(nc->tipo == 'I')
                                        aux_nc->dado.valorI = atoi(valor);

                                    else if(nc->tipo == 'N')
                                        aux_nc->dado.valorN = atof(valor);

                                    else if(nc->tipo == 'D')
                                        strcpy(aux_nc->dado.valorD, valor);

                                    else if(nc->tipo == 'T')
                                        strcpy(aux_nc->dado.valorT, valor);

                                    else if(nc->tipo == 'C')
                                        aux_nc->dado.valorC = valor[0];
                                }

                                aux_w = aux_w->prox;
                                aux_nc = aux_nc->prox;
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
Resumo do que falta:

INSERT
└── executar_insert
validar FK
validar PK duplicada

Update
 executar_update()
 localizar registros pelo WHERE
 alterar os valores
 validar tipo
 validar FK se o campo alterado for FK



*/
/*
f1 → usuarios

f2 → nome → idade

f3 → Maria Silva → 30

f4 → id_usuario = 1
*/






/*
DELETE
 executar_delete()
 localizar registro pelo WHERE
 remover corretamente os nós de Pdados
 manter os ponteiros consistentes
 decidir/tratar o que acontece ao tentar excluir um registro referenciado por uma FK


*/
void remover_outros_campos(tabela *nt, campos *campo_w, valorc *valor_w) //O aux_w anda ate achar o valor correspondente a linha, pra apagar tudo
{
    campos *campo;
    valorc *aux_w;
    valorc *aux;

    campo = nt->pcampos;

    while(campo)
    {
        if(campo != campo_w) //Para nao apagar de cara o do campo do where
        {
            aux_w = campo_w->Pdados;
            aux = campo->Pdados;

            while(aux_w && aux && aux_w != valor_w)
            {
                aux_w = aux_w->prox;
                aux = aux->prox;
            }

            if(aux)
                remover_valor_campo(campo, aux);
        }

        campo = campo->prox;
    }
}

void remover_valor_campo(campos *campo, valorc *valor)
{
    valorc *aux;
    valorc *ant;

    aux = campo->Pdados;
    ant = NULL;

    while(aux && aux != valor)
    {
        ant = aux;
        aux = aux->prox;
    }

    if(aux)
    {
        if(ant == NULL)
            campo->Pdados = aux->prox;
        else
            ant->prox = aux->prox;

        free(aux);
    }
}

int valor_igual(campos *campo, valorc *aux, char *valor)
{
    if(campo->tipo == 'I')
        return aux->dado.valorI == atoi(valor);

    else if(campo->tipo == 'N')
        return aux->dado.valorN == atof(valor);

    else if(campo->tipo == 'D')
        return strcmp(aux->dado.valorD, valor) == 0;

    else if(campo->tipo == 'T')
        return strcmp(aux->dado.valorT, valor) == 0;

    else if(campo->tipo == 'C')
        return aux->dado.valorC == valor[0];

    return 0;
}

void executar_delete(tabela *ptabela, fila **f1, fila **f2)
{
    tabela *nt;
    campos *campo_w, *campo;
    valorc *aux_w, *ant_w, *proximo, *aux, *ant;

    char nome_tabela[30], campo_where[30], operador[5], valor[30], where[40];

    nt = campo_w = campo = aux_w = ant_w = proximo = aux = ant = NULL;
    

    if(!isEmpty(*f1))
    {
        dequeue(f1, nome_tabela);

        nt = buscar_tabela(ptabela, nome_tabela);

        if(nt)
        {
            if(!isEmpty(*f2))
            {
                dequeue(f2, where);

                parser_where(campo_where, operador, valor, where);

                campo_w = buscar_campo(nt->pcampos, campo_where);
            }

            if(campo_w)
            {
                aux_w = campo_w->Pdados;

                while(aux_w)
                {
                    proximo = aux_w->prox;

                    if(strcmp(operador, "=") == 0)
                    {
                        if(valor_igual(campo_w, aux_w, valor))
                        {
                            remover_outros_campos(nt, campo_w, aux_w);

                            remover_valor_campo(campo_w, aux_w);
                        }
                    }
                    else
                    {
                        if(compara_valor(campo_w, aux_w, operador, valor))
                        {
                            remover_outros_campos(nt, campo_w, aux_w);

                            remover_valor_campo(campo_w, aux_w);
                        }
                    }

                    aux_w = proximo;
                }
            }
        }
    }
}



/*
SELECT
 executar_select()
 SELECT *
 selecionar colunas específicas
 WHERE
 BETWEEN
 JOIN usando PK/FK
*/


