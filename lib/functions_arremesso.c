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
    // Por exemplo, podemos determinar que foram fornecidos TRÊS arremessos, separados por
    // DUAS vírgulas:
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
        // Bugfix: obviamente a distância do arremesso tem que ser maior que zero.
        if(candidate < 0.0f)
            return FALSE;
        arremessos[i] = candidate;
    }

    return TRUE;
}

void OrdenaRankingArremessos(const int adversario, const float arremessos[], struct AdversarioArremessoPeso* padversario)
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

const struct AdversarioArremessoPeso* const vencedorArremessoPeso(const int melhormarca, const struct AdversarioArremessoPeso adversarios[])
{
    // Pelo enunciado do exercício, deve-se considerar apenas a segunda melhor marca como critério de desempate.
    if(melhormarca > 1)
        return EMPATE_ARREMESSO;

    struct RankingArremessoPeso melhoresmarcas;

    for (int a = 0; a < ARREMESSO_NUMERO_ADVERSARIOS; ++a)
    {
        melhoresmarcas.adversarios[a] = a;
        melhoresmarcas.melhoresmarcas[a] = adversarios[a].arremessos[NUMERO_ARREMESSOS-1-melhormarca];
    }

    // Bubble sort para ordenar de acordo com a MELHOR marca dos adversários.
    for (int i = 0; i < ARREMESSO_NUMERO_ADVERSARIOS; ++i)
        for (int j = 0; j < ARREMESSO_NUMERO_ADVERSARIOS; j++)
        {
            // Em ordem crescente
            if(melhoresmarcas.melhoresmarcas[i] < melhoresmarcas.melhoresmarcas[j])
            {
                float melhormarca = melhoresmarcas.melhoresmarcas[i];
                int melhoradversario = melhoresmarcas.adversarios[i];

                melhoresmarcas.melhoresmarcas[i] = melhoresmarcas.melhoresmarcas[j];
                melhoresmarcas.adversarios[i] = melhoresmarcas.adversarios[j];

                melhoresmarcas.melhoresmarcas[j] = melhormarca;
                melhoresmarcas.adversarios[j] = melhoradversario;
            }
        }

    // Primeiro passo: verificamos se não houve um empate.
    const struct AdversarioArremessoPeso* pVencedor = 
        melhoresmarcas.melhoresmarcas[ARREMESSO_NUMERO_ADVERSARIOS-1] == melhoresmarcas.melhoresmarcas[ARREMESSO_NUMERO_ADVERSARIOS-2] ? 
            EMPATE_ARREMESSO : 
            &adversarios[melhoresmarcas.adversarios[ARREMESSO_NUMERO_ADVERSARIOS-1]];

    // Segundo passo: oh-oh, houve empate nos melhores arremessos dos adversários. Vamos
    // usar o critério de desempate (segundo melhor arremesso) usando essa mesma função de forma recursiva.
    if(pVencedor != EMPATE_ARREMESSO)
        return pVencedor;
    else
        return vencedorArremessoPeso(melhormarca+1, adversarios);
}