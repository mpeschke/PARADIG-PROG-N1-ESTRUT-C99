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
#include "functions_stdin.h"
#include "functions_arremesso.h"

// Damos um apelido para quando não há um vencedor (retornando 'EMPATE_*' = NULL significa que não há uma instância 
// representando um vencedor).
#define EMPATE_ARREMESSO NULL

// Como os parâmetros abaixo são regras do enunciado do serviço,
// podemos colocar como uma constante #define. Isso provê
// a facilidade de utilizá-las para definir tamanho de um array ou/em tipos estruturados.
// (que não é aceito pelo compilador caso sejam declaradas como const <tipo> <variável> = <valor>).
#define NUM_ADVERSARIOS 2

static const char* const STR_MODALIDADE_ARREMESSO = "1";
const char ENTRADA_ARREMESSOS_DELIM[] = ",";

BOOL validaModalidadeArremesso(char* pEntrada)
{
    // Converte a primeira instância de terminador de linha em '\0', 
    // independente de ser '\r\n' (Windows) ou '\n' (Linux)
    converteTerminadorEmZero(pEntrada);
    return (strcmp(pEntrada, STR_MODALIDADE_ARREMESSO) == 0);
}

BOOL validaArremessos(char* pEntrada, float arremessos[])
{
    int numdelim = 0;

    // Primeira parte: usamos o strtok para inserir terminadores nulos
    // onde ele encontra o separador de valores de arremessos fornecidos pelo usuário.
    // Assim podemos determinar que foram fornecidos TRÊS arremessos, separados por
    // DUAS vírgulas.
    // Por exemplo:
    // 45.2,3.0,42.44
    char *ptr = strtok(pEntrada, ENTRADA_ARREMESSOS_DELIM);
    char *strarremessos[NUMERO_ARREMESSOS] = {NULL};

	while(ptr)
	{
        // Encontrou um número maior que o esperado de arremessos? A entrada é inválida.
        if(numdelim == NUMERO_ARREMESSOS)
            return FALSE;
        strarremessos[numdelim++] = ptr;
		ptr = strtok(NULL, ENTRADA_ARREMESSOS_DELIM);
	}

    // Se encontrou um número menor de arremessos fornecidos, a entrada também é inválida.
    if(numdelim < NUMERO_ARREMESSOS)
        return FALSE;

    // Segunda parte: temos os valores dos arremessos em strings,
    // fazemos uma conversão léxica para ponto flutuante (metros).
    for(int i = 0; i < NUMERO_ARREMESSOS; i++)
    {
        char* end;
        float candidate = strtof(strarremessos[i], &end);
        // O valor fornecido não pode ser representando como um ponto flutuante.
        if((errno == ERANGE) || (end == strarremessos[i]))
        {
            errno = 0;
            return FALSE;
        }
        arremessos[i] = candidate;
    }

    return TRUE;
}

void AdversarioArremessoPeso(const int adversario, const float arremessos[], struct AdversarioArremessoPeso* padversario)
{
    sprintf(padversario->NOME, "Adversario %d", adversario);
    for(int a = 0; a < NUMERO_ARREMESSOS; a++)
        padversario->arremessos[a] = arremessos[a];

    // Bubble sort para facilitar a comparação dos arremessos entre os adversários.
    for (int i = 0; i < NUMERO_ARREMESSOS; ++i)
        for (int j = 0; j < NUMERO_ARREMESSOS; j++)
        {
            // Em ordem crescente
            if(padversario->arremessos[i] < padversario->arremessos[j])
            {
                float tmp = padversario->arremessos[i];
                padversario->arremessos[i] = padversario->arremessos[j];
                padversario->arremessos[j] = tmp;
            }
        }
}

const struct AdversarioArremessoPeso* const vencedorArremessoPeso(const struct AdversarioArremessoPeso adversarios[])
{
    return EMPATE_ARREMESSO;
}