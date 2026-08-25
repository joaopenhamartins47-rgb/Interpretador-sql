#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <conio2.h>

/*
Um petshop armazena seus animais cadastrados em um arquivo binário animais.dat. Cada animal possui os campos: Código (int), Nome (char[50]), Espécie (char[30]) e Peso (float). O sistema não consegue carregar todos os registros em memória de uma vez, então a solução adotada é guardar somente o código e a posição de cada registro em uma Lista Duplamente Encadeada ordenada pelo código.
*/



/*
2 a.) Defina as estruturas de dados necessárias e implemente uma função que leia o arquivo binário e construa a lista duplamente encadeada com código e posição de cada registro.
*/
struct animais
{
    int cod;
    char nome[50];
    char especie[30];
    float peso;
    long pos;
    animais *ant, *prox;
};


struct Tpdescanimais
{
    animais *inicio, *fim;
};

animais *criar_animal(animais &dados)
{
    animais *novo;
    novo = new animais;
    novo->pos = dados.pos;
    novo->peso = dados.peso;
    strcpy(novo->especie, dados.especie);
    strcpy(novo->nome, dados.nome);
    novo->cod = dados.cod;
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

void insercao_ordenada(Tpdescanimais &desc, animais &dados)
{
    animais *novo = criar_animal(dados);
    if(desc.inicio == NULL)
        desc.inicio = desc.fim = novo;
    else
    {
        if(novo->cod < desc.inicio->cod) //Insercao no inicio
        {
            novo->prox = desc.inicio;
            desc.inicio->ant = novo;
            desc.inicio = novo;
        }
        else if(novo->cod > desc.fim->cod) //Insercao no fim
        {
            novo->ant = desc.fim;
            desc.fim->prox = novo;
            desc.fim = novo;
        }
        else
        {
            //Procura ate achar
            animais *andador = desc.inicio->prox;
            while(andador->prox != NULL && novo->cod > andador->cod) //Insercao entre 2 elementos
                andador = andador->prox;
            
            novo->prox = andador;
            novo->ant = andador->ant;
            andador->ant->prox = novo;
            andador->ant = novo;
        }
    }
}

void ler_registros(Tpdescanimais &desc)
{
    animais dados;
    FILE *Ptrarq = fopen("dados.dat", "rb");
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        while(!feof(Ptrarq))
        {
            fread(&dados, sizeof(animais), 1, Ptrarq);
            long pos = ftell(Ptrarq) - sizeof(animais);
            dados.pos = pos;
            insercao_ordenada(desc, dados);
        }
        fclose(Ptrarq);
    }
}

/*
2. b) Crie uma função que escreva os registros em ordem crescente (do menor para o maior código) em um arquivo txt recebido por parâmetro chamado crescente.txt.
*/
void registros(FILE *Ptrarq, Tpdescanimais &desc)
{
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        animais *andador = desc.inicio;
        while(andador != NULL)
        {
            fprintf(Ptrarq, "Cod: %d, Especie: %s, Nome: %s, pos: %ld\n", andador->cod, andador->especie, andador->nome, andador->pos);
            andador = andador->prox;
        }
    }
}

/*
2. c) Com a mesma lista, crie uma função recursiva que escreva os registros em ordem decrescente em um arquivo txt chamado decrescente.txt.
*/

void recursiva(animais *andador, FILE *Ptrarq)
{
    if(Ptrarq != NULL && andador != NULL)
    {
        recursiva(andador->prox, Ptrarq);
        fprintf(Ptrarq, "Cod: %d, Especie: %s, nome: %s, pos: %ld\n", andador->cod, andador->especie, andador->nome, andador->pos);
    }
}

    

/*
3) Lista de listas
*/

struct musica
{
    char nome_musica[80];
    int duracao;
    musica *prox;
};

struct Tpmusica
{
    musica *inicio, *fim;
};

struct album
{
    char titulo[80];
    int ano_lancamento;
    Tpmusica desc_musica;
    album *prox;
};

struct Tpalbum
{
    album *inicio, *fim;
};

struct artista
{
    char nome_artista[50];
    char genero_musical[30];
    Tpalbum desc_album;
    artista *prox;
};

