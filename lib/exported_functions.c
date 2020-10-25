#include "functions_stdin.h"
#include "functions_arremesso.h"
#include "exported_functions.h"

// Mensagens de sistema.
static const char* const pENTRADA_MODALIDADE_MENSAGEM = "Digite o número da modalidade (1-Arremesso de Peso, 2-Ginástica Artística): ";
static const char* const pMODALIDADE_DESCONHECIDA_MENSAGEM = "Modalidade desconhecida. \nDigite o número da modalidade (1-Arremesso de Peso, 2-Ginástica Artística): ";
static const char* const pVENCEDOR_MODALIDADE_ARREMESSO_MENSAGEM = "Vencedor da modalidade Arremesso de Peso: %s";
static const char* const pEMPATE_MENSAGEM = "EMPATE";

// Protótipo da função de execução da modalidade de Arremesso de Peso.
void iniciaModalidadeArremessoDePeso(void);

void iniciaCompeticao(void)
{
    BOOL tentarModalidadeNovamente = TRUE;
    while(tentarModalidadeNovamente)
    {
        // fgets vai adicionar o retorno de linha e um terminador zero no final do buffer fornecido.
        // No entanto, o retorno de linha no Windows são dois caracteres ('\r' e '\n'), enquanto
        // que no Linux é apenas um ('\n'), portanto WINDOWS_TERMINADOR_DE_LINHA = 3 = '\r\n\0'.
        // As validações dos módulos *.c das competições irão tratar corretamente essa diferença 
        // de retorno de linha entre Linux e Windows.
        char buffMODALIDADE[TAMANHO_MODALIDADE+WINDOWS_TERMINADOR_DE_LINHA] = {'\0'};

        // Passo 1: Identifica qual é a modalidade de competição a ser avaliada.
        lerEntrada(buffMODALIDADE, TAMANHO_MODALIDADE+WINDOWS_TERMINADOR_DE_LINHA, pENTRADA_MODALIDADE_MENSAGEM);

        if(validaModalidadeArremesso(buffMODALIDADE))
        {
            // Passo 2: Executa a modalidade de competição selecionada.
            iniciaModalidadeArremessoDePeso();
            tentarModalidadeNovamente = FALSE;
        }
        // else if(validaModalidadeGinastica(buffMODALIDADE, pERROR_MESSAGE))
        // {
        //     tentarModalidadeNovamente = FALSE;
        // }
        else
        {
            printf(pMODALIDADE_DESCONHECIDA_MENSAGEM, "");
            continue;
        }
    }
}

// Implementação da função de execução da modalidade de Arremesso de Peso.
void iniciaModalidadeArremessoDePeso(void)
{
    // Solicita a entrada de dados dos arremessos dos adversários, processa e mostra o resultado.
    BOOL tentarLerArremessosAdversarioNovamente = TRUE;
    struct AdversarioArremessoPeso adversarios[ARREMESSO_NUMERO_ADVERSARIOS];

    for(int i = 0; i < ARREMESSO_NUMERO_ADVERSARIOS; i++)
    {
        while(tentarLerArremessosAdversarioNovamente)
        {
            // fgets vai adicionar o retorno de linha e um terminador zero no final do buffer fornecido.
            // No entanto, o retorno de linha no Windows são dois caracteres ('\r' e '\n'), enquanto
            // que no Linux é apenas um ('\n'), portanto WINDOWS_TERMINADOR_DE_LINHA = 3 = '\r\n\0'.
            // As validações dos módulos *.c das competições irão tratar corretamente essa diferença 
            // de retorno de linha entre Linux e Windows.
            char buffARREMESSOS[ARREMESSOS_TAMANHO_BUFFER+WINDOWS_TERMINADOR_DE_LINHA] = {'\0'};
            float arremessos[NUMERO_ARREMESSOS] = {0.0f};

            // A mensagem pMENSAGEM_ENTRADA_ARREMESSOS também espera formatação para inserir dinamicamente
            // na mensagem o número de arremessos esperado e o número do adversário. 1K é mais do que suficiente.
            char MENSAGEM_ENTRADA_ARREMESSOS_BUFFER[1024] = {'\0'};
            sprintf(MENSAGEM_ENTRADA_ARREMESSOS_BUFFER, pMENSAGEM_ENTRADA_ARREMESSOS, NUMERO_ARREMESSOS, i+1);

            // Solicita os arremessos do adversário.
            lerEntrada(buffARREMESSOS, ARREMESSOS_TAMANHO_BUFFER+WINDOWS_TERMINADOR_DE_LINHA, MENSAGEM_ENTRADA_ARREMESSOS_BUFFER);
            // Incorretos? Solicita novamente/eternamente até o usuário digitá-los corretamente.
            tentarLerArremessosAdversarioNovamente = !validaArremessos(buffARREMESSOS, arremessos);
            if(tentarLerArremessosAdversarioNovamente)
                printf(pERROR_MESSAGE_ARREMESSOS_INVALIDOS, "");
            else  // Copia e ordena os arremessos desse adversário para posterior cálculo do vencedor.
                OrdenaRankingArremessos(i+1, arremessos, &adversarios[i]);
        }
        tentarLerArremessosAdversarioNovamente = TRUE;
    }

    // Calcula o vencedor. A função é recursiva, portanto o primeiro parâmetro é zero e aumentado
    // internamente para o cálculo do segundo melhor arremesso.
    const struct AdversarioArremessoPeso* pvencedor = vencedorArremessoPeso(0, adversarios);
    printf(pVENCEDOR_MODALIDADE_ARREMESSO_MENSAGEM, pvencedor == EMPATE_ARREMESSO ? pEMPATE_MENSAGEM : pvencedor->NOME);
}