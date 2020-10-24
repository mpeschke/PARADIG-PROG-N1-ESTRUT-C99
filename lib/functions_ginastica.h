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
#define NUM_ADVERSARIOS 2
#define NOME_ADVERSARIO_MAXIMO 20
#define NOTAS_NUMERO 5

char* const pERROR_MESSAGE_NOTAS_INVALIDAS = "Há um problema com as notas fornecidas. Forneça cinco notas, de 0.0 a 10.0, separadas por vírgulas. Exemplo: 9.7,10.0,2.5,7.4,4.35.";

char* const STR_MODALIDADE_GINASTICA_ARTISTICA = "2";

// Estruturas de dados. Proporciona o agrupamento
// de informações relacionadas.
struct AdversarioGinasticaArtistica{
    char NOME[NOME_ADVERSARIO_MAXIMO];
    float notas[NOTAS_NUMERO];
};

// Funções.
BOOL validaModalidadeGinastica(const char* const pEntrada, const char* pERROR_MESSAGE);

BOOL validaNotas(const char* const pEntrada, float notas[], char* const pERROR_MESSAGE);

const struct AdversarioGinasticaArtistica* const vencedorGinasticaArtistica(const struct AdversarioGinasticaArtistica adversarios[]);

#endif