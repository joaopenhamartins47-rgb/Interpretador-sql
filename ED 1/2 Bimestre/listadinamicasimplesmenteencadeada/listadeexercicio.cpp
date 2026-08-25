#include <stdio.h>
#include <conio2.h>
#include <ctype.h>

char menu(void)
{
    printf("A - Exibir o primeiro elemento da lista\n");
    printf("B - Exibir o ultimo elemento da lista\n");
    printf("C - Inserir apos o ultimo elemento\n");
    printf("D - Inserir entre dois elementos previamente conhecidos pelo usuario\n");
    printf("E - Consultar um determinado elemento\n");
    printf("F - Exibir todos os elementos da lista recursivamente\n");
    printf("G - Excluir um determinado elemento\n");
    printf("H - Excluir todos os elementos da lista (não recursivamente e recursivamente)\n");
    printf("I - Inserir os elementos ordenados alfabeticamente\n");
    return toupper(getche());
}


struct Tpno
{
    char id;
    Tpno *prox;
};

//Exibir primeiro elemento da lista
void exibir_primeiro(Tpno *L)
{
    if(L == NULL)
        printf("Lista vazia!\n");
    else
        printf("O primeiro elemento eh: %c\n", L->id);
}

//Exibir ultimo elemento da lista
void exibir_ultimo(Tpno *L)
{
    if(L == NULL)
        printf("Lista vazia!\n");
    else
    {
        while(L->prox != NULL)
            L = L->prox;
        printf("O ultimo elemento da lista é %c\n", L->id);
    }
}


//Inserir por ultimo
Tpno *criar_caixinha(char dado)
{
    Tpno *novo;
    novo = new Tpno;
    novo->id = dado;
    novo->prox = NULL;
    return novo;
}

Tpno *Inserir_por_ultimo(Tpno *L)
{
    Tpno *novo, *aux;
    char elemento;
    elemento = getche();
    while(elemento != 27)
    {
        novo = criar_caixinha(elemento);
        if(L == NULL)
            L = novo;
        else
        {
            //faz a busca pra achar o ultimo elemento, sempre do comeco por isso do aux = L
            aux = L;
            while(aux->prox != NULL)
                aux = aux->prox;
            aux->prox = novo; 
        }
        elemento = getche();
    }
    return L;
}

Tpno *Inserir_entre_2(Tpno *L, char dado1, char dado2) 
{
    Tpno *novo, *aux;
    char elemento;
    
    printf("\nDigite o novo elemento: ");
    elemento = getche();
    
    // começa no início da lista
    aux = L;

    // procura os dois elementos consecutivos
    while(aux != NULL && aux->prox != NULL && !(aux->id == dado1 && aux->prox->id == dado2))
        aux = aux->prox;
    

    // encontrou os dois elementos lado a lado
    if(aux != NULL && aux->prox != NULL)
    {
        // cria o novo nó
        novo = criar_caixinha(elemento);

        if(novo != NULL)
        {
            /*
                ANTES:

                [B] -------> [C]

                aux aponta para B
            */

            // novo aponta para o segundo elemento
            novo->prox = aux->prox;

            /*
                AGORA:

                [B] -------> [C]
                               ^
                               |
                              [X]
            */

            // primeiro elemento aponta para o novo nó
            aux->prox = novo;

            /*
                RESULTADO FINAL:

                [B] -------> [X] -------> [C]
            */
        }
    }
    else
        printf("\nElementos nao encontrados consecutivamente!");

    return L;
}

//Consultar um determinado elemento
Tpno *consulta(Tpno *L, char elemento)
{
    Tpno *aux = NULL;
    if(L == NULL)
    {
        printf("Elemento nao encontrado, lista vazia!\n");
        return NULL;
    }
    else
    {
        aux = L;
        while(aux->id != elemento && aux->prox != NULL)
            aux = aux->prox;
        if(aux->id != elemento)
            printf("Elemento nao encontrado! \n");
        else
        {
            printf("Elemento %c encontrado!", aux->id);
            return aux;
        }
        return NULL;
    }
}

//Exibir todos os elementos da lista recursivamente
Tpno *exibir_recursivo(Tpno *L)
{
    if(L == NULL)
        return L;
    else
    {
        printf("%c", L->id);
        return exibir_recursivo(L->prox); //L.prox aponta para a struct inteira do proximo nó, avançando na recursividade
    }
}

