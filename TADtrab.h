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
    char info[100];
    struct filap *prox;
};typedef struct filap fila;


valorc *buscar_valor_linha(campos *campo, campos *campo_base,valorc *linha);

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

void init(fila **f)
{
    *f = NULL;
}

void limpar_fila(fila **f)
{
    fila *aux;

    while(*f)
    {
        aux = *f;
        *f = (*f)->prox;
        free(aux);
    }
}

void limpar_filas(fila **f1, fila **f2, fila **f3, fila **f4)
{
    limpar_fila(f1);
    limpar_fila(f2);
    limpar_fila(f3);
    limpar_fila(f4);
}

void limpar_banco(pondb **pdb)
{
    tabela *tb, *prox_tb;
    campos *campo, *prox_campo;
    valorc *valor, *prox_valor;

    if(*pdb)
    {
        tb = (*pdb)->pbanco->ptabelas;

        while(tb)
        {
            prox_tb = tb->prox;
            campo = tb->pcampos;

            while(campo)
            {
                prox_campo = campo->prox;
                valor = campo->Pdados;

                while(valor)
                {
                    prox_valor = valor->prox;
                    free(valor);
                    valor = prox_valor;
                }

                free(campo);
                campo = prox_campo;
            }

            free(tb);
            tb = prox_tb;
        }

        free((*pdb)->pbanco);
        free(*pdb);
        *pdb = NULL;
    }
}


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
        if(campo->Patual == aux)
            campo->Patual = aux->prox;

        if(ant == NULL)
            campo->Pdados = aux->prox;
        else
            ant->prox = aux->prox;

        free(aux);
    }
}

