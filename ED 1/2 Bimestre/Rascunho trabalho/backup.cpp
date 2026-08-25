#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>
#include "TAD.h"

/*
PARTICIPANTES:
* ALANA MAXIMO PEREIRA
* ANDRESSA FELISBERTO FERREIRA DINIZ
* CAMILA NERIS DOS SANTOS
* JOAO VITOR PENHA MARTINS
*/

void inicializa_hospital(TpDescHospital &hospital)
{
	hospital.qtdeEspecialidades = 0;
	hospital.inicio = hospital.fim = NULL;
}

void inicializa_fila(TpDescFila &fila)
{
	fila.atendidosAlta = 0, fila.atendidosBaixa = 0, fila.atendidosMedia = 0, fila.qtdeNaFila = 0;
	fila.somaTempoEsperaAlta = 0, fila.somaTempoEsperaBaixa = 0, fila.somaTempoEsperaMedia = 0;
	fila.totalAtendidos = 0; fila.inicio = fila.fim = NULL;
}

void adicionar_especialidade(TpDescHospital &hospital, char nome[], int numatend)
{
	TpEspecialidade *novo = new TpEspecialidade; //Cria a nova especialidade
	strcpy(novo->nome, nome);
	novo->numAtendentes = numatend;
	novo->atendentes = new TpAtendente[numatend]; //Na mesma especialidade, cria o vetor de atendentes
	inicializa_fila(novo->fila);
	novo->ant = NULL;
	novo->prox = NULL;
	for(int i=0; i<numatend; i++)
	{
		novo->atendentes[i].ocupado = 0;
		novo->atendentes[i].tempoRestante = 0;
		novo->atendentes[i].paciente = NULL;
	}
	if(hospital.inicio == NULL)
	{
		hospital.inicio = hospital.fim = novo;
	}
	else
	{
		novo->ant = hospital.fim;
		hospital.fim->prox = novo;
		hospital.fim = novo;
	}
	hospital.qtdeEspecialidades++;
}

//Para a remocao, verificar a fila, nao remover se tiver pacientes nela
char filavazia(TpDescFila &f)
{
	return f.qtdeNaFila == 0;
}

void remover_especialidade(TpDescHospital &hospital, char nome[])
{
	TpEspecialidade *aux = hospital.inicio;
	int ocupado = 0;
	while(aux != NULL && strcmp(aux->nome, nome) != 0)
		aux = aux->prox;
		
	if(aux != NULL) //Significa que achou
	{
		if(filavazia(aux->fila)) //Se nao esta atendendo, faz a remocao, mas antes verifica se nao tem nenhum ocupado
		{
			for(int i = 0; i< aux->numAtendentes && !ocupado; i++)
			{
				if(aux->atendentes[i].ocupado)
					ocupado = 1;
			}
			if(!ocupado) //Significa que nao tem nada atendendo, entao remove
			{
				//faz todos os casos de remocao
				if(aux == hospital.inicio && aux == hospital.fim)
					hospital.inicio = hospital.fim = NULL;

				else if(aux == hospital.inicio)
				{
					hospital.inicio = aux->prox;
					hospital.inicio->ant = NULL;
				}
				else if(aux == hospital.fim)
				{
					hospital.fim = aux->ant;
					hospital.fim->prox = NULL;
				}
				else
				{
					aux->prox->ant = aux->ant;
					aux->ant->prox = aux->prox;
					aux->prox = NULL;
					aux->ant = NULL;
				}
				delete[] aux->atendentes; //Libera a memoria dos atendentes
				delete aux;
				hospital.qtdeEspecialidades--;
				printf("Especialidade removida!\n");
			}
			else
				printf("Paciente(s) sendo atendido, não é possivel a remocao! \n");
		}
		else
			printf("Paciente(s) na fila de espera! \n");
	}
	else
		printf("Especialidade não encontrada!\n");
}

