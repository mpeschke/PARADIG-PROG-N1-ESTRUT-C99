#ifndef CABECALHO_TESTS_FUNCTIONS_H_INCLUDED
#define CABECALHO_TESTS_FUNCTIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions_arremesso.h"
#include "functions_ginastica.h"
#include "functions_stdin.h"

/**
    Identifica e executa os testes unitários para as funções da biblioteca lib.

    @param funcao inteiro identificando qual é a função da biblioteca a ser testada.
    @param argc número de itens no parâmetro argv
    @param argv contém todos os parâmetros da linha de comando da aplicação que 
    executa os testes unitários.
*/
void unittest_suites(const int funcao, int argc, char* argv[]);

#endif
