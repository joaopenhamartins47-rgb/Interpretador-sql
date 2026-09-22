#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "TADtrab.h"


char verificar_pk_composta(tabela *nt, fila *f2, fila *f3);
void ler_palavra(char *entrada, int *i, char *destino);
char buscar_valor_fila(fila *f2, fila *f3, char nome_campo[], char valor[]);
void parser_where(char *campo, char *operador, char *valor, char *entrada);
int verifica_where(campos *campo_w, valorc *valor_w, char entrada[]);
int compara_valor(campos *campo, valorc *aux, char *operador, char *valor);
void separar_campo_join(char entrada[], char nome_tabela[], char nome_campo[]);
tabela *buscar_tabela_join(char nome[], tabela *t1, tabela *t2, tabela *t3, tabela *t4);
valorc *buscar_linha_tabela(char nome[], tabela *t1, valorc *linha1, tabela *t2, valorc *linha2, tabela *t3, valorc *linha3, tabela *t4, valorc *linha4);
void dequeue_select(fila **f, char info[]);
void imprimir_tabela_resultado(tabela *nt, campos *colunas[], int n, fila *condicoes);
int verifica_between(campos *campo, valorc *valor, char valor1[], char valor2[]);


int parser_comando(char entrada[], char *comando)
{
    int i;
    for(i=0; entrada[i] != ' ' && entrada[i] != '\0' && i < 29; i++)
    {
        comando[i] = entrada[i];
    }
    comando[i] = '\0';
    return i;
}

char isSELECT(char comando[])
{
    return !strcmp(comando, "SELECT") || !strcmp(comando, "select");
}

char isUPDATE(char comando[])
{
    return !strcmp(comando, "UPDATE") || !strcmp(comando, "update");
}

char isDELETE(char comando[])
{
    return !strcmp(comando, "DELETE") || !strcmp(comando, "delete");
}

char isCREATE(char comando[])
{
    return !strcmp(comando, "CREATE") || !strcmp(comando, "create");
}

char isALTER(char comando[])
{
    return !strcmp(comando, "ALTER") || !strcmp(comando, "alter");
}

char isInsert(char comando[])
{
    return !strcmp(comando, "INSERT") || !strcmp(comando, "insert");
}

void pula_from_where(char entrada[], int *i)
{
    while(entrada[*i] != ' ' && entrada[*i] != '\0')
        (*i)++;
}

void pula_espacos(char entrada[], int *i)
{
    while(entrada[*i] == ' ' && entrada[*i] != '\0')
        (*i)++;
}

void dequeue_select(fila **f, char info[])
{
    if(!isEmpty(*f))
    {
        strcpy(info, (*f)->info);
        *f = (*f)->prox;
    }
}

