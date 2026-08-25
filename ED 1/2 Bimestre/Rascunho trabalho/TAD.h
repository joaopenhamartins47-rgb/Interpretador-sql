
// Nó da Lista Simplesmente Encadeada (pacientes na fila)
// Inserção ORDENADA por prioridade: 1=Alta > 2=Média > 3=Baixa
struct TpAnimal 
{
    char nome[50];
    char especie[50];
    char gravidade[14];
    char data[14];
    int prioridade;          // 1=Alta, 2=Média, 3=Baixa
    int tempoProcedimento;   // unidades de tempo para ser atendido
    int tempoChegada;        // unidade de tempo em que entrou na fila
    TpAnimal *prox;
};

// Atendente de cada especialidade
struct TpAtendente
{
    int ocupado, tempoRestante;       // decrementa 1 por unidade de tempo
    TpAnimal *paciente;
};

// Descritor de Fila (TAD) — controla a fila de cada especialidade
struct TpDescFila 
{
    TpAnimal *inicio;        // aponta para o animal de maior prioridade
    TpAnimal *fim;           // aponta para o último animal da fila
    int qtdeNaFila;          // animais aguardando atendimento

    // --- estatísticas ---
    int totalAtendidos;
    int atendidosAlta;
    int atendidosMedia;
    int atendidosBaixa;

    int somaTempoEsperaAlta;
    int somaTempoEsperaMedia;
    int somaTempoEsperaBaixa;
};

// Nó da Lista Duplamente Encadeada (especialidades/setores)
struct TpEspecialidade 
{
    char nome[64];
    TpDescFila fila;           // cada setor possui seu próprio descritor
    int numAtendentes;
    TpAtendente *atendentes;   // alocado dinamicamente: new TpAtendente[numAtendentes]
    TpEspecialidade *ant, *prox;
};

// Descritor do Hospital — cabeça da lista duplamente encadeada
struct TpDescHospital 
{
    TpEspecialidade *inicio;   // primeiro setor
    TpEspecialidade *fim;      // último setor
    int qtdeEspecialidades;
};