TpEspecialidade *menorFila(TpDescHospital &hospital)
{
    TpEspecialidade *aux   = hospital.inicio;
    TpEspecialidade *menor = hospital.inicio;

    while(aux != NULL)
    {
        if(aux->fila.qtdeNaFila < menor->fila.qtdeNaFila)
            menor = aux;
        aux = aux->prox;
    }

    return menor; // retorna NULL se hospital estiver vazio
}

TpAnimal* remover_animal_fila(TpDescFila &fila)
{
    TpAnimal *aux = NULL;

    if(fila.inicio != NULL)
    {
        aux = fila.inicio;
        fila.inicio = fila.inicio->prox;
        aux->prox = NULL;
        fila.qtdeNaFila--;

        if(fila.inicio == NULL)
            fila.fim = NULL;
    }
    return aux;
}

//Dinamismo
void menu_dinamico(void)
{
    clrscr(); // ← adiciona isso aqui
    printf("\n");
    textcolor(LIGHTMAGENTA);
    printf("  +---------------------------------------+\n");
    printf("  |          MENU DE CONFIGURACAO         |\n");
    printf("  +---------------------------------------+\n");
    textcolor(WHITE);
    printf("  | 1 - Alterar tempo da simulacao        |\n");
    printf("  | 2 - Alterar numero de atendentes      |\n");
    printf("  | 3 - Incluir nova especialidade        |\n");
    printf("  | 4 - Remover especialidade existente   |\n");
    textcolor(LIGHTMAGENTA);
    printf("  +---------------------------------------+\n");
    textcolor(WHITE);
    printf("  Digite sua opcao: ");
}


void alterar_atendentes(TpDescHospital &hospital, char nome[], int novoNum)
{
    TpEspecialidade *aux = hospital.inicio;
    int ocupado = 0;

    while(aux != NULL && strcmp(aux->nome, nome) != 0)
        aux = aux->prox;

    if(aux == NULL)
        printf("Especialidade nao encontrada!\n");
    else
    {
        // Verifica se algum atendente acima do novo limite ainda está ocupado
        for(int i = novoNum; i < aux->numAtendentes && !ocupado; i++) //Aqui analisa o que sera perdido
        {
            if(aux->atendentes[i].ocupado)
                ocupado = 1;
        }

        if(ocupado)
            printf("Ha atendente em atendimento no intervalo reduzido, nao e possivel!\n");
        else
        {
            TpAtendente *novo = new TpAtendente[novoNum];

            int copiar;
            if(novoNum < aux->numAtendentes) //Aproveita ou nao os vetores dos antendentes anteriores
                copiar = novoNum;
            else
                copiar = aux->numAtendentes;

            for(int i = 0; i < copiar; i++)
                novo[i] = aux->atendentes[i];

            for(int i = copiar; i < novoNum; i++)
            {
                novo[i].ocupado = 0;
                novo[i].tempoRestante = 0;
                novo[i].paciente = NULL;
            }

            delete[] aux->atendentes;
            aux->atendentes = novo;
            aux->numAtendentes = novoNum;
            printf("Atendentes atualizados para %d!\n", novoNum);
        }
    }
}

TpAnimal *criar_animal(TpAnimal &animal)
{
	TpAnimal *novo;
	novo = new TpAnimal;
	strcpy(novo->nome, animal.nome);
	strcpy(novo->data, animal.data);
	strcpy(novo->especie, animal.especie);
	strcpy(novo->gravidade, animal.gravidade);
	novo->prioridade = animal.prioridade;
	novo->tempoChegada = animal.tempoChegada;
	novo->tempoProcedimento = animal.tempoProcedimento;
	novo->prox = NULL;
	return novo;
}

void Insercao_ordenada(TpDescFila &fila, TpAnimal *animal)
{
	if(fila.inicio == NULL)
		fila.inicio = fila.fim = animal; //Primeira insercao (1)
	else
	{
		if(animal->prioridade < fila.inicio->prioridade) //Insere no inicio (2)
		{
			animal->prox = fila.inicio;
			fila.inicio = animal;
		}
		else if(animal->prioridade >= fila.fim->prioridade) //Insere no final (3)
		{
			fila.fim->prox = animal;
			fila.fim = animal;
		}
		else //Insere entre 2 (4)
		{
			//Auxiliar para andar e auxiliar para pegar o anterior (lista simplesmente encadeada)
			TpAnimal *andador = fila.inicio->prox; //avança 1 na fila pq o inicio ja foi tratado
			TpAnimal *ant = fila.inicio;
			while(andador->prox != NULL && andador->prioridade <= animal->prioridade)
			{
				ant = andador;
				andador = andador->prox;
			}
			ant->prox = animal;
			animal->prox = andador;
		}
	}
	fila.qtdeNaFila++;
}