void parser_select(char entrada[], int i, fila **f1, fila **f2, fila **f3)
{
    int col = 0, j = 0, k;
    char palavra[50];
    char campo[50], operador[20], valor1[50], valor2[50];
    char condicao[100];

    while(entrada[i] != '\0')
    {
        /*
         * COLUNAS DO SELECT
         */
        if(col == 0)
        {
            j = 0;
            pula_espacos(entrada, &i);

            while(entrada[i] != ' ' && entrada[i] != ',' && entrada[i] != '\0')
            {
                palavra[j++] = entrada[i++];
            }

            palavra[j] = '\0';
            enqueue(f1, palavra);

            if(entrada[i] == ',')
            {
                i++;
                pula_espacos(entrada, &i);
            }
            else
            {
                pula_espacos(entrada, &i);
                col = 1;
            }
        }

       
        else if(col == 1)
        {
            pula_espacos(entrada, &i);
            pula_from_where(entrada, &i);
            pula_espacos(entrada, &i);

            col = 2;
        }

        
        else if(col == 2)
        {
            j = 0;

            while(entrada[i] != ' ' &&
                  entrada[i] != ',' &&
                  entrada[i] != ';' &&
                  entrada[i] != '\0')
            {
                palavra[j++] = entrada[i++];
            }

            palavra[j] = '\0';
            enqueue(f2, palavra);

            pula_espacos(entrada, &i);

           
            if(entrada[i] == ',')
            {
                i++;
                pula_espacos(entrada, &i);
            }

            
            else if(entrada[i] == 'W' || entrada[i] == 'w')
            {
                pula_from_where(entrada, &i);
                pula_espacos(entrada, &i);
                col = 4;
            }

            else
                col = 5;
        }

       
        else if(col == 4)
        {
            j = 0;
            k = 0;

            pula_espacos(entrada, &i);

            
            ler_palavra(entrada, &i, campo);

            while(campo[j] != '\0')
                condicao[k++] = campo[j++];

            condicao[k++] = ' ';

            pula_espacos(entrada, &i);

            
            j = 0;
            ler_palavra(entrada, &i, operador);

            while(operador[j] != '\0')
                condicao[k++] = operador[j++];

            pula_espacos(entrada, &i);

           
            if(strcmp(operador, "BETWEEN") == 0 ||
               strcmp(operador, "between") == 0)
            {
                condicao[k++] = ' ';

                j = 0;
                ler_palavra(entrada, &i, valor1);

                while(valor1[j] != '\0')
                    condicao[k++] = valor1[j++];

                pula_espacos(entrada, &i);
                condicao[k++] = ' ';

                j = 0;
                ler_palavra(entrada, &i, palavra);

                while(palavra[j] != '\0')
                    condicao[k++] = palavra[j++];

                pula_espacos(entrada, &i);
                condicao[k++] = ' ';

                j = 0;
                ler_palavra(entrada, &i, valor2);

                while(valor2[j] != '\0')
                    condicao[k++] = valor2[j++];

                condicao[k] = '\0';
            }

            else
            {
                condicao[k++] = ' ';

                j = 0;
                ler_palavra(entrada, &i, valor1);

                while(valor1[j] != '\0')
                    condicao[k++] = valor1[j++];

                condicao[k] = '\0';
            }

            
            enqueue(f3, condicao);

            pula_espacos(entrada, &i);

            
            if(entrada[i] != '\0' && entrada[i] != ';')
            {
                ler_palavra(entrada, &i, palavra);

                if(strcmp(palavra, "AND") == 0 || strcmp(palavra, "and") == 0)
                {
                    col = 4;
                }
                else
                    col = 5;
            }
            else
                col = 5;
        }

        else
            i++;
    }
}



void parser_delete(char entrada[], int i, fila **f1, fila **f2)
{
    int j = 0, col=0;
    char palavra[50];
    while(entrada[i] != '\0')
    {
        if(col == 0){
            pula_espacos(entrada,&i);
            pula_from_where(entrada, &i);

            pula_espacos(entrada, &i);

            while(entrada[i] != ' ' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];
            
            palavra[j] = '\0';
            enqueue(&*f1, palavra);
            col=1;
        }
        else if(col == 1)
        {
            pula_espacos(entrada, &i);

            pula_from_where(entrada, &i);

            pula_espacos(entrada, &i);
            j=0;
            while(entrada[i] != ';' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];
            palavra[j] = '\0';
            enqueue(&*f2, palavra);
            col = 3;
        }
        else
            i++;
    }
}


