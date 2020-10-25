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
#include "functions_ginastica.h"

static const char* const STR_MODALIDADE_GINASTICA = "2";
const char ENTRADA_NOTAS_DELIM[] = ",";

BOOL validaModalidadeGinasticaArtistica(char* pEntrada)
{
    // Converte a primeira instância de terminador de linha em '\0', 
    // independente de ser '\r\n' (Windows) ou '\n' (Linux)
    converteTerminadorEmZero(pEntrada);
    return (strcmp(pEntrada, STR_MODALIDADE_GINASTICA) == 0);
}

BOOL validaNotas(char* pEntrada, float notas[])
{
    int numdelim = 0;

    // Primeira parte: usamos o strtok para inserir terminadores nulos
    // onde ele encontra o separador de valores de notas fornecidos pelo usuário.
    // Por exemplo, podemos determinar que foram fornecidas CINCO notas, separadas por
    // QUATRO vírgulas:
    // 0.0,1.0,3.44,5.0,10.0
    char *ptr = strtok(pEntrada, ENTRADA_NOTAS_DELIM);
    char *strnotas[NUMERO_NOTAS] = {NULL};

	while(ptr)
	{
        // Encontrou um número maior que o esperado de notas? A entrada é inválida.
        if(numdelim == NUMERO_NOTAS)
            return FALSE;
        strnotas[numdelim++] = ptr;
		ptr = strtok(NULL, ENTRADA_NOTAS_DELIM);
	}

    // Se encontrou um número menor de notas fornecidas, a entrada também é inválida.
    if(numdelim < NUMERO_NOTAS)
        return FALSE;

    // Segunda parte: temos os valores das notas em strings,
    // fazemos uma conversão léxica para ponto flutuante (de 0.0 a 10.0).
    for(int i = 0; i < NUMERO_NOTAS; i++)
    {
        char* end;
        float candidate = strtof(strnotas[i], &end);
        // O valor fornecido não pode ser representando como um ponto flutuante.
        if((errno == ERANGE) || (end == strnotas[i]))
        {
            errno = 0;
            return FALSE;
        }
        // Notas apenas entre 0.0 e 10.0.
        if((candidate < 0.0f) || (candidate > 10.0f))
            return FALSE;
        notas[i] = candidate;
    }

    return TRUE;
}

void OrdenaRankingNotas(const int adversario, const float notas[], struct AdversarioGinasticaArtistica* padversario)
{
    sprintf(padversario->NOME, "Adversario %d", adversario);
    for(int a = 0; a < NUMERO_NOTAS; a++)
        padversario->notas[a] = notas[a];

    // Bubble sort para facilitar o cálculo da média e exclusão da pior nota.
    for (int i = 0; i < NUMERO_NOTAS; ++i)
        for (int j = 0; j < NUMERO_NOTAS; j++)
        {
            // Em ordem crescente
            if(padversario->notas[i] < padversario->notas[j])
            {
                float tmp = padversario->notas[i];
                padversario->notas[i] = padversario->notas[j];
                padversario->notas[j] = tmp;
            }
        }
}

const struct AdversarioGinasticaArtistica* const vencedorGinasticaArtistica(const struct AdversarioGinasticaArtistica adversarios[])
{
    struct RankingMediasGinasticaArtistica melhoresmedias;

    for (int a = 0; a < GINASTICA_NUMERO_ADVERSARIOS; ++a)
    {
        melhoresmedias.adversarios[a] = a;
        float somadasmelhoresnotas = 0.0f;
        // Considera apenas as (NUMERO_NOTAS-1) melhoras notas para o cálculo da média de cada adversário.
        // Ou seja, descarta a pior nota.
        for (int n = (NUMERO_NOTAS-1); n > 0; n--)
        {
            somadasmelhoresnotas += adversarios[a].notas[n];
        }
        melhoresmedias.media[a] = (somadasmelhoresnotas / (float)(NUMERO_NOTAS-1));
    }

    // Bubble sort para ordenar de acordo com a MELHOR média dos adversários.
    for (int i = 0; i < GINASTICA_NUMERO_ADVERSARIOS; ++i)
        for (int j = 0; j < GINASTICA_NUMERO_ADVERSARIOS; j++)
        {
            // Em ordem crescente
            if(melhoresmedias.media[i] < melhoresmedias.media[j])
            {
                float melhormedia = melhoresmedias.media[i];
                int melhoradversario = melhoresmedias.adversarios[i];

                melhoresmedias.media[i] = melhoresmedias.media[j];
                melhoresmedias.adversarios[i] = melhoresmedias.adversarios[j];

                melhoresmedias.media[j] = melhormedia;
                melhoresmedias.adversarios[j] = melhoradversario;
            }
        }

    // Comparamos as melhores médias dos dois melhores adversários e definimos o vencedor.
    return melhoresmedias.media[GINASTICA_NUMERO_ADVERSARIOS-1] == melhoresmedias.media[GINASTICA_NUMERO_ADVERSARIOS-2] ? 
                EMPATE_GINASTICA_ARTISTICA : 
                &adversarios[melhoresmedias.adversarios[GINASTICA_NUMERO_ADVERSARIOS-1]];
}