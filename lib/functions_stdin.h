#ifndef CABECALHO_FUNCTIONS_STDIN_INCLUDED
#define CABECALHO_FUNCTIONS_STDIN_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAMANHO_MODALIDADE 1
#define WINDOWS_TERMINADOR_DE_LINHA 3

void converteTerminadorEmZero(char* buff);
void lerEntrada(char* buffer, const int maxbuffsize, const char* pENTRADA_MENSAGEM);

#endif