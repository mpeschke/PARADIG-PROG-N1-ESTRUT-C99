#ifndef CABECALHO_FUNCTIONS_ARREMESSO_INCLUDED
#define CABECALHO_FUNCTIONS_ARREMESSO_INCLUDED

// Damos um apelido 'booleano' aos inteiros 0 = FALSE e (diferente de zero = TRUE),
// assim o compilador consegue realizar operações booleanas implícitamente com inteiros nas condições (if,else)
// e nos laços (while,do,etc).
#define BOOL int
#define TRUE 1
#define FALSE 0

// Damos um apelido para quando não há um vencedor (retornando 'EMPATE_*' = NULL significa que não há uma instância 
// representando um vencedor).
#define EMPATE_ARREMESSO NULL

#define ARREMESSOS_NOME_ADVERSARIO_MAXIMO 20
#define NUMERO_ARREMESSOS 3
#define ARREMESSOS_TAMANHO_BUFFER 100
#define ARREMESSO_NUMERO_ADVERSARIOS 2

static const char* const pMENSAGEM_ENTRADA_ARREMESSOS = "Entre com os %d arremessos do adversário %d: (Exemplo: 9.7,10.0,...): ";
static const char* const pERROR_MESSAGE_ARREMESSOS_INVALIDOS = "Há um problema com os arremessos fornecidos. Forneça três arremessos, em metros, separados por vírgulas. Exemplo: 10.8,4.82,12.93.";

// Estruturas de dados. Proporcionam o agrupamento
// de informações relacionadas e facilitam os algoritmos de sorting
// e identificação do vencedor.
struct AdversarioArremessoPeso{
    char NOME[ARREMESSOS_NOME_ADVERSARIO_MAXIMO];
    float arremessos[NUMERO_ARREMESSOS];
};

struct RankingArremessoPeso{
    int adversarios[ARREMESSO_NUMERO_ADVERSARIOS];
    float melhoresmarcas[ARREMESSO_NUMERO_ADVERSARIOS];
};

/**
    Valida a modalidade selecionada pelo usuário.

    @param pEntrada buffer de string contendo o que o usuário digitou como modalidade selecionada.
    @return TRUE (modalidade implementada) ou FALSE (modalidade não-implementada)
*/
BOOL validaModalidade(char* pEntrada);

/**
    Valida os arremessos fornecidos.

    @param pEntrada buffer de string contendo os arremessos (float), separados por vírgulas.
    @param arremessos array contendo os arremessos (float) identificados no parâmetro pEntrada.
    @return TRUE (identificados todos os arremessos como válidos) ou FALSE (um ou mais ou todos os arremessos são inválidos)
*/
BOOL validaArremessos(char* pEntrada, float arremessos[]);

/**
    Ordena os arremessos, do menor para o maior.

    @param adversario identifica o número do usuário (1,2,3, etc).
    @param arremessos array contendo os arremessos (float) identificados no parâmetro pEntrada.
    @param padversario pointer para instância AdversarioArremessoPeso, para receber seu nome identificador
    e seus arremessos ordenados.
*/
void OrdenaRankingArremessos(const int adversario, const float arremessos[], struct AdversarioArremessoPeso* padversario);

/**
    Identifica o vencedor da competição de arremesso de peso considerando todas as regras do enunciado do exercício.

    @param melhormarca Deve sempre ser 0: a função recursiva vai tentar identificar o vencedor pelo melhor arremesso, 
    e recursivamente incrementa esse parâmetro para critério de desempate.
    @param adversarios array de AdversarioArremessoPeso representando os adversários.
    @return AdversarioArremessoPeso* pointer para o adversário no parâmetro adversarios identificado como vencedor.
    Ou NULL caso haja empate.
*/
const struct AdversarioArremessoPeso* const vencedorArremessoPeso(const int melhormarca, const struct AdversarioArremessoPeso adversarios[]);

#endif