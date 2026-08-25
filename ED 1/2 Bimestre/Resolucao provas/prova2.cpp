#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

struct data 
{
    int dia, mes, ano;
};

struct cidades 
{
    int  cod_cidade;
    char nome_cidade[50];
    char est_cidade[50];
    cidades* prox;
};

struct TpDescCidades 
{
    cidades* inicio;
};

struct pessoas 
{
    char cpf[18];
    char nome[50];
    char endereco[50];
    char estado[3];
    char email[70];
    char cidade[50];
    pessoas* prox;
};

struct Tpdescpessoas
{
    pessoas* inicio;
    pessoas* fim;
};

struct passagens
{
    int numero_passagem;
    int cod_voo;
    char cpf[18];
    data data_compra;
    int poltrona;
    pessoas *dono;
    passagens *prox;
};

struct TpDescPassagens 
{
    passagens* inicio;
    passagens* fim;
};

struct voos 
{
    int cod_voo;
    data data_voo;
    int num_lugares;
    char cidade_de_origem[50];
    char cidade_de_destino[50];
    TpDescPassagens passagens;
    voos* prox;
};

struct TpDescVoos {
    voos* inicio;
    voos* fim;
};


pessoas *criar_pessoa(pessoas &dados)
{
    pessoas *novo;
    novo = new pessoas; //Cria a caixinha
    strcpy(novo->cidade, dados.cidade);
    strcpy(novo->cpf, dados.cpf);
    strcpy(novo->email, dados.email);
    strcpy(novo->endereco, dados.endereco);
    strcpy(novo->estado, dados.estado);
    strcpy(novo->nome, dados.nome);
    novo->prox = NULL;
    return novo;
}

passagens *criar_passagem(passagens &dados)
{
    passagens *novo;
    novo = new passagens;
    novo->cod_voo = dados.cod_voo;
    novo->data_compra.dia = dados.data_compra.dia;
    novo->data_compra.mes = dados.data_compra.mes;
    novo->data_compra.ano = dados.data_compra.ano;
    strcpy(novo->cpf, dados.cpf);
    novo->dono = dados.dono;
    novo->poltrona = dados.poltrona;
    novo->numero_passagem = dados.numero_passagem;
    novo->prox = NULL;
    return novo;
}

cidades *criar_cidade(cidades &dados)
{
    cidades *novo;
    novo = new cidades;
    novo->cod_cidade = dados.cod_cidade;
    strcpy(novo->est_cidade, dados.est_cidade);
    strcpy(novo->nome_cidade, dados.nome_cidade);
    novo->prox = NULL;
    return novo;
}

