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

void pula_espacos(char entrada[], int *i);
void ler_palavra(char entrada[], int *i, char destino[]);
int valor_igual(campos *campo, valorc *aux, char *valor);
char verificar_fk_delete(tabela *ptab, campos *campo, valorc *valor);
int verifica_where(campos *campo_w, valorc *valor_w, char entrada[]);
void imprimir_valor(campos *campo, valorc *valor);
valorc *buscar_valor_linha(campos *campo, campos *campo_base,valorc *linha);
void remover_valor_campo(campos *campo, valorc *valor);
int valores_iguais_join(campos *campo1, valorc *valor1, campos *campo2, valorc *valor2);

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


/*
*/
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

char buscar_valor_fila(fila *f2, fila *f3, char nome_campo[], char valor[])
{
    int achou=0;
    while(f2 && f3)
    {
        if(strcmp(f2->info, nome_campo) == 0)
        {
            strcpy(valor, f3->info);
            achou=1;
        }

        f2 = f2->prox;
        f3 = f3->prox;
    }

    if(achou)
        return 1;
    return 0;
}

char verificar_pk_composta(tabela *nt, fila *f2, fila *f3)
{
    campos *campo;
    valorc *linha;
    valorc *valor_linha;
    char valor_insert[50];
    char igual;

    linha = nt->pcampos->Pdados;

    while(linha)
    {
        campo = nt->pcampos;
        igual = 1;

        while(campo && igual)
        {
            if(campo->pk == 'S')
            {
                if(!buscar_valor_fila(f2, f3, campo->campo, valor_insert))
                    igual = 0;
                else
                {
                    valor_linha = buscar_valor_linha(campo, nt->pcampos, linha);

                    if(!valor_linha || !valor_igual(campo, valor_linha, valor_insert))
                        igual = 0;
                }
            }

            campo = campo->prox;
        }

        if(igual)
            return 0;

        linha = linha->prox;
    }

    return 1;
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

void executar_insert(tabela *ptab, fila **f1, fila **f2, fila **f3)
{
    char info[20];
    tabela *nt;
    campos *nc;
    valorc *novo, *aux;
    fila *aux2, *aux3;
    int valido = 1;
    int qtd_pk;

    if(!isEmpty(*f1))
    {
        dequeue(f1, info);

        nt = buscar_tabela(ptab, info);

        if(nt)
        {
            campos *coluna = nt->pcampos;

            aux2 = *f2;
            aux3 = *f3;

            while(aux2 && aux3 && valido)
            {
                nc = buscar_campo(coluna, aux2->info);

                if(nc)
                {
                    aux = NULL;
                    qtd_pk = contar_pk(coluna);

                    if(nc->pk == 'S' && qtd_pk == 1)
                    {
                        if(!verificar_pk(nc, aux3->info))
                        {
                            printf("Erro: valor de PK ja existe!\n");
                            valido = 0;
                        }
                    }
                    

                    if(valido && !verificar_fk(nc, aux3->info))
                    {
                        printf("Erro: valor de FK nao existe!\n");
                        valido = 0;
                    }
                }

                aux2 = aux2->prox;
                aux3 = aux3->prox;
            }

            if(valido && contar_pk(coluna) > 1)
            {
                if(!verificar_pk_composta(nt, *f2, *f3))
                {
                    printf("Erro: chave primaria composta ja existe!\n");
                    valido = 0;
                }
            }

            if(valido)
            {
                while(!isEmpty(*f2) && !isEmpty(*f3))
                {
                    dequeue(f2, info);

                    nc = buscar_campo(coluna, info);

                    if(nc)
                    {
                        dequeue(f3, info);

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
}

void parser_where(char *campo, char *operador, char *valor, char *entrada)
{
    int i = 0, j = 0;
    char palavra[30];

    pula_espacos(entrada, &i);

    j = 0;
    while(entrada[i] != ' ' && entrada[i] != '\0')
        palavra[j++] = entrada[i++];

    palavra[j] = '\0';
    strcpy(campo, palavra);

    pula_espacos(entrada, &i);

    j = 0;
    while(entrada[i] != ' ' && entrada[i] != '\0')
        palavra[j++] = entrada[i++];

    palavra[j] = '\0';
    strcpy(operador, palavra);

    pula_espacos(entrada, &i);

    j = 0;

    if(entrada[i] == 39)
    {
        i++;

        while(entrada[i] != 39 && entrada[i] != '\0')
            valor[j++] = entrada[i++];

        valor[j] = '\0';

        if(entrada[i] == 39)
            i++;
    }
    else
    {
        while(entrada[i] != '\0')
            valor[j++] = entrada[i++];

        valor[j] = '\0';
    }
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

void executar_update(tabela *ptab, fila **f1, fila **f2, fila **f3, fila **f4)
{
    char info[50], valor[50], where[100];
    char campo_where[30], operador[10], valor_where[30];
    int valido;
    int qtd_pk;
    tabela *nt;
    campos *campo_w, *nc;
    valorc *aux_w, *aux_nc;
    valorc *linha_atual;

    if(!isEmpty(*f1))
    {
        dequeue(f1, info);

        nt = buscar_tabela(ptab, info);

        if(nt)
        {
            campo_w = NULL;

            if(!isEmpty(*f4))
            {
                dequeue(f4, where);

                parser_where(campo_where, operador, valor_where, where);

                campo_w = buscar_campo(nt->pcampos, campo_where);
            }

            if(campo_w)
            {
                while(!isEmpty(*f2) && !isEmpty(*f3))
                {
                    dequeue(f2, info);
                    dequeue(f3, valor);

                    nc = buscar_campo(nt->pcampos, info);

                    if(nc)
                    {
                        aux_w = campo_w->Pdados;
                        aux_nc = nc->Pdados;
                        linha_atual = nt->pcampos->Pdados;

                        while(aux_w && aux_nc && linha_atual)
                        {
                            if(verifica_where(campo_w, aux_w, where))
                            {
                                valido = 1;
                                qtd_pk = contar_pk(nt->pcampos);

                                if(nc->pk == 'S' && !valor_igual(nc, aux_nc, valor))
                                {
                                    if(!verificar_fk_delete(ptab, nc, aux_nc))
                                    {
                                        printf("Erro: PK possui referencia de FK!\n");
                                        valido = 0;
                                    }
                                }

                                if(valido && nc->pk == 'S')
                                {
                                    if(qtd_pk == 1)
                                    {
                                        if(!verificar_pk_update(nc, aux_nc, valor))
                                        {
                                            printf("Erro: valor de PK ja existe!\n");
                                            valido = 0;
                                        }
                                    }
                                    else if(qtd_pk > 1)
                                    {
                                        if(!verificar_pk_update_composta(nt,
                                                                         linha_atual,
                                                                         nc,
                                                                         valor))
                                        {
                                            printf("Erro: chave primaria composta ja existe!\n");
                                            valido = 0;
                                        }
                                    }
                                }

                                if(valido && !verificar_fk(nc, valor))
                                {
                                    printf("Erro: valor de FK nao existe!\n");
                                    valido = 0;
                                }

                                if(valido)
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
                            }

                            aux_w = aux_w->prox;
                            aux_nc = aux_nc->prox;
                            linha_atual = linha_atual->prox;
                        }
                    }
                }
            }
        }
    }
}

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
        if(campo->Patual == aux)
            campo->Patual = aux->prox;

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


void executar_delete(tabela *ptabela, fila **f1, fila **f2)
{
    tabela *nt;
    campos *campo_w;
    valorc *aux_w;
    valorc *proximo;

    char nome_tabela[30], campo_where[30], operador[5], valor[30], where[40];

    nt = NULL;
    campo_w = NULL;
    aux_w = NULL;
    proximo = NULL;

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
                            if(verificar_fk_delete(ptabela, campo_w, aux_w))
                            {
                                remover_outros_campos(nt, campo_w, aux_w);

                                remover_valor_campo(campo_w, aux_w);
                            }
                            else
                                printf("Erro: registro possui referencia de FK!\n");
                        }
                    }
                    else
                    {
                        if(compara_valor(campo_w, aux_w, operador, valor))
                        {
                            if(verificar_fk_delete(ptabela, campo_w, aux_w))
                            {
                                remover_outros_campos(nt, campo_w, aux_w);

                                remover_valor_campo(campo_w, aux_w);
                            }
                            else
                                printf("Erro: registro possui referencia de FK!\n");
                        }
                    }

                    aux_w = proximo;
                }
            }
        }
    }
}
void cor_ciano(void)
{
    textcolor(CYAN);
}

void cor_padrao(void)
{
    textcolor(LIGHTGRAY);
}

void imprimir_borda(int n)
{
    int j, k;

    for(j = 0; j < n; j++)
    {
        printf("+");

        for(k = 0; k < 27; k++)
            printf("-");
    }

    printf("+\n");
}



int linha_atende_where(tabela *nt, fila *condicoes, valorc *linha)
{
    int resultado = 1;
    fila *condicao;
    char campo_where[30];
    int i;
    campos *campo_w;
    valorc *v;

    condicao = condicoes;

    while(condicao && resultado)
    {
        i = 0;
        ler_palavra(condicao->info, &i, campo_where);
        campo_w = buscar_campo(nt->pcampos, campo_where);

        if(campo_w)
        {
            v = buscar_valor_linha(campo_w, nt->pcampos, linha);

            if(v)
                resultado = verifica_where(campo_w, v, condicao->info);
            else
                resultado = 0;
        }
        else
            resultado = 0;

        condicao = condicao->prox;
    }

    return resultado;
}

void imprimir_tabela_resultado(tabela *nt, campos *colunas[], int n, fila *condicoes)
{
    int j;
    valorc *ref;
    valorc *valor;

    cor_ciano();

    imprimir_borda(n);


    for(j = 0; j < n; j++)
        printf(" %-25s |", colunas[j]->campo);

    printf("\n");

    imprimir_borda(n);

    ref = nt->pcampos->Pdados;

    while(ref)
    {
        if(linha_atende_where(nt, condicoes, ref))
        {
            printf("|");

            for(j = 0; j < n; j++)
            {
                valor = buscar_valor_linha(colunas[j], nt->pcampos, ref);

                if(valor)
                    imprimir_valor(colunas[j], valor);
            }

            printf("\n");
        }

        ref = ref->prox;
    }

    imprimir_borda(n);

    cor_padrao();
}
/*f1 → colunas que o usuário pediu
f2 → tabela do FROM
f3 → condição do WHERE
*/

int verifica_between(campos *campo, valorc *valor, char valor1[], char valor2[])
{
    int v1, v2; 
    float n1, n2;
    if(campo->tipo == 'I')
    {
        v1 = atoi(valor1);
        v2 = atoi(valor2);

        return valor->dado.valorI >= v1 && valor->dado.valorI <= v2;
    }

    else if(campo->tipo == 'N')
    {
        n1 = atof(valor1);
        n2 = atof(valor2);

        return valor->dado.valorN >= n1 && valor->dado.valorN <= n2;
    }

    else if(campo->tipo == 'D')
    {
        return strcmp(valor->dado.valorD, valor1) >= 0 && strcmp(valor->dado.valorD, valor2) <= 0;
    }

    else if(campo->tipo == 'T')
    {
        return strcmp(valor->dado.valorT, valor1) >= 0 && strcmp(valor->dado.valorT, valor2) <= 0;
    }

    else if(campo->tipo == 'C')
    {
        return valor->dado.valorC >= valor1[0] && valor->dado.valorC <= valor2[0];
    }
    return 0;
}

int verifica_where(campos *campo_w, valorc *valor_w, char entrada[])
{
    int i = 0, resultado = 1;
    int j;
    char campo[30], operador[10], valor1[30], valor2[30], palavra[20];

    while(entrada[i] != '\0' && entrada[i] != ';' && resultado)
    {
        pula_espacos(entrada, &i);
        ler_palavra(entrada, &i, campo);

        pula_espacos(entrada, &i);
        ler_palavra(entrada, &i, operador);

        pula_espacos(entrada, &i);

        if(strcmp(operador, "BETWEEN") == 0 || strcmp(operador, "between") == 0)
        {
            j = 0;

            if(entrada[i] == 39)
            {
                i++;

                while(entrada[i] != 39 && entrada[i] != '\0')
                    valor1[j++] = entrada[i++];

                valor1[j] = '\0';

                if(entrada[i] == 39)
                    i++;
            }
            else
                ler_palavra(entrada, &i, valor1);

            pula_espacos(entrada, &i);
            ler_palavra(entrada, &i, palavra);

            pula_espacos(entrada, &i);

            j = 0;

            if(entrada[i] == 39)
            {
                i++;

                while(entrada[i] != 39 && entrada[i] != '\0')
                    valor2[j++] = entrada[i++];

                valor2[j] = '\0';

                if(entrada[i] == 39)
                    i++;
            }
            else
                ler_palavra(entrada, &i, valor2);

            if(strcmp(palavra, "AND") == 0 || strcmp(palavra, "and") == 0)
                resultado = verifica_between(campo_w, valor_w, valor1, valor2);
            else
                resultado = 0;
        }
        else
        {
            j = 0;

            if(entrada[i] == 39)
            {
                i++;

                while(entrada[i] != 39 && entrada[i] != '\0')
                    valor1[j++] = entrada[i++];

                valor1[j] = '\0';

                if(entrada[i] == 39)
                    i++;
            }
            else
                ler_palavra(entrada, &i, valor1);

            if(strcmp(operador, "=") == 0)
                resultado = valor_igual(campo_w, valor_w, valor1);
            else
                resultado = compara_valor(campo_w, valor_w, operador, valor1);
        }

        pula_espacos(entrada, &i);

        if(entrada[i] != '\0' && entrada[i] != ';' && resultado)
        {
            ler_palavra(entrada, &i, palavra);

            if(strcmp(palavra, "AND") != 0 && strcmp(palavra, "and") != 0)
                resultado = 0;
        }
    }

    return resultado;
}

void separar_campo_join(char entrada[], char nome_tabela[], char nome_campo[])
{
    int i = 0, j = 0;

    while(entrada[i] != '.' && entrada[i] != '\0')
    {
        nome_tabela[j++] = entrada[i++];
    }

    nome_tabela[j] = '\0';

    if(entrada[i] == '.')
        i++;

    j = 0;

    while(entrada[i] != '\0')
    {
        nome_campo[j++] = entrada[i++];
    }

    nome_campo[j] = '\0';
}

void parser_condicao_join(char entrada[], char tabela1[], char campo1[], char operador[], char tabela2[], char campo2[])
{
    int i = 0;
    char esquerda[50], direita[50];

    ler_palavra(entrada, &i, esquerda);
    pula_espacos(entrada, &i);
    ler_palavra(entrada, &i, operador);
    pula_espacos(entrada, &i);
    ler_palavra(entrada, &i, direita);

    separar_campo_join(esquerda, tabela1, campo1);
    separar_campo_join(direita, tabela2, campo2);
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

//Comparar os valores do join
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

void imprimir_valor(campos *campo, valorc *valor)
{
    if(campo->tipo == 'I')
        printf("| %-25d ", valor->dado.valorI);

    else if(campo->tipo == 'N')
        printf("| %-25.2f ", valor->dado.valorN);

    else if(campo->tipo == 'D')
        printf("| %-25s ", valor->dado.valorD);

    else if(campo->tipo == 'T')
        printf("| %-25s ", valor->dado.valorT);

    else if(campo->tipo == 'C')
        printf("| %-25c ", valor->dado.valorC);
}

void imprimir_tabela_join(tabela *t, valorc *linha)
{
    campos *campo;
    valorc *valor;

    campo = t->pcampos;

    while(campo)
    {
        valor = buscar_valor_linha(campo, t->pcampos, linha);

        if(valor)
            imprimir_valor(campo, valor);

        campo = campo->prox;
    }
}

//Verificar uma condicao do join
int verifica_condicao_join(char entrada[],
                           tabela *t1, valorc *linha1,
                           tabela *t2, valorc *linha2,
                           tabela *t3, valorc *linha3,
                           tabela *t4, valorc *linha4)
{
    int resultado = 0;
    char tabela1[30], campo1[30], operador[10];
    char tabela2[30], campo2[30];
    tabela *tb1, *tb2;
    campos *cp1, *cp2;
    valorc *ln1, *ln2;
    valorc *valor1, *valor2;

    parser_condicao_join(entrada,
                         tabela1, campo1, operador,
                         tabela2, campo2);

    tb1 = buscar_tabela_join(tabela1, t1, t2, t3, t4);
    tb2 = buscar_tabela_join(tabela2, t1, t2, t3, t4);

    if(tb1 && tb2)
    {
        cp1 = buscar_campo(tb1->pcampos, campo1);
        cp2 = buscar_campo(tb2->pcampos, campo2);

        ln1 = buscar_linha_tabela(tabela1,
                                   t1, linha1,
                                   t2, linha2,
                                   t3, linha3,
                                   t4, linha4);

        ln2 = buscar_linha_tabela(tabela2,
                                   t1, linha1,
                                   t2, linha2,
                                   t3, linha3,
                                   t4, linha4);

        if(cp1 && cp2 && ln1 && ln2)
        {
            valor1 = buscar_valor_linha(cp1, tb1->pcampos, ln1);
            valor2 = buscar_valor_linha(cp2, tb2->pcampos, ln2);

            if(valor1 && valor2)
            {
                if(strcmp(operador, "=") == 0)
                    resultado = valores_iguais_join(cp1, valor1, cp2, valor2);
            }
        }
    }

    return resultado;
}

//Verificar todas as condicoes de f3
int verifica_condicoes_join(fila *f3, tabela *t1, valorc *linha1, tabela *t2, valorc *linha2, tabela *t3, valorc *linha3, tabela *t4, valorc *linha4)
{
    int resultado = 1;
    char condicao[100];
    fila *aux;

    aux = f3;

    while(!isEmpty(aux) && resultado)
    {
        strcpy(condicao, aux->info);

        resultado = verifica_condicao_join(condicao, t1, linha1, t2, linha2, t3, linha3, t4, linha4);

        aux = aux->prox;
    }

    return resultado;
}

void imprimir_campo_join(char entrada[], tabela *t1, valorc *linha1, tabela *t2, valorc *linha2, tabela *t3, valorc *linha3, tabela *t4, valorc *linha4)
{
    char nome_tabela[30], nome_campo[30];
    tabela *t;
    campos *campo;
    valorc *linha, *valor;

    separar_campo_join(entrada, nome_tabela, nome_campo);

    t = buscar_tabela_join(nome_tabela, t1, t2, t3, t4);

    if(t)
    {
        campo = buscar_campo(t->pcampos, nome_campo);

        linha = buscar_linha_tabela(nome_tabela,
                                    t1, linha1,
                                    t2, linha2,
                                    t3, linha3,
                                    t4, linha4);

        if(campo && linha)
        {
            valor = buscar_valor_linha(campo, t->pcampos, linha);

            if(valor)
                imprimir_valor(campo, valor);
        }
    }
}

void dequeue_select(fila **f, char info[])
{
    if(!isEmpty(*f))
    {
        strcpy(info, (*f)->info);
        *f = (*f)->prox;
    }
}


int contar_colunas_join(fila *f1, tabela *t1, tabela *t2, tabela *t3, tabela *t4)
{
    int n = 0;
    fila *aux_f1;
    campos *campo;

    if(f1 && strcmp(f1->info, "*") == 0)
    {
        if(t1)
        {
            campo = t1->pcampos;
            while(campo)
            {
                n++;
                campo = campo->prox;
            }
        }

        if(t2)
        {
            campo = t2->pcampos;
            while(campo)
            {
                n++;
                campo = campo->prox;
            }
        }

        if(t3)
        {
            campo = t3->pcampos;
            while(campo)
            {
                n++;
                campo = campo->prox;
            }
        }

        if(t4)
        {
            campo = t4->pcampos;
            while(campo)
            {
                n++;
                campo = campo->prox;
            }
        }
    }
    else
    {
        aux_f1 = f1;
        while(aux_f1)
        {
            n++;
            aux_f1 = aux_f1->prox;
        }
    }

    return n;
}

void imprimir_borda_join(int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        printf("+");
        for(j = 0; j < 27; j++)
            printf("-");
    }

    printf("+\n");
}

void imprimir_cabecalho_join(fila *f1, tabela *t1, tabela *t2, tabela *t3, tabela *t4)
{
    fila *aux_f1;
    campos *campo;

    imprimir_borda_join(contar_colunas_join(f1, t1, t2, t3, t4));
    printf("|");

    if(f1 && strcmp(f1->info, "*") == 0)
    {
        if(t1)
        {
            campo = t1->pcampos;
            while(campo)
            {
                printf(" %-25s |", campo->campo);
                campo = campo->prox;
            }
        }

        if(t2)
        {
            campo = t2->pcampos;
            while(campo)
            {
                printf(" %-25s |", campo->campo);
                campo = campo->prox;
            }
        }

        if(t3)
        {
            campo = t3->pcampos;
            while(campo)
            {
                printf(" %-25s |", campo->campo);
                campo = campo->prox;
            }
        }

        if(t4)
        {
            campo = t4->pcampos;
            while(campo)
            {
                printf(" %-25s |", campo->campo);
                campo = campo->prox;
            }
        }
    }
    else
    {
        aux_f1 = f1;
        while(aux_f1)
        {
            printf(" %-25s |", aux_f1->info);
            aux_f1 = aux_f1->prox;
        }
    }

    printf("\n");
    imprimir_borda_join(contar_colunas_join(f1, t1, t2, t3, t4));
}

void executar_select_join(tabela *ptab, fila *f1, fila *f2, fila *f3)
{
    char info[100];
    tabela *t1, *t2, *t3, *t4;
    campos *base1, *base2, *base3, *base4;
    valorc *linha1, *linha2, *linha3, *linha4;
    fila *aux_f1;

    t1 = t2 = t3 = t4 = NULL;

    base1 = base2 = base3 = base4 = NULL;
    linha1 = linha2 = linha3 = linha4 = NULL;

    if(!isEmpty(f2))
    {
        dequeue_select(&f2, info);
        t1 = buscar_tabela(ptab, info);
    }

    if(!isEmpty(f2))
    {
        dequeue_select(&f2, info);
        t2 = buscar_tabela(ptab, info);
    }

    if(!isEmpty(f2))
    {
        dequeue_select(&f2, info);
        t3 = buscar_tabela(ptab, info);
    }

    if(!isEmpty(f2))
    {
        dequeue_select(&f2, info);
        t4 = buscar_tabela(ptab, info);
    }

    if(t1)
        base1 = t1->pcampos;

    if(t2)
        base2 = t2->pcampos;

    if(t3)
        base3 = t3->pcampos;

    if(t4)
        base4 = t4->pcampos;

    if(t1 && t2)
        imprimir_cabecalho_join(f1, t1, t2, t3, t4);

    /* JOIN com 2 tabelas */
    if(t1 && t2 && !t3)
    {
        linha1 = base1->Pdados;

        while(linha1)
        {
            linha2 = base2->Pdados;

            while(linha2)
            {
                if(verifica_condicoes_join(f3, t1, linha1, t2, linha2, NULL, NULL, NULL, NULL))
                {
                    aux_f1 = f1;

                    while(!isEmpty(aux_f1))
                    {
                        if(strcmp(aux_f1->info, "*") == 0)
                        {
                            imprimir_tabela_join(t1, linha1);
                            imprimir_tabela_join(t2, linha2);
                            aux_f1 = NULL;
                        }
                        else
                        {
                            imprimir_campo_join(aux_f1->info,
                                                t1, linha1,
                                                t2, linha2,
                                                NULL, NULL,
                                                NULL, NULL);

                            aux_f1 = aux_f1->prox;
                        }
                    }

                    printf("|\n");
                }

                linha2 = linha2->prox;
            }

            linha1 = linha1->prox;
        }
    }

    /* JOIN com 3 tabelas */
    else if(t1 && t2 && t3 && !t4)
    {
        linha1 = base1->Pdados;

        while(linha1)
        {
            linha2 = base2->Pdados;

            while(linha2)
            {
                linha3 = base3->Pdados;

                while(linha3)
                {
                    if(verifica_condicoes_join(f3,
                                               t1, linha1,
                                               t2, linha2,
                                               t3, linha3,
                                               NULL, NULL))
                    {
                        aux_f1 = f1;

                        while(!isEmpty(aux_f1))
                        {
                            if(strcmp(aux_f1->info, "*") == 0)
                            {
                                imprimir_tabela_join(t1, linha1);
                                imprimir_tabela_join(t2, linha2);
                                imprimir_tabela_join(t3, linha3);
                                aux_f1 = NULL;
                            }
                            else
                            {
                                imprimir_campo_join(aux_f1->info, t1, linha1, t2, linha2, t3, linha3, NULL, NULL);

                                aux_f1 = aux_f1->prox;
                            }
                        }

                        printf("|\n");
                    }

                    linha3 = linha3->prox;
                }

                linha2 = linha2->prox;
            }

            linha1 = linha1->prox;
        }
    }

    /* JOIN com 4 tabelas */
    else if(t1 && t2 && t3 && t4)
    {
        linha1 = base1->Pdados;

        while(linha1)
        {
            linha2 = base2->Pdados;

            while(linha2)
            {
                linha3 = base3->Pdados;

                while(linha3)
                {
                    linha4 = base4->Pdados;

                    while(linha4)
                    {
                        if(verifica_condicoes_join(f3, t1, linha1, t2, linha2, t3, linha3, t4, linha4))
                        {
                            aux_f1 = f1;

                            while(!isEmpty(aux_f1))
                            {
                                if(strcmp(aux_f1->info, "*") == 0)
                                {
                                    imprimir_tabela_join(t1, linha1);
                                    imprimir_tabela_join(t2, linha2);
                                    imprimir_tabela_join(t3, linha3);
                                    imprimir_tabela_join(t4, linha4);

                                    aux_f1 = NULL;
                                }
                                else
                                {
                                    imprimir_campo_join(aux_f1->info, t1, linha1, t2, linha2, t3, linha3, t4, linha4);

                                    aux_f1 = aux_f1->prox;
                                }
                            }

                            printf("|\n");
                        }

                        linha4 = linha4->prox;
                    }

                    linha3 = linha3->prox;
                }

                linha2 = linha2->prox;
            }

            linha1 = linha1->prox;
        }
    }

    if(t1 && t2)
        imprimir_borda_join(contar_colunas_join(f1, t1, t2, t3, t4));
}



void executar_select_simples(tabela *ptab, fila *f1, fila *f2, fila *f3)
{
    char info[100];
    int n;
    tabela *nt;
    campos *aux;
    campos *colunas[30];

    nt = NULL;
    n = 0;

    if(!isEmpty(f2))
    {
        dequeue_select(&f2, info);

        nt = buscar_tabela(ptab, info);

        if(nt)
        {
            while(!isEmpty(f1) && n < 30)
            {
                dequeue_select(&f1, info);

                if(strcmp(info, "*") == 0)
                {
                    aux = nt->pcampos;

                    while(aux && n < 30)
                    {
                        colunas[n++] = aux;
                        aux = aux->prox;
                    }
                }
                else
                {
                    aux = buscar_campo(nt->pcampos, info);

                    if(aux)
                        colunas[n++] = aux;
                }
            }

            if(n > 0)
                imprimir_tabela_resultado(nt, colunas, n, f3);
        }
    }
}

void executar_select(tabela *ptab, fila *f1, fila *f2, fila *f3)
{
    if(f2 && f2->prox)
        executar_select_join(ptab, f1, f2, f3);
    else
        executar_select_simples(ptab, f1, f2, f3);
}