void parser_update(char entrada[], int i, fila **f1, fila **f2, fila **f3, fila **f4)
{
    int j = 0, col = 0;
    char palavra[50];
    //f1 eh a tabela que sera alterada, f2 sao os campos, f3 os valores e f4 where

    while(entrada[i] != '\0')
    {
        if(col == 0)
        {
            pula_espacos(entrada, &i);
            while(entrada[i] != ' ' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];
            palavra[j] = '\0';
            enqueue(&*f1, palavra);

            pula_espacos(entrada, &i);
            pula_from_where(entrada, &i); /* pula o SET */
            pula_espacos(entrada, &i);

            j = 0;
            col = 1;
        }
        else if(col == 1)
        {
            while(entrada[i] != ' ' && entrada[i] != '=' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];

            palavra[j] = '\0';
            enqueue(&*f2, palavra);

            pula_espacos(entrada, &i);

            if(entrada[i] == '=')
                i++;

            pula_espacos(entrada, &i);

            j = 0;

            if(entrada[i] == 39)
            {
                i++;

                while(entrada[i] != 39 && entrada[i] != '\0')
                    palavra[j++] = entrada[i++];

                palavra[j] = '\0';

                if(entrada[i] == 39)
                    i++;
            }
            else
            {
                while(entrada[i] != ' ' && entrada[i] != ',' && entrada[i] != '\0')
                    palavra[j++] = entrada[i++];

                palavra[j] = '\0';
            }

            enqueue(&*f3, palavra);
            pula_espacos(entrada, &i);
            if(entrada[i] == ',')
            {
                i++;
                pula_espacos(entrada, &i);
                j = 0;
            }
            else
                col = 2;
        }
            
        else if(col == 2)
        {
            pula_espacos(entrada, &i);

            if(entrada[i] == 'W' || entrada[i] == 'w')
            {
                pula_from_where(entrada, &i);
                pula_espacos(entrada, &i);
                j = 0;
                col = 3;
            }
            else
            {
                col = 4;
            }
        }
        else if(col == 3)
        {
            while(entrada[i] != ';' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];
            palavra[j] = '\0';
            enqueue(&*f4, palavra);
            col = 4;
        }
        else
            i++;
    }
}