void remover_outros_campos(tabela *nt, campos *campo_w, valorc *valor_w) 
{
    campos *campo;
    valorc *aux_w;
    valorc *aux;

    campo = nt->pcampos;

    while(campo)
    {
        if(campo != campo_w) 
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

int contar_pk(campos *inicio)
{
    int qtd = 0;

    while(inicio)
    {
        if(inicio->pk == 'S')
            qtd++;

        inicio = inicio->prox;
    }

    return qtd;
}

char verificar_pk(campos *campo, char valor[])
{
    valorc *aux;
    int achou = 0;

    aux = campo->Pdados;

    while(aux && !achou)
    {
        if(valor_igual(campo, aux, valor))
            achou = 1;

        aux = aux->prox;
    }

    if(achou)
        return 0;

    return 1;
}



char verificar_fk(campos *campo, char valor[])
{
    valorc *aux;
    int achou = 0;

    if(campo->fk == NULL)
        achou = 1;
    else
    {
        aux = campo->fk->Pdados;

        while(aux && !achou)
        {
            if(valor_igual(campo->fk, aux, valor))
                achou = 1;

            aux = aux->prox;
        }
    }

    if(achou)
        return 1;

    return 0;
}



char verificar_fk_delete(tabela *ptab, campos *campo, valorc *valor)
{
    tabela *tb;
    campos *campo_fk;
    valorc *aux;
    char encontrou;

    encontrou = 0;
    tb = ptab;

    while(tb && !encontrou)
    {
        campo_fk = tb->pcampos;

        while(campo_fk && !encontrou)
        {
            if(campo_fk->fk == campo)
            {
                aux = campo_fk->Pdados;

                while(aux && !encontrou)
                {
                    if(valores_iguais_join(campo_fk, aux, campo, valor))
                        encontrou = 1;

                    aux = aux->prox;
                }
            }

            campo_fk = campo_fk->prox;
        }

        tb = tb->prox;
    }

    if(encontrou)
        return 0;

    return 1;
}

char verificar_pk_update(campos *campo, valorc *atual, char valor[])
{
    valorc *aux;
    int achou;

    achou = 0;
    aux = campo->Pdados;

    while(aux && !achou)
    {
        if(aux != atual)
        {
            if(valor_igual(campo, aux, valor))
                achou = 1;
        }

        aux = aux->prox;
    }

    if(achou)
        return 0;

    return 1;
}

int tipo_valido(char tipo)
{
    return tipo == 'I' || tipo == 'N' || tipo == 'D' || tipo == 'C' || tipo == 'T';
}

void imprimir_banco(pondb *banco)
{
    if(!banco)
        printf("Banco nao existente!\n");
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

int valores_iguais(campos *campo, valorc *valor1, valorc *valor2)
{
    if(campo->tipo == 'I')
        return valor1->dado.valorI == valor2->dado.valorI;

    else if(campo->tipo == 'N')
        return valor1->dado.valorN == valor2->dado.valorN;

    else if(campo->tipo == 'D')
        return strcmp(valor1->dado.valorD, valor2->dado.valorD) == 0;

    else if(campo->tipo == 'T')
        return strcmp(valor1->dado.valorT, valor2->dado.valorT) == 0;

    else if(campo->tipo == 'C')
        return valor1->dado.valorC == valor2->dado.valorC;

    return 0;
}

int valores_iguais_join(campos *campo1, valorc *valor1, campos *campo2, valorc *valor2)
{
    int resultado = 0;

    if(campo1->tipo == 'I' && campo2->tipo == 'I')
    {
        if(valor1->dado.valorI == valor2->dado.valorI)
            resultado = 1;
    }

    else if(campo1->tipo == 'N' && campo2->tipo == 'N')
    {
        if(valor1->dado.valorN == valor2->dado.valorN)
            resultado = 1;
    }

    else if(campo1->tipo == 'D' && campo2->tipo == 'D')
    {
        if(strcmp(valor1->dado.valorD, valor2->dado.valorD) == 0)
            resultado = 1;
    }

    else if(campo1->tipo == 'T' && campo2->tipo == 'T')
    {
        if(strcmp(valor1->dado.valorT, valor2->dado.valorT) == 0)
            resultado = 1;
    }

    else if(campo1->tipo == 'C' && campo2->tipo == 'C')
    {
        if(valor1->dado.valorC == valor2->dado.valorC)
            resultado = 1;
    }

    return resultado;
}

char verificar_pk_update_composta(tabela *nt, valorc *linha_atual, campos *campo_alterado, char valor[])
{
    campos *campo;
    valorc *linha;
    valorc *valor_linha;
    valorc *valor_atual;
    char igual;

    linha = nt->pcampos->Pdados;

    while(linha)
    {
        if(linha != linha_atual)
        {
            campo = nt->pcampos;
            igual = 1;

            while(campo && igual)
            {
                if(campo->pk == 'S')
                {
                    valor_linha = buscar_valor_linha(campo, nt->pcampos, linha);

                    if(campo == campo_alterado)
                    {
                        if(!valor_linha || !valor_igual(campo, valor_linha, valor))
                            igual = 0;
                    }
                    else
                    {
                        valor_atual = buscar_valor_linha(campo, nt->pcampos, linha_atual);

                        if(!valor_linha || !valor_atual || !valores_iguais(campo, valor_linha, valor_atual))
                            igual = 0;
                    }
                }

                campo = campo->prox;
            }

            if(igual)
                return 0;
        }

        linha = linha->prox;
    }

    return 1;
}


//Buscar uma tabela entre as 4
tabela *buscar_tabela_join(char nome[], tabela *t1, tabela *t2, tabela *t3, tabela *t4)
{
    tabela *resultado = NULL;

    if(t1 && strcmp(t1->nome_tabela, nome) == 0)
        resultado = t1;
    else if(t2 && strcmp(t2->nome_tabela, nome) == 0)
        resultado = t2;
    else if(t3 && strcmp(t3->nome_tabela, nome) == 0)
        resultado = t3;
    else if(t4 && strcmp(t4->nome_tabela, nome) == 0)
        resultado = t4;

    return resultado;
}

//Pegar a linha atual de uma tabela
valorc *buscar_linha_tabela(char nome[], tabela *t1, valorc *linha1, tabela *t2, valorc *linha2, tabela *t3, valorc *linha3, tabela *t4, valorc *linha4)
{
    valorc *linha = NULL;

    if(t1 && strcmp(t1->nome_tabela, nome) == 0)
        linha = linha1;

    else if(t2 && strcmp(t2->nome_tabela, nome) == 0)
        linha = linha2;

    else if(t3 && strcmp(t3->nome_tabela, nome) == 0)
        linha = linha3;

    else if(t4 && strcmp(t4->nome_tabela, nome) == 0)
        linha = linha4;

    return linha;
}

//Buscar o valor daquele campo
valorc *buscar_valor_linha(campos *campo, campos *campo_base, valorc *linha)
{
    valorc *aux, *base, *resultado;

    aux = campo->Pdados;
    base = campo_base->Pdados;
    resultado = NULL;

    while(aux && base && base != linha)
    {
        aux = aux->prox;
        base = base->prox;
    }

    if(base == linha)
        resultado = aux;

    return resultado;
}






