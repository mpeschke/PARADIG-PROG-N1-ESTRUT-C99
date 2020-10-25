#include "functions_stdin.h"

static const char* PLATFORMINDEPENDENTSTREND = "\r\n";

/*
 * Essa função coloca um caracter nulo na primeira instância desses
 * caracteres terminadores, garantindo um buffer com apenas o que o
 * usuário digitou, sem os terminadores de linha.
*/
void converteTerminadorEmZero(char* buff)
{buff[strcspn(buff, PLATFORMINDEPENDENTSTREND)] = 0;}

void lerEntrada(char* buffer, const int maxbuffsize, const char* pENTRADA_MENSAGEM)
{
    // Fornece um parâmetro dummy para silenciar um warning do compilador sobre ausência de parâmetros para o printf
    // (a string pENTRADA_MENSAGEM não é formatada).
    //printf("%s", pENTRADA_MENSAGEM);
    printf("%s", pENTRADA_MENSAGEM);
    fgets(buffer, maxbuffsize, stdin);
}

