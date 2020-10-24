#include "functions_stdin.h"
#include "functions_arremesso.h"
#include "exported_functions.h"

void iniciaCompeticao(void)
{
    BOOL tentarModalidadeNovamente = TRUE;
    while(tentarModalidadeNovamente)
    {
        // fgets vai adicionar o retorno de linha e um terminador zero no final do buffer fornecido.
        // No entanto, o terminador no Windows são dois caracteres ('\r' e '\n'), enquanto
        // que no Linux é apenas um ('\n'). Portanto 3 = '\r\n\0'.
        char buffMODALIDADE[TAMANHO_MODALIDADE+3] = {'\0'};
        char* const pERROR_MESSAGE = NULL;

        // Passo 1: Identifica qual é a modalidade de competição a ser avaliada.
        lerEntrada(buffMODALIDADE, TAMANHO_MODALIDADE, pENTRADA_MODALIDADE_MENSAGEM);

        float arremessos[] = {0.0f};
        if(validaModalidadeArremesso(buffMODALIDADE, pERROR_MESSAGE))
        {
            // Passo 2: Solicita a entrada de dados e processa o resultado.
            char buffARREMESSOS[ARREMESSOS_TAMANHO_BUFFER] = {'\0'};
            BOOL tentarArremessoNovamente = TRUE;
            while(tentarArremessoNovamente)
            {
                struct AdversarioArremessoPeso adversarios[ARREMESSO_NUMERO_ADVERSARIOS];
                for(int i = 0; i < ARREMESSO_NUMERO_ADVERSARIOS; i++)
                {
                    lerEntrada(buffARREMESSOS, ARREMESSOS_TAMANHO_BUFFER, pMENSAGEM_ENTRADA_ARREMESSOS);
                    while(!validaArremessos(buffARREMESSOS, arremessos, pERROR_MESSAGE))
                        printf(pERROR_MESSAGE, "");
                }
            }
            tentarModalidadeNovamente = FALSE;
        }
        // else if(validaModalidadeGinastica(buffMODALIDADE, pERROR_MESSAGE))
        // {
        //     tentarModalidadeNovamente = FALSE;
        // }
        else
        {
            printf(pERROR_MESSAGE, "");
            continue;
        }
    }
}