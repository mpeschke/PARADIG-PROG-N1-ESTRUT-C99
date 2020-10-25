#ifndef CABECALHO_FUNCTIONS_GINASTICA_INCLUDED
#define CABECALHO_FUNCTIONS_GINASTICA_INCLUDED
/*
Esse header não deve ser compartilhado com as aplicações que consomem essa biblioteca.
Contém todas as funções que representam os algoritmos
e facilitam uma arquitetura de testes unitários para validá-los.
Para essa implementação é essencial porque muitas funções utilizam stdin,
dificultando automação de testes unitários.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// Damos um apelido 'booleano' aos inteiros 0 = FALSE e (diferente de zero = TRUE),
// assim o compilador consegue realizar operações booleanas implícitamente com inteiros nas condições (if,else)
// e nos laços (while,do,etc).
#define BOOL int
#define TRUE 1
#define FALSE 0

// Damos um apelido para quando não há um vencedor (retornando 'EMPATE_*' = NULL significa que não há uma instância 
// representando um vencedor).
#define EMPATE_GINASTICA_ARTISTICA NULL

// Como os parâmetros abaixo são regras do enunciado do serviço,
// podemos colocar como uma constante #define. Isso provê
// a facilidade de utilizá-las para definir tamanho de um array ou/em tipos estruturados.
// (que não é aceito pelo compilador caso sejam declaradas como const <tipo> <variável> = <valor>).
#define GINASTICA_NUMERO_ADVERSARIOS 2
#define GINASTICAARTISTICA_NOME_ADVERSARIO_MAXIMO 20
#define NUMERO_NOTAS 5
#define NOTAS_TAMANHO_BUFFER 100

static const char* const pMENSAGEM_ENTRADA_NOTAS = "Entre com as %d notas do adversário %d: (Exemplo: 9.7,10.0,...): ";
static const char* const pERROR_MESSAGE_NOTAS_INVALIDAS = "Há um problema com as notas fornecidas. Forneça cinco notas, de 0.0 a 10.0, separadas por vírgulas. Exemplo: 9.7,10.0,2.5,7.4,4.35.";
static const char* const STR_MODALIDADE_GINASTICA_ARTISTICA = "2";

// Estruturas de dados. Proporcionam o agrupamento
// de informações relacionadas e facilitam os algoritmos de sorting
// e identificação do vencedor.
struct AdversarioGinasticaArtistica{
    char NOME[GINASTICAARTISTICA_NOME_ADVERSARIO_MAXIMO];
    float notas[NUMERO_NOTAS];
};

struct RankingMediasGinasticaArtistica{
    int adversarios[GINASTICA_NUMERO_ADVERSARIOS];
    float media[GINASTICA_NUMERO_ADVERSARIOS];
};

/**
    Valida a modalidade selecionada pelo usuário.

    @param pEntrada buffer de string contendo o que o usuário digitou como modalidade selecionada.
    @return TRUE (modalidade implementada) ou FALSE (modalidade não-implementada)
*/
BOOL validaModalidadeGinasticaArtistica(char* pEntrada);

/**
    Valida a modalidade selecionada pelo usuário.

    @param pEntrada buffer de string contendo as notas (float), separadas por vírgulas.
    @param notas array contendo as notas (float) identificadas no parâmetro pEntrada.
    @return TRUE (identificadas todas as notas como válidas) ou FALSE (uma ou mais ou todas as notas são inválidas)
*/
BOOL validaNotas(char* pEntrada, float notas[]);

/**
    Ordena as notas, da menor para a maior.

    @param adversario identifica o número do usuário (1,2,3, etc).
    @param notas array contendo as notas (float) identificadas no parâmetro pEntrada.
    @param padversario pointer para instância AdversarioGinasticaArtistica, para receber seu nome identificador
    e suas notas ordenadas.
*/
void OrdenaRankingNotas(const int adversario, const float notas[], struct AdversarioGinasticaArtistica* padversario);

/**
    Identifica o vencedor da competição de ginástica artística considerando todas as regras do enunciado do exercício.

    @param adversarios array de AdversarioGinasticaArtistica representando os adversários.
    @return AdversarioGinasticaArtistica* pointer para o adversário no parâmetro adversarios identificado como vencedor.
    Ou NULL caso haja empate.
*/
const struct AdversarioGinasticaArtistica* const vencedorGinasticaArtistica(const struct AdversarioGinasticaArtistica adversarios[]);

#endif