#include <stdlib.h>
#include <stdio.h>

// Damos um apelido 'booleano' aos inteiros 0 e (diferente de zero),
// assim o compilador consegue realizar operações booleanas implícitas com inteiros nas condições (if,else)
// e nos laços (while,do,etc).
#define BOOL int
#define TRUE 1
#define FALSE 0

// Damos um apelido para quando não há um vencedor (retornando 'EMPATE_*' = não há uma instância representando um vencedor).
#define EMPATE_ARREMESSO NULL
#define EMPATE_GINASTICA_ARTISTICA NULL

#define NOME_ADVERSARIO_MAXIMO 20
#define ARREMESSOS_NUMERO 3
#define NOTAS_NUMERO 5

const unsigned int MODALIDADE_ARREMESSO = 1U;
const unsigned int MODALIDADE_GINASTICA_ARTISTICA = 2U;

struct AdversarioArremessoPeso{
    char NOME[NOME_ADVERSARIO_MAXIMO+1U];
    float arremessos[ARREMESSOS_NUMERO];
};

struct AdversarioGinasticaArtistica{
    char NOME[NOME_ADVERSARIO_MAXIMO+1U];
    float notas[NOTAS_NUMERO];
};

BOOL validaModalidade(const char* const pEntrada, const char* const pERROR_MESSAGE);

BOOL validaNomeAdversario(const char* const pEntrada, const char* const pERROR_MESSAGE);

BOOL validaArremessos(const char* const pEntrada, float arremessos[], const char* const pERROR_MESSAGE);

BOOL validaNotas(const char* const pEntrada, float notas[], const char* const pERROR_MESSAGE);

float notaFinalArremesso(const struct AdversarioArremessoPeso* pAdversario);

float melhorArremesso(const struct AdversarioArremessoPeso* pAdversario);

float segundoMelhorArremesso(const struct AdversarioArremessoPeso* pAdversario);

const struct AdversarioArremessoPeso* const vencedorArremessoPeso(const struct AdversarioGinasticaArtistica adversarios[]);

const struct AdversarioArremessoPeso* const vencedorArremessoPesoCriterioDesempate(const struct AdversarioGinasticaArtistica adversarios[]);

const struct AdversarioGinasticaArtistica* const vencedorGinasticaArtistica(const struct AdversarioGinasticaArtistica adversarios[]);