//Excluir um determinado elemento
Tpno *excluir(Tpno *L, char elemento)
{

    //A ideia aqui é encontrar o elemento que eu quero excluir,fazer o elemento anterior apontar para o próximo nó, retirando o nó da lista
    Tpno *aux = L, *elem_anterior = NULL;
    // procura o elemento
    while(aux != NULL && aux->id != elemento)
    {
        elem_anterior = aux;
        aux = aux->prox;
    }

    // encontrou o elemento
    if(aux != NULL)
    {
        // se for o primeiro nó
        if(elem_anterior == NULL)
            L = aux->prox;

        else
            elem_anterior->prox = aux->prox;

        // desconecta o nó removido
        aux->prox = NULL;
        delete aux;
        printf("Elemento removido!\n");
    }
    else
        printf("Elemento nao encontrado!\n");

    return L;
}

//Excluir todos os elementos da lista recursivamente
Tpno *excluir_todos(Tpno *L)
{
    //vou andar com o L
    if(L == NULL)
        return L;
    else
    {
        excluir_todos(L->prox);
        L->prox = NULL;
        delete(L);
        return NULL;
    }
}

//Excluir todos os elementos sem recursividade
Tpno *excluir_todos_iterativo(Tpno *L)
{
    Tpno *aux = NULL;
    while(L != NULL)
    {
        aux = L;
        L = L->prox;
        aux->prox = NULL; //A ordem importa, pois quando copiamos uma variavel a outra e colocamos o .prox = NULL, a variavel original é atualizada automaticamente pois estamos lidando com memoria
        delete(aux);
    }
    return L;
}

//Inserir os elementos ordenados alfabeticamente
Tpno *Inserir_ordenado(Tpno *L)
{
    Tpno *novo = NULL, *andador = NULL, *aux = NULL;
    char elemento;
    elemento = getche();
    while(elemento != 27)
    {
        novo = criar_caixinha(elemento);
        andador = L;
        if(andador == NULL)
            L = novo;
        else
        {
            aux = NULL;
            while(andador != NULL && elemento > andador->id)
            {
                aux = andador;
                andador = andador->prox;
            }
            if(aux == NULL) //Insere no comeco
            {
                novo->prox = andador;
                //Como insere no começo, atualiza L
                L = novo;
            }
            else
            {
                novo->prox = andador; //Aponta para o maior elemento
                aux->prox = novo; //elemento anterior, que é o menor, aponta para o novo
            }
        }
        elemento = getche();
    }
    return L;
}

int main(void)
{
    char op;
    char elemento, dado1, dado2;

    Tpno *lista = NULL;

    do
    {
		clrscr();
        op = menu();

        switch (op)
        {
        case 'A':
            exibir_primeiro(lista);
            break;

        case 'B':
            exibir_ultimo(lista);
            break;

        case 'C':

            printf("\nDigite os elementos (ESC para parar): ");
            lista = Inserir_por_ultimo(lista);
            break;

        case 'D':

            printf("\nDigite o primeiro elemento conhecido: ");
            dado1 = getche();

            printf("\nDigite o segundo elemento conhecido: ");
            dado2 = getche();
            
            lista = Inserir_entre_2(lista, dado1, dado2);
            break;

        case 'E':

            printf("\nDigite o elemento para consultar: ");
            elemento = getche();
            consulta(lista, elemento);
            break;

        case 'F':

            printf("\nElementos da lista:\n");
            exibir_recursivo(lista);
            break;

        case 'G':

            printf("\nDigite o elemento para excluir: ");
            elemento = getche();
            lista = excluir(lista, elemento);
            break;

        case 'H':

            printf("\n1 - Excluir recursivamente");
            printf("\n2 - Excluir iterativamente");

            op = getche();

            if(op == '1')
                lista = excluir_todos(lista);
            else
                lista = excluir_todos_iterativo(lista);
            break;

        case 'I':

            printf("\nDigite os elementos ordenados (ESC para parar): ");
            lista = Inserir_ordenado(lista);
            break;
        }

        printf("Pressione qualquer tecla...\n");
        getch();

    } while (op != 27);

    return 0;
}