struct Tpartista
{
    artista *inicio, *fim;
};

/*
3 a) Crie um sistema de inserção de Artistas ordenado alfabeticamente pelo nome. Dentro de cada artista, os álbuns devem ser inseridos de forma ordenada pelo ano de lançamento (crescente). Dentro de cada álbum, as músicas devem ser inseridas seguindo o conceito de FILA (FIFO).
*/

musica *criar_musica(musica &dados)
{
    musica *novo;
    novo = new musica;
    novo->duracao = dados.duracao;
    strcpy(novo->nome_musica, dados.nome_musica);
    novo->prox = NULL;
    return novo;
}

album *criar_album(album &dados)
{
    album *novo;
    novo = new album;
    strcpy(novo->titulo, dados.titulo);
    novo->ano_lancamento = dados.ano_lancamento;
    novo->desc_musica.inicio = novo->desc_musica.fim = NULL;
    novo->prox = NULL;
    return novo;
}

artista *criar_artista(artista &dados)
{
    artista *novo;
    novo = new artista;
    strcpy(novo->nome_artista, dados.nome_artista);
    strcpy(novo->genero_musical, dados.genero_musical);
    novo->desc_album.inicio = novo->desc_album.fim = NULL;
    novo->prox = NULL;
    return novo;
}

//Primeiro insercao da musica (FIFO)
void inserir_musica(Tpmusica &desc, musica *dados)
{
    if(desc.inicio == NULL)
        desc.inicio = desc.fim = dados;
    else
    {
        desc.fim->prox = dados;
        desc.fim = dados;
    }
}
//Insercao do album (ordenada pelo ano de lancamento)
void inserir_album(Tpalbum &desc, album *dados)
{
    if(desc.inicio == NULL)
        desc.inicio = desc.fim = dados;
    else
    {
        if(dados->ano_lancamento < desc.inicio->ano_lancamento)
        {
            dados->prox = desc.inicio;
            desc.inicio = dados;
        }
        else if(dados->ano_lancamento > desc.fim->ano_lancamento)
        {
            desc.fim->prox = dados;
            desc.fim = dados;
        }
        else
        {
            album *andador = desc.inicio->prox;
            album *ant = desc.inicio;
            while(andador->prox != NULL && dados->ano_lancamento > andador->ano_lancamento)
            {
                ant = andador;
                andador = andador->prox;
            }
            dados->prox = andador;
            ant->prox = dados;
        }
    }
}

//Insercao do artista(ordenada pelo nome)
void inserir_artista(Tpartista &desc)
{
    artista dados;
    album dados_album;
    musica dados_musica;
    printf("Digite o nome do artista: \n");
    fflush(stdin);
    gets(dados.nome_artista);
    printf("Digite o genero musical: \n");
    fflush(stdin);
    gets(dados.genero_musical);
    artista *novo = criar_artista(dados);
    if(desc.inicio == NULL)
        desc.inicio = desc.fim = novo;
    else
    {
        if(strcmp(novo->nome_artista, desc.inicio->nome_artista) < 0)
        {
            novo->prox = desc.inicio;
            desc.inicio = novo;
        }
        else if(strcmp(novo->nome_artista, desc.fim->nome_artista) > 0)
        {
            desc.fim->prox = novo;
            desc.fim = novo;
        }
        else
        {
            artista *andador = desc.inicio->prox, *ant = desc.inicio;
            while(andador->prox != NULL && strcmp(novo->nome_artista, andador->nome_artista) > 0)
            {
                ant = andador;
                andador = andador->prox;
            }
            novo->prox = andador;
            ant->prox = novo;
        }
    }
    printf("Artista inserido com sucesso! \n");
    printf("Digite o titulo do album \n");
    fflush(stdin);
    gets(dados_album.titulo);
    printf("Digite o ano de lançamento do album \n");
    scanf("%d", &dados_album.ano_lancamento);

    album *novo_album = criar_album(dados_album);
    inserir_album(novo->desc_album, novo_album); //Insere o album onde o novo esta inserido

    printf("Digite o titulo da musica \n");
    fflush(stdin);
    gets(dados_musica.nome_musica);
    printf("Digite a duracao da musica \n");
    scanf("%d", &dados_musica.duracao);

    musica *nova_musica;

    nova_musica = criar_musica(dados_musica);
    inserir_musica(novo_album->desc_musica, nova_musica);

    printf("Cadastro realizado com sucesso! \n");
}
/*
3 b) Crie uma função para remover um Artista da lista, liberando toda a memória alocada (incluindo álbuns e músicas). Ao final, gere um relatório informando o nome do artista removido e quantos álbuns ele possuía no momento da exclusão.
*/

