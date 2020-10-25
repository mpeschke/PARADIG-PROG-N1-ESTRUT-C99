#ifndef CABECALHO_FUNCTIONS_ARREMESSO_INCLUDED
#define CABECALHO_FUNCTIONS_ARREMESSO_INCLUDED

// Damos um apelido 'booleano' aos inteiros 0 = FALSE e (diferente de zero = TRUE),
// assim o compilador consegue realizar operações booleanas implícitamente com inteiros nas condições (if,else)
// e nos laços (while,do,etc).
#define BOOL int
#define TRUE 1
#define FALSE 0

#define ARREMESSOS_NOME_ADVERSARIO_MAXIMO 20
#define NUMERO_ARREMESSOS 3
#define ARREMESSOS_TAMANHO_BUFFER 100
#define ARREMESSO_NUMERO_ADVERSARIOS 2

static const char* const pMENSAGEM_ENTRADA_ARREMESSOS = "Entre com os %d arremessos do adversário %d: (Exemplo: 9.7,10.0,...): ";
static const char* const pERROR_MESSAGE_ARREMESSOS_INVALIDOS = "Há um problema com os arremessos fornecidos. Forneça três arremessos, em metros, separados por vírgulas. Exemplo: 10.8,4.82,12.93.";

// Estruturas de dados. Proporciona o agrupamento
// de informações relacionadas.
struct AdversarioArremessoPeso{
    char NOME[ARREMESSOS_NOME_ADVERSARIO_MAXIMO];
    float arremessos[NUMERO_ARREMESSOS];
};

struct RankingArremessoPeso{
    int adversarios[ARREMESSO_NUMERO_ADVERSARIOS];
    float melhoresmarcas[ARREMESSO_NUMERO_ADVERSARIOS];
};

// Funções.
BOOL validaModalidadeArremesso(char* pEntrada);

BOOL validaArremessos(char* pEntrada, float arremessos[]);

void AdversarioArremessoPeso(const int adversario, const float arremessos[], struct AdversarioArremessoPeso* padversario);

const struct AdversarioArremessoPeso* const vencedorArremessoPeso(const struct AdversarioArremessoPeso adversarios[]);

const struct AdversarioArremessoPeso* const vencedorArremessoPesoCriterioDesempate(const struct AdversarioArremessoPeso adversarios[]);

#endif