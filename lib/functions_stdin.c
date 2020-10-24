#include "functions_stdin.h"

void lerEntrada(char* buffer, const int maxbuffsize, const char* pENTRADA_MENSAGEM)
{
    // Fornece um parâmetro dummy para silenciar um warning do compilador sobre ausência de parâmetros para o printf
    // (a string pENTRADA_MENSAGEM não é formatada).
    printf(pENTRADA_MENSAGEM, "");
    fgets(buffer, maxbuffsize, stdin);
}

