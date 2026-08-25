#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

/*
2- Um feiticeiro quer acessar o seu arsenal de itens que estão guardados em um arquivo binário
dados.dat, cada item possui os seguintes campos Codigo, Descricao, Poder_Atual. Entretanto seu
computador não consegue armazenar uma grande quantidade de dados. Para resolver esse
problema o feiticeiro teve a brilhante ideia de guardar o código e localização de cada item de seu
arsenal em uma Lista Duplamente Encadeada Ordenada pelo código.
*/

struct feiticeiro
{
    int cod, poder_atual;
    char desc[50];
};

struct Tpno
{
    long pos;
    int cod;
    Tpno *ant, *prox;
};

struct Tpdesclista
{
    Tpno *inicio, *fim;
};

Tpno *criar_caixinha(long pos, int cod)
{
    Tpno *novo;
    novo = new Tpno;
    novo->pos = pos;
    novo->cod = cod;
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

void Insercao_ordenada_codigo(Tpdesclista &desc, int cod, long pos)
{
    Tpno *novo = criar_caixinha(pos, cod);
    if(desc.inicio == NULL)
        desc.inicio = desc.fim = novo; //(1)
    else
    {
        if(novo->cod < desc.inicio->cod) //Insere no inicio
        {
            novo->prox = desc.inicio;
            desc.inicio->ant = novo;
            desc.inicio = novo;
        }
        else if(novo->cod > desc.fim->cod) //Insere no final
        {
            novo->ant = desc.fim;
            desc.fim->prox = novo;
            desc.fim = novo;
        }
        else //Insere no meio
        {
            Tpno *andador = desc.inicio;
            while(novo->cod > andador->cod)
                andador = andador->prox;
            
            novo->prox = andador;
            novo->ant = andador->ant;
            andador->ant->prox = novo;
            andador->ant = novo;
        }
    }
    
}

void ler_arq(Tpdesclista &desc)
{
    FILE *Ptrarq = fopen("dados.dat", "rb");
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        feiticeiro feit;
        while(!feof(Ptrarq))
        {
            fread(&feit, sizeof(feiticeiro), 1, Ptrarq);
            long pos = ftell(Ptrarq) - sizeof(feiticeiro);
            Insercao_ordenada_codigo(desc, feit.cod, pos);
        }
        fclose(Ptrarq);
    }
}

//Após ter feito a lista ordenada dos itens do feiticeiro crie uma função que as escreva em ordemcrescente (menor para o maior) em um arquivo txt recebido por parâmetro chamado asceno_crescente.txt.
void escrever_lista_ordenada(Tpdesclista &desc, FILE *Ptrarq)
{
    if(Ptrarq == NULL)
        printf("Erro!\n");
    else
    {
        Tpno *andador = desc.inicio;
        while(andador != NULL)
        {
            fprintf(Ptrarq, "codigo: %d, pos: %ld\n", andador->cod, andador->pos);
            andador = andador->prox;
        }
    }
    
}

//Com a mesma Lista Encadeada faça uma função recursiva que grave em ordem decrescente os itens em um arquivo txt chamado desceno_decresente.txt.
void escrever_descrescente(FILE *Ptrarq, Tpno *andador) //andador comeca do comeco
{
    if(andador == NULL)
        return;
    
    escrever_descrescente(Ptrarq, andador->prox);
    fprintf(Ptrarq, "codigo: %d, posicao: %ld\n", andador->cod, andador->pos);
}

/*
(3)
Startup:
Nome da Startup:
CEO:
Desenvolvedores:
ID:
Nome do Desenvolvedor:
Tecnologia Dominante:
Projetos Entregues:
Anos de Experiencia:
Histórico de trabalho: (Deve conter o nome e o ano de início no qual foi trabalho na Startup)

3 a. - Crie um Sistema para Inserção de Startups que será ordenado de maneira alfabética, nele
    também deverá ser possível inserir os devs que trabalham nessa startup e o histórico de trabalho de
    cada dev. Os históricos de trabalho devem ser ordenados de maneira crescente de modo que o
    emprego atual seja o último da Lista Encadeada.
*/



