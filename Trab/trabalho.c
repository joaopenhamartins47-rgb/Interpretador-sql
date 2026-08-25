#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void parser_select(char entrada[], int i, char colunas[10][20], int *num_colunas, char tabela[], char condicao[50])
{
    int col = 0;   // 0=colunas 1=pula FROM 2=tabela 3=verifica WHERE 4=le condicao 5=fim 
    int nc = 0;
    int j = 0;

    condicao[0] = '\0';   // garante vazio se nao tiver WHERE 

    while(entrada[i] != '\0')
    {
        if(col == 0)
        {
            i = pula_espacos(entrada, i);
            while(entrada[i] != ' ' && entrada[i] != ',' && entrada[i] != '\0')
            {
                colunas[nc][j] = entrada[i];
                j++;
                i++;
            }
            colunas[nc][j] = '\0';

            if(entrada[i] == ',')
            {
                nc++;
                j = 0;
                i++; //Pula a virgula
                i = pula_espacos(entrada, i);
            }
            else if(entrada[i] == ' ')
            {
                nc++;
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
                tabela[j] = entrada[i];
                j++;
                i++;
            }
            tabela[j] = '\0';
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
                condicao[j++] = entrada[i++];
            
            condicao[j] = '\0';
            col = 5;
        }
        else
        {
            i++;
        }
    }

    *num_colunas = nc;
}



void parser_delete(char entrada[], int i, char tabela[], char condicao[])
{
    int j = 0, col=0;
    while(entrada[i] != '\0')
    {
        if(col == 0){
            i = pula_espacos(entrada, i);
            i = pula_from_where(entrada, i);

            i = pula_espacos(entrada, i);

            while(entrada[i] != ' ' && entrada[i] != '\0')
                tabela[j++] = entrada[i++];
            
            tabela[j] = '\0';
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
                condicao[j++] = entrada[i++];
            condicao[j] = '\0';
            col = 3;
        }
        else
            i++;
    }
}


void parser_update(char entrada[], int i, char tabela[], char colunas[10][20], char valores[10][20], int *num_atribuicoes, char condicao[50])
{
    int j = 0, na = 0, col = 0;

    condicao[0] = '\0';

    while(entrada[i] != '\0')
    {
        if(col == 0)
        {
            i = pula_espacos(entrada, i);
            while(entrada[i] != ' ' && entrada[i] != '\0')
                tabela[j++] = entrada[i++];
            tabela[j] = '\0';

            i = pula_espacos(entrada, i);
            i = pula_from_where(entrada, i); /* pula o SET */
            i = pula_espacos(entrada, i);

            j = 0;
            col = 1;
        }
        else if(col == 1)
        {
            while(entrada[i] != ' ' && entrada[i] != '=' && entrada[i] != '\0')
                colunas[na][j++] = entrada[i++];
            colunas[na][j] = '\0';

            i = pula_espacos(entrada, i);

            if(entrada[i] == '=')
                i++;

            i = pula_espacos(entrada, i);

            j = 0;
            while(entrada[i] != ' ' && entrada[i] != ',' && entrada[i] != '\0')
                valores[na][j++] = entrada[i++];
            valores[na][j] = '\0';

            na++;

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
                condicao[j++] = entrada[i++];
            condicao[j] = '\0';
            col = 4;
        }
        else
        {
            i++;
        }
    }

    *num_atribuicoes = na;
}


void parser_insert(char entrada[], int i, char tabela[], char colunas[10][20], char valores[10][20], int *num_colunas)
{
    int j = 0, nc = 0, col = 0;

    while(entrada[i] != '\0')
    {
        if(col == 0)
        {
            i = pula_espacos(entrada, i);
            i = pula_from_where(entrada, i); /* pula o INTO */
            i = pula_espacos(entrada, i);

            while(entrada[i] != ' ' && entrada[i] != '(' && entrada[i] != '\0')
                tabela[j++] = entrada[i++];
            tabela[j] = '\0';

            i = pula_espacos(entrada, i);
            if(entrada[i] == '(')
                i++; /* pula o '(' */

            j = 0;
            col = 1;
        }
        else if(col == 1)
        {
            i = pula_espacos(entrada, i);

            while(entrada[i] != ',' && entrada[i] != ')' && entrada[i] != '\0')
                colunas[nc][j++] = entrada[i++];
            colunas[nc][j] = '\0';
            nc++;

            if(entrada[i] == ',')
            {
                i++;
                j = 0;
            }
            else if(entrada[i] == ')')
            {
                i++; /* pula o ')' */
                col = 2;
            }
        }
        else if(col == 2)
        {
            i = pula_espacos(entrada, i);
            i = pula_from_where(entrada, i); /* pula o VALUES */
            i = pula_espacos(entrada, i);
            if(entrada[i] == '(')
                i++; /* pula o '(' */

            j = 0;
            nc = 0;
            col = 3;
        }
        else if(col == 3)
        {
            i = pula_espacos(entrada, i);

            if(entrada[i] == 39)
            {
                i++; /* pula a aspa de abertura */
                while(entrada[i] != 39 && entrada[i] != '\0')
                    valores[nc][j++] = entrada[i++];
                valores[nc][j] = '\0';
                if(entrada[i] == 39)
                    i++; /* pula a aspa de fechamento */
            }
            else
            {
                while(entrada[i] != ',' && entrada[i] != ')' && entrada[i] != '\0')
                    valores[nc][j++] = entrada[i++];
                valores[nc][j] = '\0';
            }
            nc++;

            i = pula_espacos(entrada, i);

            if(entrada[i] == ',')
            {
                i++;
                j = 0;
            }
            else if(entrada[i] == ')')
            {
                col = 4;
            }
            else
            {
                j = 0;
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