//Primeiro tenho que remover a musica, pra depois remover o album pra depois remover o artista
void remover_artista(Tpartista &desc, char nome[])
{
    artista *andador = desc.inicio, *ant = NULL;
    while(andador != NULL && strcmp(andador->nome_artista, nome) != 0)
    {
        ant = andador;
        andador = andador->prox;
    }
    if(andador != NULL)
    {
        char artista_removido[50];
        int qtde_album=0;
        strcpy(artista_removido, andador->nome_artista);
        //Percorre os albuns
        album *andador_album = andador->desc_album.inicio;
        while(andador_album != NULL)
        {
            qtde_album++;
            musica *andador_musica = andador_album->desc_musica.inicio;
            while(andador_musica != NULL)
            {
                musica *deletar = andador_musica;
                andador_musica = andador_musica->prox;
                delete deletar;
            }
            album *tmp = andador_album;
            andador_album = andador_album->prox;
            delete tmp;
        }
        //Deletar nos 3 casos de exclusao pq eu to removendo em um campo q nao conheço, nao sao todos
        if(andador == desc.inicio)
        {
            desc.inicio = desc.inicio->prox;
            if(desc.inicio == NULL)
                desc.fim = NULL;
        }
        else if(andador == desc.fim)
        {
            desc.fim = ant;
            desc.fim->prox = NULL;
        }
        else
            ant->prox = andador->prox;

        delete andador;
        printf("O artista %s foi removido com %d albuns!\n", artista_removido, qtde_album);
    }
}



/*
3 c) Crie uma função recursiva que percorra todos os álbuns de um artista e, para cada álbum, calcule e exiba o tempo total de duração (soma das durações de todas as músicas). O formato de exibição deve ser: Álbum: [título] — Duração total: [X] segundos.
*/
void recursiva_album(album *andador)
{
    if(andador != NULL)
    {
        int duracao = 0;
        musica *percorrer = andador->desc_musica.inicio;
        while(percorrer != NULL)
        {
            duracao += percorrer->duracao;
            percorrer = percorrer->prox;
        }
        printf("Álbum: [%s] - Duração total: [%d] segundos \n", andador->titulo, duracao);
        recursiva_album(andador->prox);
    }
}


float total_nao_reproduzida(musica *m, int *cont)
{
    if(m == NULL)
        return 0;
    if(!m->reproduzida)
    {
        (*cont)++;
        return m->duracao + total_nao_reproduzida(m->prox, cont);
    }
    else
        return total_nao_reproduzida(m->prox, cont);
}

/*
a) Escreva a função recursiva int liberaTarefas(Tarefa *t) que libera toda a memória das tarefas de um projeto e retorna quantas foram liberadas.
*/

int liberar_tarefa(Tarefa *t)
{
    if(t == NULL)
        return 0;
    
    Tarefa *tmp = t;
    t = t->prox;
    delete tmp;
    return 1 + liberar_tarefa(t);   
}

/*
Escreva a função recursiva void liberaProjetos(Projeto *p) que percorre a lista de projetos, chama liberaTarefas para cada um, libera cada projeto e exibe o nome do projeto removido junto com o número de tarefas que ele possuía.
*/

void liberaprojetos(Projeto *p)
{
    if(p != NULL)
    {
        int result;
        result = liberar_tarefa(p->tarefas.inicio);
        printf("Nome: %s, tarefas que possuia: %d\n", p->nome, result);
        Projeto *tmp = p;
        p = p->prox;
        delete tmp;
        liberaprojetos(p);
    }
        
}


int main(void)
{
    return 0;
}