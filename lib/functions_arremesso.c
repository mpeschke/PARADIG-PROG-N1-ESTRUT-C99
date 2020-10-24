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
#include "functions_arremesso.h"

// Damos um apelido para quando não há um vencedor (retornando 'EMPATE_*' = NULL significa que não há uma instância 
// representando um vencedor).
#define EMPATE_ARREMESSO NULL

// Como os parâmetros abaixo são regras do enunciado do serviço,
// podemos colocar como uma constante #define. Isso provê
// a facilidade de utilizá-las para definir tamanho de um array ou/em tipos estruturados.
// (que não é aceito pelo compilador caso sejam declaradas como const <tipo> <variável> = <valor>).
#define NUM_ADVERSARIOS 2
#define FGETS_BUFFER_SIZE 100

char* const STR_MODALIDADE_ARREMESSO = "1";
const char ENTRADA_ARREMESSOS_DELIM[] = ",";

BOOL validaModalidadeArremesso(char* pEntrada, const char* pERROR_MESSAGE)
{
    BOOL modalidadevalida = (strcmp(pEntrada, STR_MODALIDADE_ARREMESSO) == 0);

    pERROR_MESSAGE = modalidadevalida ? NULL : pERROR_MESSAGE_MODALIDADE_ARREMESSOS_INVALIDA;

    return modalidadevalida;
}

BOOL validaArremessos(char* pEntrada, float arremessos[], const char* pERROR_MESSAGE)
{
    int numdelim = 0;
    pERROR_MESSAGE = pERROR_MESSAGE_ARREMESSOS_INVALIDOS;

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
        strarremessos[numdelim++] = ptr;
        if(numdelim > (NUMERO_ARREMESSOS - 1))
            return FALSE;
		ptr = strtok(NULL, ENTRADA_ARREMESSOS_DELIM);
	}

    // Segunda parte: temos os valores dos arremessos em strings,
    // fazemos uma conversão léxica para ponto flutuante (metros).
    // Todos os valores tem que obrigatoriamente representar um ponto flutuante.
    for(int i = 0; i < NUMERO_ARREMESSOS; i++)
    {
        char* end;
        float candidate = strtof(strarremessos[i], &end);
        if(errno == ERANGE)
        {
            errno = 0;
            return FALSE;
        }
        arremessos[i] = candidate;
    }

    pERROR_MESSAGE = NULL;
    return TRUE;
}

float notaFinalArremesso(float arremessos[])
{
    return 0.0f;
}

void AdversarioArremessoPeso(const float arremessos[], struct AdversarioArremessoPeso* padversario)
{
    //sprintf(padversario->NOME, "Adversario %d", i+1);
    for(int j = 0; j < NUMERO_ARREMESSOS; j++)
        padversario->arremessos[j] = arremessos[j];
}

const struct AdversarioArremessoPeso* const vencedorArremessoPeso(const struct AdversarioArremessoPeso adversarios[])
{
    return EMPATE_ARREMESSO;
}