struct historico
{
    char nome_trab[50];
    int ano;
    historico *prox;
};

struct Tpdeschistorico
{
    historico *inicio, *fim;
};

struct desenvolvedor
{
    int id, projetos_entregues, anos_experiencia;
    char nomedev[50], tecnologia[50];
    desenvolvedor *prox;
    Tpdeschistorico historicos;
};

struct Tpdescdev
{
    desenvolvedor *inicio, *fim;
    int qtde;
};

struct startup
{
    char nome[50];
    char CEO[50];
    startup *prox;
    Tpdescdev devs;
};

struct Tpdescstartup
{
    startup *inicio, *fim;
};


historico *criar_caixinhahis(historico his)
{
    historico *novo;
    novo = new historico;
    *novo = his;
    novo->prox = NULL;
    return novo;
}

void Inserir_historico(Tpdeschistorico &his) //ordenados pelo ano
{
    historico dados;
    printf("Digite o nome do trabalho: \n");
    fflush(stdin);
    gets(dados.nome_trab);
    printf("Digite o ano em que foi contratado: \n");
    scanf("%d", &dados.ano);

    historico *novo;
    novo = criar_caixinhahis(dados);
    //Insercao ordenada
    if(his.inicio == NULL)
        his.inicio = his.fim = novo;
    else
    {
        if(novo->ano < his.inicio->ano)
        {
            novo->prox = his.inicio;
            his.inicio = novo;
        }
        else if(novo->ano > his.fim->ano)
        {
            his.fim->prox = novo;
            his.fim = novo;
        }
        else
        {
            historico *andador = his.inicio->prox, *ant = his.inicio;
            while(andador != NULL && novo->ano > andador->ano)
            {
                ant = andador;
                andador = andador->prox;
            }
            novo->prox = andador;
            ant->prox = novo;

        }
    }
}

desenvolvedor *criar_caixinha(desenvolvedor dados)
{
    desenvolvedor *novo;
    novo = new desenvolvedor;
    *novo = dados;
    novo->historicos.inicio = novo->historicos.fim = NULL; // inicializa
    novo->prox = NULL;
    return novo;
}

void inserir_dev(Tpdescdev &dev)
{
    desenvolvedor desen;

    printf("Digite o id: \n");
    scanf("%d", &desen.id);
    printf("Digite o seu nome: \n");
    fflush(stdin);
    gets(desen.nomedev);
    printf("Quantos projetos entregues? \n");
    scanf("%d", &desen.projetos_entregues);
    printf("Qual tecnologia voce domina? \n");
    fflush(stdin);
    gets(desen.tecnologia);
    printf("Quantos anos de experiencia?");
    scanf("%d", &desen.anos_experiencia);
    printf("Possui historico de trabalho? [s/n]");

    desenvolvedor *novo;
    novo = criar_caixinha(desen);

    if(dev.inicio == NULL)
        dev.inicio = dev.fim = novo;
    else
    {
        dev.fim->prox = novo;
        dev.fim = novo;
    }
    dev.qtde++;

    if(toupper(getch()) == 'S')
    {
        Inserir_historico(dev.fim->historicos);
    }

    printf("Cadastrado com sucesso! \n");
}

startup *criar_caixa(startup dados)
{
    startup *novo;
    novo = new startup;
    *novo = dados;
    novo->devs.inicio = novo->devs.fim = NULL; // inicializa
    novo->devs.qtde = 0;
    novo->prox = NULL;
    return novo;
}