void mostrar_status(TpDescHospital &hospital, int ut)
{
    clrscr(); // Limpa a tela a cada atualização para o efeito de "Dashboard"
    
    textcolor(WHITE);
    printf("\n ==================================================================\n");
    textcolor(LIGHTCYAN);
    printf(" ||            HOSPITAL VETERINARIO - PAINEL DE CONTROLE         ||\n");
    textcolor(WHITE);
    printf(" ==================================================================\n");
    
    textcolor(YELLOW);
    printf("  [ RELOGIO DO SISTEMA: %04d ut ]\n", ut);
    textcolor(WHITE);
    printf(" ------------------------------------------------------------------\n\n");

    TpEspecialidade *esp = hospital.inicio;
    while(esp != NULL)
    {
        textcolor(LIGHTBLUE);
        printf("  [ SETOR: %s ]\n", esp->nome);
        textcolor(WHITE);
        printf("  Animais aguardando na fila de triagem: ");
        
        // Destaca se a fila estiver acumulando muito
        if(esp->fila.qtdeNaFila > 5) textcolor(LIGHTRED);
        else textcolor(LIGHTGREEN);
        printf("%d\n\n", esp->fila.qtdeNaFila);

        for(int i = 0; i < esp->numAtendentes; i++)
        {
            if(esp->atendentes[i].ocupado)
            {
                textcolor(LIGHTRED);
                printf("   -> Atendente %02d: [ OCUPADO ]", i+1);
                textcolor(WHITE);
                
                // Formatação alinhada para não quebrar a interface
                printf(" | Paciente: %-10s | Tempo Restante: %02d ut\n",
                    esp->atendentes[i].paciente->nome, esp->atendentes[i].tempoRestante);
            }
            else
            {
                textcolor(LIGHTGREEN);
                printf("   -> Atendente %02d: [ LIVRE ]\n", i+1);
            }
        }
        printf("\n");
        esp = esp->prox;
    }
    
    textcolor(WHITE);
    printf(" ==================================================================\n");
    textcolor(DARKGRAY);
    printf("  Pressione qualquer tecla para abrir o MENU DINAMICO...\n");
    textcolor(WHITE);
}

void relatorio_final(TpDescHospital &hospital)
{
    clrscr();
    textcolor(WHITE);
    printf("\n ==================================================================\n");
    textcolor(LIGHTGREEN);
    printf(" ||               RELATORIO ESTATISTICO FINAL                    ||\n");
    textcolor(WHITE);
    printf(" ==================================================================\n");

    TpEspecialidade *esp = hospital.inicio;
    while(esp != NULL)
    {
        textcolor(LIGHTCYAN);
        printf("\n  >> SETOR: %s\n", esp->nome);
        textcolor(WHITE);
        printf("  Total de atendimentos realizados: %d\n", esp->fila.totalAtendidos);
        printf("  --------------------------------------------------\n");

        // Alta Prioridade
        textcolor(LIGHTRED);
        printf("  [!] Prioridade Alta (Emergencia) : ");
        textcolor(WHITE);
        printf("%02d atendido(s)", esp->fila.atendidosAlta);
        if(esp->fila.atendidosAlta > 0)
            printf(" | Espera media: %.2f ut", (float)esp->fila.somaTempoEsperaAlta / esp->fila.atendidosAlta);
        printf("\n");

        // Média Prioridade
        textcolor(YELLOW);
        printf("  [-] Prioridade Media (Urgencia)  : ");
        textcolor(WHITE);
        printf("%02d atendido(s)", esp->fila.atendidosMedia);
        if(esp->fila.atendidosMedia > 0)
            printf(" | Espera media: %.2f ut", (float)esp->fila.somaTempoEsperaMedia / esp->fila.atendidosMedia);
        printf("\n");

        // Baixa Prioridade
        textcolor(LIGHTGREEN);
        printf("  [v] Prioridade Baixa (Rotina)    : ");
        textcolor(WHITE);
        printf("%02d atendido(s)", esp->fila.atendidosBaixa);
        if(esp->fila.atendidosBaixa > 0)
            printf(" | Espera media: %.2f ut", (float)esp->fila.somaTempoEsperaBaixa / esp->fila.atendidosBaixa);
        printf("\n");

        printf("  --------------------------------------------------\n");
        textcolor(DARKGRAY);
        printf("  Animais que permaneceram na fila : %d\n", esp->fila.qtdeNaFila);
        
        esp = esp->prox;
    }
    
    textcolor(WHITE);
    printf("\n ==================================================================\n");
    printf("  Simulacao encerrada com sucesso.\n\n");
}