void parser_insert(char entrada[], int i, fila **f1, fila **f2, fila **f3)
{
    int j = 0, col = 0;
    //f1 vai ser a tabela, f2 as colunas e f3 os valores
    char palavra[50];

    while(entrada[i] != '\0')
    {
        if(col == 0)
        {
            pula_espacos(entrada, &i);
            pula_from_where(entrada, &i); 
            pula_espacos(entrada, &i);

            j = 0;

            while(entrada[i] != ' ' && entrada[i] != '(' && entrada[i] != '\0')
            {
                palavra[j++] = entrada[i++];
            }

            palavra[j] = '\0';
            enqueue(&*f1, palavra);

            pula_espacos(entrada, &i);

            if(entrada[i] == '(')
                i++; 

            j = 0;
            col = 1;
        }

        else if(col == 1)
        {
            pula_espacos(entrada, &i);

            j = 0;

            while(entrada[i] != ',' && entrada[i] != ')' && entrada[i] != '\0')
            {
                palavra[j++] = entrada[i++];
            }

            palavra[j] = '\0';
            enqueue(&*f2, palavra);

            if(entrada[i] == ',')
            {
                i++;
            }
            else if(entrada[i] == ')')
            {
                i++; 
                col = 2;
            }
        }

        else if(col == 2)
        {
            pula_espacos(entrada, &i);
            pula_from_where(entrada, &i); /* pula VALUES */
            pula_espacos(entrada, &i);

            if(entrada[i] == '(')
                i++; 

            j = 0;
            col = 3;
        }

        else if(col == 3)
        {
            pula_espacos(entrada, &i);

            j = 0;

            if(entrada[i] == '\'')
            {
                i++;

                while(entrada[i] != '\'' && entrada[i] != '\0')
                {
                    palavra[j++] = entrada[i++];
                }

                palavra[j] = '\0';
                enqueue(&*f3, palavra);

                if(entrada[i] == 39) //aspas
                    i++;
            }
            else
            {
                while(entrada[i] != ',' && entrada[i] != ')' && entrada[i] != '\0')
                {
                    palavra[j++] = entrada[i++];
                }

                palavra[j] = '\0';
                enqueue(&*f3, palavra);
            }
            pula_espacos(entrada, &i);

            if(entrada[i] == ',')
            {
                i++;
            }
            else if(entrada[i] == ')')
            {
                i++;
                col = 4;
            }
        }

        else
        {
            i++;
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
int verifica_condicao_join(char entrada[], tabela *t1, valorc *linha1, tabela *t2, valorc *linha2, tabela *t3, valorc *linha3, tabela *t4, valorc *linha4)
{
    int resultado = 0;
    char tabela1[30], campo1[30], operador[10];
    char tabela2[30], campo2[30];
    tabela *tb1, *tb2;
    campos *cp1, *cp2;
    valorc *ln1, *ln2;
    valorc *valor1, *valor2;

    parser_condicao_join(entrada, tabela1, campo1, operador, tabela2, campo2);

    tb1 = buscar_tabela_join(tabela1, t1, t2, t3, t4);
    tb2 = buscar_tabela_join(tabela2, t1, t2, t3, t4);

    if(tb1 && tb2)
    {
        cp1 = buscar_campo(tb1->pcampos, campo1);
        cp2 = buscar_campo(tb2->pcampos, campo2);

        ln1 = buscar_linha_tabela(tabela1, t1, linha1, t2, linha2, t3, linha3, t4, linha4);

        ln2 = buscar_linha_tabela(tabela2, t1, linha1, t2, linha2, t3, linha3, t4, linha4);

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
                            imprimir_campo_join(aux_f1->info, t1, linha1, t2, linha2, NULL, NULL, NULL, NULL);
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
                    if(verifica_condicoes_join(f3, t1, linha1, t2, linha2, t3, linha3, NULL, NULL))
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

void cor_ciano(void)
{
    textcolor(CYAN);
}

void cor_padrao(void)
{
    textcolor(LIGHTGRAY);
}

void executar_select(tabela *ptab, fila *f1, fila *f2, fila *f3)
{
    if(f2 && f2->prox)
        executar_select_join(ptab, f1, f2, f3);
    else
        executar_select_simples(ptab, f1, f2, f3);
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


char isCreateDatabase(char entrada[], int *i)
{
    pula_espacos(entrada, &*i);
    if(entrada[*i] == 'D' || entrada[*i] == 'd')
        return 1;
    return 0;
}

int compara_palavra(char *a, char *b){
    int i = 0;
    char ca, cb;

    while(a[i] != '\0' && b[i] != '\0'){
        ca = a[i];
        cb = b[i];

        if(ca >= 'a' && ca <= 'z')
            ca = ca - 'a' + 'A';

        if(cb >= 'a' && cb <= 'z')
            cb = cb - 'a' + 'A';

        if(ca != cb)
            return 0;

        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}

void ler_palavra(char *entrada, int *i, char *destino)
{
    int j = 0;

    if(entrada[*i] == 39)
    {
        destino[j++] = entrada[(*i)++];

        while(entrada[*i] != 39 && entrada[*i] != '\0')
            destino[j++] = entrada[(*i)++];

        if(entrada[*i] == 39)
            destino[j++] = entrada[(*i)++];
    }
    else
    {
        while(entrada[*i] != '\0' && entrada[*i] != ' ' && entrada[*i] != '(' && entrada[*i] != ')' && entrada[*i] != ',' && entrada[*i] != ';')
        {
            destino[j++] = entrada[(*i)++];
        }
    }

    destino[j] = '\0';
}

int compara_palavra_inicio(char *entrada, int i, char *ref){
    char palavra[30];

    ler_palavra(entrada, &i, palavra);
    return compara_palavra(palavra, ref);
}

int ler_tipo_campo(char *entrada, int i, char *tipo){
    char palavra[30], tamanho[10];
    int j;

    ler_palavra(entrada, &i, palavra);

    if(compara_palavra(palavra, "INTEGER"))
        *tipo = 'I';
    else if(compara_palavra(palavra, "NUMERIC"))
        *tipo = 'N';
    else if(compara_palavra(palavra, "DATE"))
        *tipo = 'D';
    else
        *tipo = 'T';

    if(entrada[i] == '('){
        i++;
        j = 0;

        while(entrada[i] != ')' && entrada[i] != '\0')
            tamanho[j++] = entrada[i++];

        tamanho[j] = '\0';

        if(entrada[i] == ')')
            i++;

        if(*tipo == 'T' && compara_palavra(tamanho, "1"))
            *tipo = 'C';
    }
    return i;
}

void processar_create_database(char *entrada, int i, pondb **pdb){ //extrair nome banco
    char nome[30];

    pula_espacos(entrada, &i);
    pula_from_where(entrada, &i);
    pula_espacos(entrada, &i);

    ler_palavra(entrada, &i, nome);
    criar_banco(pdb, nome);
}

void processar_create_table(char *entrada, int i, pondb *pdb)
{
    char nome_tabela[30], nome_campo[30], segmento[100], tipo;
    int j, depth, k;
    int fim, fimSegmento;
    tabela *nt;
    campos *nc;

    pula_espacos(entrada, &i);
    pula_from_where(entrada, &i);
    pula_espacos(entrada, &i);

    ler_palavra(entrada, &i, nome_tabela);

    nt = inserir_tabela(&pdb->pbanco->ptabelas, nome_tabela);

    pula_espacos(entrada, &i);

    if(entrada[i] == '(')
        i++;

    fim = 0;

    while(entrada[i] != '\0' && !fim)
    {
        pula_espacos(entrada, &i);

        if(entrada[i] == ')')
        {
            i++;
            fim = 1;
        }
        else
        {
            depth = 0;
            j = 0;
            fimSegmento = 0;

            while(entrada[i] != '\0' && !fimSegmento)
            {
                if(entrada[i] == '(')
                {
                    depth++;
                    segmento[j++] = entrada[i++];
                }
                else if(entrada[i] == ')')
                {
                    if(depth == 0)
                        fimSegmento = 1;
                    else
                    {
                        depth--;
                        segmento[j++] = entrada[i++];
                    }
                }
                else if(entrada[i] == ',' && depth == 0)
                {
                    i++;
                    fimSegmento = 1;
                }
                else
                    segmento[j++] = entrada[i++];
            }

            segmento[j] = '\0';

            k = 0;
            pula_espacos(segmento, &k);

            if(compara_palavra_inicio(segmento, k, "CONSTRAINT"))
            {
                pula_from_where(segmento, &k);
                pula_espacos(segmento, &k);
                pula_from_where(segmento, &k);
                pula_espacos(segmento, &k);
                pula_from_where(segmento, &k);
                pula_espacos(segmento, &k);
                pula_from_where(segmento, &k);
                pula_espacos(segmento, &k);

                if(segmento[k] == '(')
                    k++;

                while(segmento[k] != '\0' && segmento[k] != ')')
                {
                    pula_espacos(segmento, &k);

                    if(segmento[k] == ',')
                    {
                        k++;
                        pula_espacos(segmento, &k);
                    }

                    ler_palavra(segmento, &k, nome_campo);

                    nc = buscar_campo(nt->pcampos, nome_campo);

                    if(nc)
                        nc->pk = 'S';

                    pula_espacos(segmento, &k);
                }
            }
            else
            {
                ler_palavra(segmento, &k, nome_campo);
                pula_espacos(segmento, &k);
                ler_tipo_campo(segmento, k, &tipo);

                inserir_campo(nt, nome_campo, tipo, 'N');
            }
        }
    }
}

void processar_alter_table(char *entrada, int i, pondb *pdb)
{
    char nome_tabela[30], nome_campo[30];
    char nome_tabela_ref[30], nome_campo_ref[30];
    tabela *nt, *nt_ref;
    campos *nc, *nc_ref;

    pula_espacos(entrada, &i);
    pula_from_where(entrada, &i);
    pula_espacos(entrada, &i);

    ler_palavra(entrada, &i, nome_tabela);

    nt = buscar_tabela(pdb->pbanco->ptabelas, nome_tabela);

    pula_espacos(entrada, &i);
    pula_from_where(entrada, &i);
    pula_espacos(entrada, &i);
    pula_from_where(entrada, &i);
    pula_espacos(entrada, &i);
    pula_from_where(entrada, &i);
    pula_espacos(entrada, &i);
    pula_from_where(entrada, &i);
    pula_espacos(entrada, &i);
    pula_from_where(entrada, &i);
    pula_espacos(entrada, &i);

    if(entrada[i] == '(')
        i++;

    ler_palavra(entrada, &i, nome_campo);

    if(entrada[i] == ')')
        i++;

    pula_espacos(entrada, &i);
    pula_from_where(entrada, &i);
    pula_espacos(entrada, &i);

    ler_palavra(entrada, &i, nome_tabela_ref);

    pula_espacos(entrada, &i);

    if(entrada[i] == '(')
        i++;

    ler_palavra(entrada, &i, nome_campo_ref);

    if(nt)
        nc = buscar_campo(nt->pcampos, nome_campo);
    else
        nc = NULL;

    nt_ref = buscar_tabela(pdb->pbanco->ptabelas, nome_tabela_ref);

    if(nt_ref)
        nc_ref = buscar_campo(nt_ref->pcampos, nome_campo_ref);
    else
        nc_ref = NULL;

    if(nc && nc_ref)
        nc->fk = nc_ref;
}

void executar_comando_ddl(char *entrada, pondb **pdb){
    char comando[30];
    int i;
    i = parser_comando(entrada, comando);

    if(isCREATE(comando)){
        pula_espacos(entrada, &i);
        if(isCreateDatabase(entrada, &i))
            processar_create_database(entrada, i, pdb);
        else
            processar_create_table(entrada, i, *pdb);
    }
    else if(isALTER(comando)){
        processar_alter_table(entrada, i, *pdb);
    }
}

void abrir_arquivo_script(FILE *arq, char *caminho, pondb **pdb){
    char statement[1000];
    int j, c, anteriorEspaco;
    if(arq == NULL){
    	printf("[!] Erro ao abrir o arquivo");
    }
    else
    {
    	j = 0;
	    anteriorEspaco = 1;
	    c = fgetc(arq);
	
	    while(c != EOF){
	        if(c == ';'){
	            statement[j] = '\0';
	            if(j > 0)
	                executar_comando_ddl(statement, pdb);
	            j = 0;
	            anteriorEspaco = 1;
	        }
	        else if(c == '\n' || c == '\r' || c == '\t' || c == ' ')
            {
	            if(!anteriorEspaco && j > 0){
	                statement[j++] = ' ';
	                anteriorEspaco = 1;
	            }
	        }
	        else{
	            statement[j++] = (char)c;
	            anteriorEspaco = 0;
	        }
	        c = fgetc(arq);
	    }
	    fclose(arq);	
    }
}



int main(void)
{
    int i;
    char comando[30];
    char entrada[500];
    char caminho[100];
    fila *f1, *f2, *f3, *f4;
    pondb *pdb;

    inicializa_ponteiro_banco(&pdb);
    init(&f1);
    init(&f2);
    init(&f3);
    init(&f4);
    FILE *arq = NULL;

    do
    {
        printf("Digite o nome do arquivo de script (deve estar na pasta do projeto): ");
        gets(caminho);
        arq = fopen(caminho, "r");
        if(arq == NULL)
        {
            printf("Erro ao abrir arquivo, digite novamente!\n");
        }
        else
            abrir_arquivo_script(arq, caminho, &pdb);

    } while (arq == NULL);
    
    

    imprimir_banco(pdb);

    gets(entrada);
    while(strcmp(entrada, "\0") != 0)
    {
        i = parser_comando(entrada, comando);

        if(isCREATE(comando) || isALTER(comando))
        {
            executar_comando_ddl(entrada, &pdb);
        }
        else if(isSELECT(comando))
        {
            parser_select(entrada, i, &f1, &f2, &f3);
            executar_select(pdb->pbanco->ptabelas, f1, f2, f3);
        }
        else if(isInsert(comando))
        {
            parser_insert(entrada, i, &f1, &f2, &f3);
            executar_insert(pdb->pbanco->ptabelas, &f1, &f2, &f3);
        }
        else if(isUPDATE(comando))
        {
            parser_update(entrada, i, &f1, &f2, &f3, &f4);
            executar_update(pdb->pbanco->ptabelas, &f1, &f2, &f3, &f4);
        }
        else if(isDELETE(comando))
        {
            parser_delete(entrada, i, &f1, &f2);
            executar_delete(pdb->pbanco->ptabelas, &f1, &f2);
        }

        limpar_filas(&f1, &f2, &f3, &f4);
        gets(entrada);
    }

    limpar_filas(&f1, &f2, &f3, &f4);
    limpar_banco(&pdb);

    return 0;
}

