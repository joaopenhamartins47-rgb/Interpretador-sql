#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int pula_from_where(char entrada[], int i)
{
    while(entrada[i] != ' ' && entrada[i] != '\0')
        i++;
    return i;
}

int pula_espacos(char entrada[], int i)
{
    while(entrada[i] == ' ' && entrada[i] != '\0')
        i++;
    return i;
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
            i = pula_espacos(entrada, i);

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
                i = pula_espacos(entrada, i);
            }
            else
            {
                i = pula_espacos(entrada, i);
                col = 1;
            }
        }

        /*
         * PULA O FROM
         */
        else if(col == 1)
        {
            i = pula_espacos(entrada, i);
            i = pula_from_where(entrada, i);
            i = pula_espacos(entrada, i);

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

            i = pula_espacos(entrada, i);

            /*
             * Tem outra tabela
             */
            if(entrada[i] == ',')
            {
                i++;
                i = pula_espacos(entrada, i);
            }

            /*
             * Terminou o FROM e tem WHERE
             */
            else if(entrada[i] == 'W' || entrada[i] == 'w')
            {
                i = pula_from_where(entrada, i);
                i = pula_espacos(entrada, i);
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

            i = pula_espacos(entrada, i);

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
            i = pula_espacos(entrada, i);
            i = pula_from_where(entrada, i);

            i = pula_espacos(entrada, i);

            while(entrada[i] != ' ' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];
            
            palavra[j] = '\0';
            enqueue(&*f1, palavra);
            col=1;
        }
        else if(col == 1)
        {
            i = pula_espacos(entrada, i);

            i = pula_from_where(entrada, i);

            i = pula_espacos(entrada, i);
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
            i = pula_espacos(entrada, i);
            while(entrada[i] != ' ' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];
            palavra[j] = '\0';
            enqueue(&*f1, palavra);

            i = pula_espacos(entrada, i);
            i = pula_from_where(entrada, i); /* pula o SET */
            i = pula_espacos(entrada, i);

            j = 0;
            col = 1;
        }
        else if(col == 1)
        {
            while(entrada[i] != ' ' && entrada[i] != '=' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];
            palavra[j] = '\0';
            enqueue(&*f2, palavra);

            i = pula_espacos(entrada, i);

            if(entrada[i] == '=')
                i++;

            i = pula_espacos(entrada, i);

            j = 0;
            while(entrada[i] != ' ' && entrada[i] != ',' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];
            palavra[j] = '\0';
            enqueue(&*f3, palavra);

            if(entrada[i] == ',')
            {
                i++;
                i = pula_espacos(entrada, i);
                j = 0;
            }
            else
                col = 2;
            
        }
        else if(col == 2)
        {
            i = pula_espacos(entrada, i);

            if(entrada[i] == 'W' || entrada[i] == 'w')
            {
                i = pula_from_where(entrada, i);
                i = pula_espacos(entrada, i);
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
            i = pula_espacos(entrada, i);
            i = pula_from_where(entrada, i); 
            i = pula_espacos(entrada, i);

            j = 0;

            while(entrada[i] != ' ' && entrada[i] != '(' && entrada[i] != '\0')
            {
                palavra[j++] = entrada[i++];
            }

            palavra[j] = '\0';
            enqueue(&*f1, palavra);

            i = pula_espacos(entrada, i);

            if(entrada[i] == '(')
                i++; 

            j = 0;
            col = 1;
        }

        else if(col == 1)
        {
            i = pula_espacos(entrada, i);

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
            i = pula_espacos(entrada, i);
            i = pula_from_where(entrada, i); /* pula VALUES */
            i = pula_espacos(entrada, i);

            if(entrada[i] == '(')
                i++; 

            j = 0;
            col = 3;
        }

        else if(col == 3)
        {
            i = pula_espacos(entrada, i);

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
            i = pula_espacos(entrada, i);

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
    *i = pula_espacos(entrada, *i);
    if(entrada[*i] == 'D' || entrada[*i] == 'd')
        return 1;
    return 0;
}

int main(void)
{
    int i;
    char comando[30];
    char entrada[100];
    fila *f1, *f2, *f3, *f4;
    pondb *pdb;
    inicializa_ponteiro_banco(&pdb);
    init(&f1);
    init(&f2);
    init(&f3);
    init(&f4);
    gets(entrada);
    while(strcmp(entrada, "\0") != 0)
    {
        i = parser_comando(entrada, comando);
        if(isCREATE(comando))
        {
            i = pula_espacos(entrada, i);

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
    }
    

    return 0;
}