// ESBOÇO DA SIMULAÇÃO

void simulacao(TpDescHospital &hospital)
{
	FILE *Ptrarq = fopen("arquivo.txt", "r");

	if(Ptrarq == NULL)
		printf("Erro ao abrir arquivo!\n");
	else
	{
		int ut=0, ocupado = 0, tempo_dinamico = 1000;
		TpAnimal animal, *novo = NULL;
		TpEspecialidade *esp, *destino;
		while(!(feof(Ptrarq) && !ocupado) && hospital.qtdeEspecialidades>0 && tempo_dinamico != 0)
		{
			esp = hospital.inicio; //Volta o esp para o inicio toda vez na simulacao
			if(!feof(Ptrarq))
			{
				fscanf(Ptrarq, " %[^,],%d,%[^,],%[^,],%[^,\n]", animal.gravidade, &animal.tempoProcedimento, animal.nome, animal.data, animal.especie);
				if(strcmp(animal.gravidade, "Emergencia") == 0)
					animal.prioridade = 1;
				else if(strcmp(animal.gravidade, "Urgencia") == 0)
					animal.prioridade = 2;
				else
					animal.prioridade = 3;
				animal.tempoChegada = ut;

				novo = criar_animal(animal);

				destino = menorFila(hospital); 
				Insercao_ordenada(destino->fila, novo);
			}

			// 2. PERCORRER ESPECIALIDADES
			ocupado = 0;
			while(esp != NULL)
			{
				for(int i=0; i<esp->numAtendentes; i++)
				{
					if(esp->atendentes[i].ocupado == 1)
					{
						esp->atendentes[i].tempoRestante--;
						if(esp->atendentes[i].tempoRestante == 0)
						{
							esp->atendentes[i].ocupado = 0;
							if(esp->atendentes[i].paciente->prioridade == 1)
								esp->fila.atendidosAlta++;
							else if(esp->atendentes[i].paciente->prioridade == 2)
								esp->fila.atendidosMedia++;
							else
								esp->fila.atendidosBaixa++;

							esp->fila.totalAtendidos++;
							delete esp->atendentes[i].paciente;
							esp->atendentes[i].paciente = NULL;
							if(!filavazia(esp->fila))
							{
								TpAnimal *aux;
								aux = remover_animal_fila(esp->fila);

								if(aux->prioridade == 1)
									esp->fila.somaTempoEsperaAlta += ut - aux->tempoChegada;
								else if(aux->prioridade == 2)
									esp->fila.somaTempoEsperaMedia += ut - aux->tempoChegada;
								else
									esp->fila.somaTempoEsperaBaixa += ut - aux->tempoChegada;

								esp->atendentes[i].ocupado = 1;
								esp->atendentes[i].tempoRestante = aux->tempoProcedimento;
								esp->atendentes[i].paciente = aux;
								ocupado = 1;
							}
						}
						else
							ocupado = 1; 
					}
					else
					{
						if(!filavazia(esp->fila))
						{
							TpAnimal *aux;
							aux = remover_animal_fila(esp->fila);

							if(aux->prioridade == 1)
								esp->fila.somaTempoEsperaAlta += ut - aux->tempoChegada;
							else if(aux->prioridade == 2)
								esp->fila.somaTempoEsperaMedia += ut - aux->tempoChegada;
							else
								esp->fila.somaTempoEsperaBaixa += ut - aux->tempoChegada;

							esp->atendentes[i].ocupado = 1;
							esp->atendentes[i].tempoRestante = aux->tempoProcedimento;
							esp->atendentes[i].paciente = aux;
							ocupado = 1;
						}
					}
				}
				esp = esp->prox;
			}

			ut++;

			Sleep(tempo_dinamico);
			mostrar_status(hospital, ut);
			// menu rápido:
			
            if(kbhit())
			{
				getch(); // descarta a tecla que ativou o menu (qualquer tecla)
				
				menu_dinamico(); // mostra o menu e "Digite sua opcao: "
				
				char tecla = getch(); // agora lê a escolha do usuário
				char nome[64];
				int novoNum;

				clrscr();
				if(tecla == '1')
				{
					printf(" > Novo tempo de simulacao (0 para parar): ");
					scanf("%d", &tempo_dinamico);
				}
				else if(tecla == '2')
				{
					printf(" > Nome do setor para alterar: ");
					scanf("%s", nome);
					printf(" > Novo numero de atendentes: ");
					scanf("%d", &novoNum);
					alterar_atendentes(hospital, nome, novoNum);
					Sleep(1200);
				}
				else if(tecla == '3')
				{
					printf(" > Nome do novo setor: ");
					scanf("%s", nome);
					printf(" > Numero de atendentes: ");
					scanf("%d", &novoNum);
					adicionar_especialidade(hospital, nome, novoNum);
					printf(" > Especialidade criada!\n");
					Sleep(1200);
				}
				else if(tecla == '4')
				{
					printf(" > Nome do setor a remover: ");
					scanf("%s", nome);
					remover_especialidade(hospital, nome);
					Sleep(1200);
				}
			}
		}
		relatorio_final(hospital);
	
        fclose(Ptrarq);
	}
    
}