voos *criar_voos(voos &dados)
{
    voos *novo;
    novo = new voos;
    strcpy(novo->cidade_de_destino, dados.cidade_de_destino);
    strcpy(novo->cidade_de_origem, dados.cidade_de_origem);
    novo->cod_voo = dados.cod_voo;
    novo->data_voo.dia = dados.data_voo.dia;
    novo->data_voo.mes = dados.data_voo.mes;
    novo->data_voo.ano = dados.data_voo.ano;
    novo->num_lugares = dados.num_lugares;
    novo->passagens.inicio = NULL;
    novo->passagens.fim = NULL;
    novo->prox = NULL;
    return novo;
}
//Insercao dos dados respeitando o conceito de fila numa estrutura dinamica
void Insercao_voo(Tpdescpessoas &desc, TpDescPassagens &desc_passagem, TpDescCidades &desc_cidades, TpDescVoos &desc_voo)
{
    pessoas dados;
    voos dados_voo;
    cidades dados_cidade;
    passagens dados_passagem;
    FILE *Ptrarq = fopen("voos.dat", "rb");
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        while(!feof(Ptrarq))
        {
            fread(&dados_voo, sizeof(voos), 1, Ptrarq);
            voos *novo = criar_voos(dados_voo);
            if(desc_voo.inicio == NULL)
                desc_voo.inicio = desc_voo.fim = novo;
            else
            {
                desc_voo.fim->prox = novo;
                desc_voo.fim = novo;
            }
        }
        
        printf("Voos disponiveis: \n");
        voos *andador = desc_voo.inicio;
        printf("Voos disponiveis! \n");
        while(andador != NULL)
        {
            printf("Codigo do voo: %d\n", andador->cod_voo);
            printf("Viagem de: %s para: %s\n", andador->cidade_de_origem, andador->cidade_de_destino);
            printf("Data: %d/%d/%d\n", andador->data_voo.dia, andador->data_voo.mes, andador->data_voo.ano);
            printf("Lugares disponiveis: %d\n", andador->num_lugares);
            andador = andador->prox;
        }

        printf("Digite o seu cpf: \n");
        fflush(stdin);
        gets(dados.cpf);
        pessoas *andador_pessoas = desc.inicio; 
        while(andador_pessoas != NULL && strcmp(dados.cpf, andador_pessoas->cpf) != 0)
            andador_pessoas = andador_pessoas->prox;
        
        if(andador_pessoas == NULL) //Nao achou a pessoa, entao insere
        {
            printf("Cadastro nao encontrada, realizando...\n");
            printf("Digite o seu nome: \n");
            fflush(stdin);
            gets(dados.nome);
            printf("Digite o endereco: \n");
            fflush(stdin);
            gets(dados.endereco);
            printf("Digite o estado em que mora: \n");
            fflush(stdin);
            gets(dados.estado);
            printf("Digite o seu email: \n");
            fflush(stdin);
            gets(dados.email);
            printf("Digite a cidade em que mora: \n");
            fflush(stdin);
            gets(dados.cidade);

            //Agora insere

            pessoas *novo;
            novo = criar_pessoa(dados);
            if(desc.inicio == NULL)
                desc.inicio = desc.fim = novo;
            else
            {
                desc.fim->prox = novo;
                desc.fim = novo;
            }
        }
        
        printf("Digite o codigo do voo que deseja comprar! (0 para nao comprar)\n");
        int cod;
        scanf("%d", &cod);
        if(cod != 0)
        {
            voos *procurar = desc_voo.inicio;
            while(procurar != NULL && procurar->cod_voo != cod)
                procurar = procurar->prox;
            
            if(procurar == NULL)
                printf("Voo nao encontrado!\n");
            else
            {
                printf("Voo encontrado!\n");
                printf("Voo: %d - Viagem de %s para %s. Data: %d %d %d", procurar->cod_voo, procurar->cidade_de_origem, procurar->cidade_de_destino, procurar->data_voo.dia, procurar->data_voo.mes, procurar->data_voo.ano);
                printf("Deseja comprar a passagem? \n");
                if(toupper(getch()) == 'S')
                {
                    pessoas *andador_pessoas = desc.inicio; 
                    while(andador_pessoas != NULL && strcmp(dados.cpf, andador_pessoas->cpf) != 0)
                        andador_pessoas = andador_pessoas->prox;

                    printf("Digite o numero da passagem e da poltrona\n");

                    scanf("%d %d", &dados_passagem.numero_passagem, &dados_passagem.poltrona);
                    strcpy(dados_passagem.cpf, andador_pessoas->cpf);
                    dados_passagem.cod_voo = procurar->cod_voo;

                    printf("Digite a data da compra\n");
                    int dia, mes, ano;
                    scanf("%d %d %d", &dia, &mes, &ano);
                    dados_passagem.data_compra.dia = dia;
                    dados_passagem.data_compra.mes = mes;
                    dados_passagem.data_compra.ano = ano;
                    dados_passagem.dono = andador_pessoas;
                    passagens *novo;
                    novo = criar_passagem(dados_passagem);
                    if(procurar->passagens.inicio == NULL)
                        procurar->passagens.inicio = procurar->passagens.fim = novo;
                    else
                    {
                        procurar->passagens.fim->prox = novo;
                        procurar->passagens.fim = novo;
                    }
                    printf("Passagem cadastrada com sucesso! \n");
                }
            }
        }
        fclose(Ptrarq);
            
    }
}



//Exclusao de todas as passagens de forma recursiva
void exclusao_passagens(passagens *andador)
{
    if(andador == NULL)
        return;

    exclusao_passagens(andador->prox);
    delete andador->dono;
    delete andador;
}

void exclusao_voo(TpDescVoos &desc, int cod) //Procura pelo cod, ant pq é lista simplesmente encadeada e tira os nós para nao apontarem para lixo
{
    voos *procurar = desc.inicio, *ant = NULL;
    while(procurar != NULL && procurar->cod_voo != cod)
    {
        ant = procurar;
        procurar = procurar->prox;
    }
        

    if(procurar != NULL) //Significa que achou
    {
        voos *tmp = procurar;
        exclusao_passagens(procurar->passagens.inicio); //exclui todas as passagens

        //realiza os casos da exclusao, ajustando o inicio e o fim

        if(ant == NULL) //Significa que foi o primeiro
            desc.inicio = desc.inicio->prox;
        else
            ant->prox = procurar->prox;
        if(desc.fim == procurar)
            desc.fim = ant;

        delete tmp;
    }
    else
        printf("Voo nao encontrado!\n");   
}

//Relatorio de todos os voos e os passageiros que fizeram a compra do mesmo
void relatorio(TpDescVoos &desc, TpDescPassagens &desc_passagens, Tpdescpessoas &desc_pessoas)
{
    voos *andador_voo = desc.inicio;
    while(andador_voo != NULL)
    {
        printf("Codigo do voo: %d\tData do voo: %d/%d/%d\tNrLugares: %d\n", andador_voo->cod_voo, andador_voo->data_voo.dia, andador_voo->data_voo.mes, andador_voo->data_voo.ano, andador_voo->num_lugares);
        printf("Cidade de origem: %s\n", andador_voo->cidade_de_origem);
        printf("Cidade de destino: %s\n", andador_voo->cidade_de_destino);
        
        passagens *andador_passagens = andador_voo->passagens.inicio;
        printf("Nome \tCidade \tPoltrona\n");
        while(andador_passagens != NULL)
        {
            
            printf("%s \t%s \t%d\n", andador_passagens->dono->nome, andador_passagens->dono->cidade, andador_passagens->poltrona);
            andador_passagens = andador_passagens->prox;
        }
        andador_voo = andador_voo->prox;
    }
}



int main(void)
{
    return 0;
}