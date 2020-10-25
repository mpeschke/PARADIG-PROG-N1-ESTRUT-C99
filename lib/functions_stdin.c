#include "functions_stdin.h"

// Contém os caracteres terminadores de linha, tanto para Linux como para Windows.
static const char* PLATFORMINDEPENDENTSTREND = "\r\n";

/**
    Essa função coloca um caracter nulo na primeira instância desses
    caracteres terminadores, garantindo um buffer com apenas o que o
    usuário digitou, sem os terminadores de linha.

    @param buff buffer de string retornado pela função fgets (terá no final os caracteres
    terminadores de linha e zero).
*/
void converteTerminadorEmZero(char* buff)
{buff[strcspn(buff, PLATFORMINDEPENDENTSTREND)] = '\0';}

/**
    Digita uma mensagem com instruções para o usuário e captura
    o que o usuário digitou.

    @param buffer buffer de string para captura do stdin.
    @param maxbuffsize limite para a função fgets coletar dados do stdin (função segura).
    @param pENTRADA_MENSAGEM mensagem com instruções para o usuário.
*/
void lerEntrada(char* buffer, const int maxbuffsize, const char* pENTRADA_MENSAGEM)
{
    printf("%s", pENTRADA_MENSAGEM);
    fgets(buffer, maxbuffsize, stdin);
}

