#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "TADtrab.h"

int parser_comando(char entrada[], char *comando)
{
    int i;
    for(i=0;entrada[i] != ' ';i++)
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

            while(entrada[i] != ' ' &&
                  entrada[i] != ',' &&
                  entrada[i] != '\0')
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

        /*
         * PULA O FROM
         */
        else if(col == 1)
        {
            pula_espacos(entrada, &i);
            pula_from_where(entrada, &i);
            pula_espacos(entrada, &i);

            col = 2;
        }

        /*
         * TABELAS DO FROM
         */
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

            /*
             * Tem outra tabela
             */
            if(entrada[i] == ',')
            {
                i++;
                pula_espacos(entrada, &i);
            }

            /*
             * Terminou o FROM e tem WHERE
             */
            else if(entrada[i] == 'W' || entrada[i] == 'w')
            {
                pula_from_where(entrada, &i);
                pula_espacos(entrada, &i);
                col = 4;
            }

            else
                col = 5;
        }

        /*
         * WHERE
         */
        else if(col == 4)
        {
            j = 0;
            k = 0;

            /*
             * Campo
             */
            ler_palavra(entrada, &i, campo);

            while(campo[j] != '\0')
                condicao[k++] = campo[j++];

            condicao[k++] = ' ';

            /*
             * Operador
             */
            j = 0;
            ler_palavra(entrada, &i, operador);

            while(operador[j] != '\0')
                condicao[k++] = operador[j++];

            /*
             * BETWEEN
             */
            if(strcmp(operador, "BETWEEN") == 0 ||
               strcmp(operador, "between") == 0)
            {
                condicao[k++] = ' ';

                j = 0;
                ler_palavra(entrada, &i, valor1);

                while(valor1[j] != '\0')
                    condicao[k++] = valor1[j++];

                condicao[k++] = ' ';

                j = 0;
                ler_palavra(entrada, &i, palavra);

                while(palavra[j] != '\0')
                    condicao[k++] = palavra[j++];

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

            /*
             * Verifica se existe outro AND
             */
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
            //Le a condicao
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
    int j = 0, na = 0, col = 0;
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
            while(entrada[i] != ' ' && entrada[i] != ',' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];
            palavra[j] = '\0';
            enqueue(&*f3, palavra);

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
        {
            i++;
        }
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

void ler_palavra(char *entrada, int *i, char *destino){
    int j = 0;

    while(entrada[*i] != ' ' && entrada[*i] != '\0' && entrada[*i] != '(' && entrada[*i] != ')' && entrada[*i] != ',' && entrada[*i] != ';')
        destino[j++] = entrada[(*i)++];

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

                ler_palavra(segmento, &k, nome_campo);

                nc = buscar_campo(nt->pcampos, nome_campo);

                if(nc)
                    nc->pk = 'S';
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

void abrir_arquivo_script(char *caminho, pondb **pdb){
    FILE *arq = fopen(caminho, "r");
    char statement[1000];
    int j, c, anteriorEspaco;
    if(arq == NULL){
    	printf("[!] Erro ao abrir o arquivo");
    }
    else{
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
	        else if(c == '\n' || c == '\r' || c == '\t' || c == ' '){
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

int main(void){
    int i;
    char comando[30];
    char entrada[100];
    char caminho[100];
    fila *f1, *f2, *f3, *f4;
    pondb *pdb;
    inicializa_ponteiro_banco(&pdb);
    init(&f1);
    init(&f2);
    init(&f3);
    init(&f4);

    printf("Digite o nome do arquivo de script (deve estar na pasta do projeto): ");
    fgets(caminho, sizeof(caminho), stdin);

    i = 0;
    while(caminho[i] != '\n' && caminho[i] != '\0')
        i++;
    caminho[i] = '\0';

    abrir_arquivo_script(caminho, &pdb);

    imprimir_banco(pdb);

    gets(entrada);
    while(strcmp(entrada, "\0") != 0)
    {
        i = parser_comando(entrada, comando);
        if(isCREATE(comando))
        {
            pula_espacos(entrada, &i);

            if(isCreateDatabase(entrada, &i))
            {
                /*
                    Aqui entra a parte que vai extrair
                    o nome do banco do comando.
                */
                criar_banco(&pdb, "banco_de_dados"); //Aqui vai entrar a parte do create database pra extrair os dados do script sql, entao acho q seria uma variavel
            }
            else
            {  
                /*
                    Aqui entra a parte que vai extrair
                    o nome da tabela e os campos.
                */
                inserir_tabela(&pdb->pbanco->ptabelas, "nome_tabela");
            }
        }
        else if(isALTER(comando))
        {
            /*
                ALTER TABLE
                Aqui entra a função que vai
                criar o relacionamento FK.
            */
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

            executar_update(pdb->pbanco->ptabelas, &f1,&f2,&f3,&f4);
        }
        else if(isDELETE(comando))
        {
            parser_delete(entrada, i, &f1, &f2);
            executar_delete(pdb->pbanco->ptabelas,&f1, &f2);
        }

        gets(entrada);
        limpar_filas(&f1, &f2, &f3, &f4);
    }


    return 0;
}
/*
INTEGRIDADE
├── PK duplicada                             ❌
├── FK no INSERT                             ❌
├── FK no UPDATE                             ❌
└── FK no DELETE                             ❌

FINALIZAÇÃO
├── Limpar filas após SELECT                 ❌
├── Ajustar saída para formato de tabela     🔄
├── Corrigir Patual após DELETE              🔄
├── Script final                             🔄
└── Testes completos                         🔄
*/

