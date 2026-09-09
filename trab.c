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
    int col = 0;   // 0=colunas 1=pula FROM 2=tabela 3=verifica WHERE 4=le condicao 5=fim 
    int j = 0;
    char palavra[50];
    while(entrada[i] != '\0')
    {
        if(col == 0)
        {
            j = 0;
            i = pula_espacos(entrada, i);
            while(entrada[i] != ' ' && entrada[i] != ',' && entrada[i] != '\0')
            {
                palavra[j] = entrada[i];
                j++;
                i++;
            }
            palavra[j] = '\0';
            enqueue(&*f1, palavra);

            if(entrada[i] == ',')
            {
                i++; 
                i = pula_espacos(entrada, i);
            }
            else if(entrada[i] == ' ')
            {
                col = 1;
                i++;
            }
        }
        else if(col == 1)
        {
            i = pula_espacos(entrada, i);
            i = pula_from_where(entrada, i);   
            i = pula_espacos(entrada, i);
            col = 2;
            j = 0;
        }
        else if(col == 2)
        {
            while(entrada[i] != ' ' && entrada[i] != ';' && entrada[i] != '\0')
            {
                palavra[j] = entrada[i];
                j++;
                i++;
            }
            palavra[j] = '\0';
            enqueue(&*f2, palavra);
            col = 3;
        }
        else if(col == 3)
        {
            i = pula_espacos(entrada, i);

            if(entrada[i] == 'W' || entrada[i] == 'w')
            {
                i = pula_from_where(entrada, i); 
                i = pula_espacos(entrada, i);
                j = 0;
                col = 4;
            }
            else
            {
                col = 5;
            }
        }
        else if(col == 4)
        {
            while(entrada[i] != ';' && entrada[i] != '\0')
                palavra[j++] = entrada[i++];
            
            palavra[j] = '\0';
            enqueue(&*f3, palavra);
            col = 5;
        }
        else
        {
            i++;
        }
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
                palavra[j] = entrada[i++];
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


void parser_insert(char entrada[], int i, char tabela[], char colunas[10][20], char valores[10][20], int *num_colunas)
{
    int j = 0, nc = 0, col = 0;

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
                tabela[j++] = entrada[i++];
            }

            tabela[j] = '\0';

            i = pula_espacos(entrada, i);

            if(entrada[i] == '(')
                i++; 

            j = 0;
            nc = 0;
            col = 1;
        }

        else if(col == 1)
        {
            i = pula_espacos(entrada, i);

            j = 0;

            while(entrada[i] != ',' && entrada[i] != ')' && entrada[i] != '\0')
            {
                colunas[nc][j++] = entrada[i++];
            }

            colunas[nc][j] = '\0';
            nc++;

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
            nc = 0;
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
                    valores[nc][j++] = entrada[i++];
                }

                valores[nc][j] = '\0';

                if(entrada[i] == 39)
                    i++; /* pula aspa de fechamento */
            }
            else
            {
                while(entrada[i] != ',' && entrada[i] != ')' && entrada[i] != '\0')
                {
                    valores[nc][j++] = entrada[i++];
                }

                valores[nc][j] = '\0';
            }

            nc++;

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

    *num_colunas = nc;
}



int main(void)
{
    int i;
    char comando[30];
    char tabela[20];
    char condicao[50];
    char entrada[100];

    strcpy(entrada, "DELETE FROM cliente WHERE id_cliente = 1;");

    i = parser_comando(entrada, comando);
    printf("Comando: %s\n", comando);

    parser_delete(entrada, i, tabela, condicao);
    printf("Tabela: %s\n", tabela);
    printf("Condicao: %s\n", condicao);

    printf("\n---\n\n");

    strcpy(entrada, "DELETE FROM aluguel WHERE valor_pago = 0.00;");

    i = parser_comando(entrada, comando);
    printf("Comando: %s\n", comando);

    parser_delete(entrada, i, tabela, condicao);
    printf("Tabela: %s\n", tabela);
    printf("Condicao: %s\n", condicao);

    return 0;
}