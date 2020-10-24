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

static char* const pMENSAGEM_ENTRADA_ARREMESSOS = "Entre com os %d arremessos do adversário %d: (Exemplo: 9.7,10.0,...): ";
static char* const pERROR_MESSAGE_ARREMESSOS_INVALIDOS = "Há um problema com os arremessos fornecidos. Forneça três arremessos, em metros, separados por vírgulas. Exemplo: 10.8,4.82,12.93.";
static char* const pERROR_MESSAGE_MODALIDADE_ARREMESSOS_INVALIDA = "Modalidade não é de arremesso de pesos.";

// Estruturas de dados. Proporciona o agrupamento
// de informações relacionadas.
struct AdversarioArremessoPeso{
    char NOME[ARREMESSOS_NOME_ADVERSARIO_MAXIMO];
    float arremessos[NUMERO_ARREMESSOS];
};

// Funções.
BOOL validaModalidadeArremesso(char* pEntrada, const char* pERROR_MESSAGE);

BOOL validaArremessos(char* pEntrada, float arremessos[], const char* pERROR_MESSAGE);

float melhorArremesso(const struct AdversarioArremessoPeso* pAdversario);

float segundoMelhorArremesso(const struct AdversarioArremessoPeso* pAdversario);

const struct AdversarioArremessoPeso* const vencedorArremessoPeso(const struct AdversarioArremessoPeso adversarios[]);

const struct AdversarioArremessoPeso* const vencedorArremessoPesoCriterioDesempate(const struct AdversarioArremessoPeso adversarios[]);

#endif