#include <stdio.h>
#include <conio2.h>
#include <string.h>
#include <ctype.h>

#include "pilhaparenteses.h"



void gravarexpressao(char nomearq[50])
{
    FILE *Ptrarq = fopen(nomearq, "a");
    char expressao[50];
    printf("Digite a expressao que deseja gravar [Enter para sair] \n");
    fflush(stdin);
    gets(expressao);
    while(strcmp(expressao, "\0") != 0)
    {
        fputs(expressao, Ptrarq);
        fputs("\n", Ptrarq);
        printf("Digite a expressao que deseja gravar [Enter para sair] \n");
        fflush(stdin);
        gets(expressao);
    }
    fclose(Ptrarq);
}

void verificar(char nomearq[50], char nomearq2[50])
{
    char expressao[50];
    pilha p;
    FILE *Ptrarq = fopen(nomearq, "w"); //nome diferente
    FILE *Ptrarq2 = fopen(nomearq2, "r");
    if(Ptrarq2 != NULL)
    {
        fscanf(Ptrarq2, "%s", expressao);
        while(!feof(Ptrarq2))
        {
            int correto = 1;
            inicializa(p);
            for(int i=0; expressao[i] != '\0'; i++)
            {
                if(expressao[i] == '(')
                    PUSH(p, expressao[i]);
                     
                else if(expressao[i] == ')')
                {
                    if(vazia(p.topo))
                        correto=0;
                    else
                        POP(p);
                }                
            }
            // verifica se sobraram '('
            if(!vazia(p.topo))
                correto = 0;

            if(correto)
                fprintf(Ptrarq, "Correto!\n");
            else
                fprintf(Ptrarq, "Incorreto!\n");

            fscanf(Ptrarq2, "%s", expressao);    
        }
        fclose(Ptrarq2);
    }
    fclose(Ptrarq);
}

void exibir(char nomearq[50])
{
    char caracter;
    FILE *Ptrarq = fopen(nomearq, "r");
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        caracter = fgetc(Ptrarq);
        while(!feof(Ptrarq))
        {
            printf("%c", caracter);
            caracter = fgetc(Ptrarq);
        }
    }
    fclose(Ptrarq);
}
void learq(char nomearq[50])
{
    printf("Digite o nome do arquivo! \n");
    fflush(stdin);
    gets(nomearq);
}

void validaarq(char nomearq[50])
{
    FILE *Ptrarq = fopen(nomearq, "r");
    if(Ptrarq == NULL)
    {
        printf("Erro ao abrir arquivo, deseja criar? \n");
        if(toupper(getch()) == 'S')
        {
            Ptrarq = fopen(nomearq, "w");
            fclose(Ptrarq);
            printf("Arquivo criado! \n");
        }
    }
    else
    {
        fclose(Ptrarq);
        printf("Tudo certo! \n");
    }
        

}

int main(void)
{
    char nomearq[50], nomearq2[50], expressao[50];
    learq(nomearq);
    validaarq(nomearq);
    learq(nomearq2);
    validaarq(nomearq2);
    gravarexpressao(nomearq);
    verificar(nomearq2, nomearq);
    exibir(nomearq2);
    
    return 0;
}