void liberar_hospital(TpDescHospital &hospital)
{
	TpEspecialidade *esp = hospital.inicio;
	while(esp != NULL)
	{
		TpAnimal *animal = esp->fila.inicio;
		while(animal != NULL)
		{
			TpAnimal *aux = animal;
			animal = animal->prox;
			delete aux;
		}

		//Depois de deletar os animais na fila, libera os pacientes
		for(int i = 0; i<esp->numAtendentes; i++)
		{
			if(esp->atendentes[i].paciente != NULL)
				delete esp->atendentes[i].paciente;
		}
		
		//Por fim deleta os atendentes
		delete[] esp->atendentes;
		TpEspecialidade *aux = esp;  //Copia a especialidade pra deletar, depois avança com o esp
		esp = esp->prox;
		delete aux;
	}
}
int main()
{
    TpDescHospital hospital;
    inicializa_hospital(hospital);

    int op;
    do 
	{
        printf("\n==== CONFIGURACAO DO HOSPITAL ====\n");
        printf("1 - Adicionar especialidade\n");

        // só mostra a opção 2 se tiver pelo menos uma especialidade
        if(hospital.qtdeEspecialidades > 0)
            printf("2 - Iniciar simulacao\n");

        scanf("%d", &op);

        if(op == 1)
        {
            char nome[64];
            int nAtend;
            printf("Nome da especialidade: ");
            scanf("%s", nome);
            printf("Numero de atendentes: ");
            scanf("%d", &nAtend);
            adicionar_especialidade(hospital, nome, nAtend);
        }
        else if(op == 2 && hospital.qtdeEspecialidades == 0)
        {
            printf("Adicione ao menos uma especialidade antes de iniciar!\n");
        }

    } while(op != 2 || hospital.qtdeEspecialidades == 0);

    simulacao(hospital);
	liberar_hospital(hospital);
    return 0;
}
