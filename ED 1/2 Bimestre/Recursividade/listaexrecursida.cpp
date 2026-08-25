#include <stdio.h>

int fatorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    else
        return n*fatorial(n-1);
}

int MDC(int x, int y)
{
    if (y == 0)
        return x;
    else
    {
        int resto = x % y;
        return MDC(y, resto);
    }
}

//Exibir de forma inversa
int inversao(int v[], int tl)
{
    if (tl >= 0)
    {
        printf("%d", v[tl]);
        return inversao(v, tl-1);
    }
        
    else
        return 0; 
}

int potencia(int x, int p)
{
    if (p == 0)
        return 1;
    else
        return x*potencia(x, p-1);
    
}


#define MAXPILHA 100
struct Tppilha
{
    int topo;
    char pilha[MAXPILHA];
};

void PUSH(Tppilha &p, char elem)
{
    p.pilha[++p.topo] = elem;
}

char POP(Tppilha &p)
{
    return p.pilha[p.topo--];
}

char vazia(int topo)
{
    return topo == -1;
}

char cheia(int topo)
{
    return topo == MAXPILHA-1;
}

void inverter_frase_pilha(char frase[], int i, Tppilha &p)
{
    if(frase[i] == '\0')
    {
        while(!vazia(p.topo))
            printf("%c", POP(p));
    }
    else
    {
        if(!cheia(p.topo))
            PUSH(p, frase[i]);
        inverter_frase_pilha(frase, i+1, p);
    }
}

void inverter_frase(char frase[], int tamanho)
{
    if(tamanho < 0)
        return;
    printf("%c", frase[tamanho]);
    inverter_frase(frase, tamanho-1);
}

void inverter_classico(char frase[], int i)
{
    if(frase[i] == '\0')
        return;
    inverter_classico(frase, i+1);
    printf("%c", frase[i]);
}

void hanoi(int n, char a, char b, char c)
{
    if(n > 0)
    {
        hanoi(n-1, a, c, b);

        printf("\nMover disco %d de %c para %c", n, a, c);

        hanoi(n-1, b, a, c);
    }
}


/*
void inverter(char frase[], int i)
{
    if(frase[i] == '\0')
        return;

    inverter(frase, i + 1);

    printf("%c", frase[i]);
}
*/


int formula_somatorio(int n)
{
    if(n == 1)
        return 1;
    else
        return (n*n) + formula_somatorio(n-1);
}

//Construa uma função que calcule a multiplicação de dois números positivos, maiores que zero, através de sucessivas somas do primeiro número.
int mult(int i, int j)
{
    if(j == 0)
        return 0;
    else
        return i+mult(i, j-1);
    
}

//9. Faça uma função recursiva que realize o cálculo do resto da divisão de dois números.
/*
17 % 5

17 - 5 = 12
12 - 5 = 7
7 - 5 = 2

2 < 5
resultado = 2
*/

int resto(int num, int div)
{
    if(num < div)
        return num;
    else
        return resto(num-div, div);
}

#include <math.h>

int binario_dec(char bi[], int tam, int i)
{
    if(i == tam)
        return 0;
    else
        if(bi[i] == '1')
            return pow(2, tam-1-i) + binario_dec(bi, tam, i+1);
        else
            return binario_dec(bi, tam, i+1);
}

int MDC(int a, int b)
{
    if(b == 0)
        return a;
    else
        return MDC(b, (a%b));
}


int main(void)
{
    int result = mult(3, 4);
    printf("%d", result);

    return 0;
}