void inserir_startup(Tpdescstartup &start)
{
    startup dados;
    printf("Digite o nome da startup: \n");
    fflush(stdin);
    gets(dados.nome);
    printf("Digite o nome do CEO: \n");
    fflush(stdin);
    gets(dados.CEO);

    startup *novo;
    novo = criar_caixa(dados);
    //Insere a startup primeiro
    if(start.inicio == NULL)
        start.inicio = start.fim = novo;
    else
    {
        if(strcmp(novo->nome, start.inicio->nome) < 0) //Insere no inicio
        {
            novo->prox = start.inicio;
            start.inicio = novo;
        }
        else if(strcmp(novo->nome, start.fim->nome) > 0) //Insere no final
        {
            start.fim->prox = novo;
            start.fim = novo;
        }
        else
        {
            //Procura o lugar certo
            startup *andador = start.inicio->prox, *ant = start.inicio;
            while(andador != NULL && strcmp(novo->nome, andador->nome) > 0)
            {
                ant = andador;
                andador = andador->prox;
            }
            novo->prox = andador;
            ant->prox = novo;
        }
    }
    printf("Deseja inserir dev? [s/n]\n");
    if(toupper(getch()) == 'S')
        inserir_dev(novo->devs);
}

/*
3 b. - Crie uma função para apagar uma Startup da Lista liberando a memoria alocada, além disso gere um relatório contando quantos devs a empresa possuía no momento do desligamento.
*/

void liberar_historico(Tpdeschistorico &his)
{
    historico *andador = his.inicio;
    while(andador != NULL)
    {
        historico *temp = andador;
        andador = andador->prox;
        delete temp;
    }
    his.inicio = his.fim = NULL;
}

void liberar_dev(Tpdescdev &dev)
{
    desenvolvedor *andador = dev.inicio;
    while(andador != NULL)
    {
        liberar_historico(andador->historicos);
        desenvolvedor *temp = andador;
        andador = andador->prox;
        delete temp;
        dev.qtde--;
    }
    dev.inicio = dev.fim = NULL;
}

void remover_startup(Tpdescstartup &desc)
{
    char nome[50];
    printf("Digite o nome da startup que deseja remover! \n");
    fflush(stdin);
    gets(nome);
    if(strcmp(nome, desc.inicio->nome) == 0)
    {
        int qtde = desc.inicio->devs.qtde;
        liberar_dev(desc.inicio->devs);
        startup *remover;
        
        remover = desc.inicio;
        desc.inicio = desc.inicio->prox;
        remover->prox = NULL;
        delete remover;
        printf("%d devs estavam trabalhando! \n", qtde);
    }
    else
    {
        startup *andador = desc.inicio->prox, *ant = desc.inicio;
        while(andador != NULL && strcmp(nome, andador->nome) != 0)
        {
            ant = andador;
            andador = andador->prox;
        }
        if(andador != NULL) //Significa que achou
        {
            int qtde = andador->devs.qtde;
            liberar_dev(andador->devs);
            
            ant->prox = andador->prox;
            andador->prox = NULL;
            delete andador;
            printf("%d devs estavam trabalhando! \n", qtde);
        }
        else
            printf("Elemento nao encontrado! \n");
        
    }
}

/*
3 c). Crie um relatório que verifica qual é o dev com maior eficiência (a eficiência é dada pelo dev
com mais projetos entregues), em caso de empate, mostre todos os devs que tiveram o maior
número de entregas.
*/

void relatorio(Tpdescstartup &start)
{
    startup *s = start.inicio;
    int maior=0;
    while(s != NULL)
    {
        desenvolvedor *andador = s->devs.inicio;
        while(andador != NULL)
        {
            if(andador->projetos_entregues > maior)
                maior = andador->projetos_entregues;

            andador = andador->prox;
        }
        s = s->prox;
    }
    
    s = start.inicio;
    while(s != NULL)
    {
        desenvolvedor *andador = s->devs.inicio;
        while(andador != NULL)
        {
            if(andador->projetos_entregues == maior)
                printf("Dev: %s com %d projetos entregues!\n", andador->nomedev, andador->projetos_entregues);
            andador = andador->prox;
        }
        s = s->prox;
    }
    
}



int main(void)
{

    return 0;
}