#ifndef CABECALHO_EXPORTED_FUNCTIONS_INCLUDED
#define CABECALHO_EXPORTED_FUNCTIONS_INCLUDED
/*
Esse header se destina a ser compartilhado com as aplicações que consomem essa biblioteca.
Contém todas as funções que são exportadas (públicas).
*/
#include <stdlib.h>
#include <stdio.h>

static const char* const pENTRADA_MODALIDADE_MENSAGEM = "Digite o número da modalidade (1-Arremesso de Peso, 2-Ginástica Artística): ";

// Inicia o processamento de dados da competição escolhida.
void iniciaCompeticao(void);

#endif