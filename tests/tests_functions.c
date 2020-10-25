#include "tests_functions.h"

static const char* const strTRUE = "TRUE";
static const char* const strFALSE = "FALSE";
static const char* const strEMPATE = "EMPATE";

void unittest_suites(const int funcao, int argc, char* argv[])
{
    char buff[1024] = {'\0'};

    switch(funcao)
    {
        case 1: //validaModalidadeArremesso
        {
            char buff[1024] = {'\0'};
            strncpy(buff, argv[2], 1024);
            BOOL ret = validaModalidadeArremesso(buff);
            printf("Retorno: %s. Modalidade: '%s'.", ret ? strTRUE : strFALSE, buff);
            break;
        }
        case 2: //validaArremessos
        {
            char buff[1024] = {'\0'};
            strncpy(buff, argv[2], 1024);
            float arremessos[NUMERO_ARREMESSOS] = {0.0f};
            BOOL ret = validaArremessos(buff, arremessos);
            printf("Retorno: %s.", ret ? strTRUE : strFALSE);
            break;
        }
        case 3: //OrdenaRankingArremessos
        {
            // Primeiro: obtém o array de arremessos através da
            // string fornecida pelo teste unitário.
            char buff[1024] = {'\0'};
            strncpy(buff, argv[2], 1024);
            float arremessos[NUMERO_ARREMESSOS] = {0.0f};
            BOOL ret = validaArremessos(buff, arremessos);
            // Segundo: 'instancia' o AdversarioArremessoPeso
            // e ordena os resultados dos seus arremessos.
            // O propósito desse teste unitário é demonstrar
            // que o último arremesso é sua melhor marca.
            struct AdversarioArremessoPeso adversario;
            for(int a = 0; a < NUMERO_ARREMESSOS; a++)
                adversario.arremessos[a] = arremessos[a];
            OrdenaRankingArremessos(0, arremessos, &adversario);
            printf("Melhor arremesso: %.2f", adversario.arremessos[NUMERO_ARREMESSOS-1]);

            break;
        }
        case 4: //vencedorArremessoPeso
        {
            struct AdversarioArremessoPeso adversarios[2];
            // Primeiro: instancia e ordena os arremessos do primeiro adversário.
            char adversario1arremessos[1024] = {'\0'};
            strncpy(adversario1arremessos, argv[2], 1024);
            float arremessos1[NUMERO_ARREMESSOS] = {0.0f};
            validaArremessos(adversario1arremessos, arremessos1);
            OrdenaRankingArremessos(1, arremessos1, &adversarios[0]);
            // Segundo: instancia e ordena os arremessos do segundo adversário.
            char adversario2arremessos[1024] = {'\0'};
            strncpy(adversario2arremessos, argv[3], 1024);
            float arremessos2[NUMERO_ARREMESSOS] = {0.0f};
            validaArremessos(adversario2arremessos, arremessos2);
            OrdenaRankingArremessos(2, arremessos2, &adversarios[1]);
            // Terceiro: identifica o vencedor.
            const struct AdversarioArremessoPeso* const pvencedor = vencedorArremessoPeso(0, adversarios);
            printf("Adversário vencedor: %s", pvencedor == EMPATE_ARREMESSO ? strEMPATE : pvencedor->NOME);

            break;
        }
        default:
            break;
    };
}

int main(int argc, char* argv[])
{
    // Lembrando que, nos sistemas operacionais Windows e Linux,
    // o primeiro argumento é sempre o caminho do executável.
    // O segundo argumento é sempre um inteiro que identifica a função
    // alvo dos testes unitários (hardcoded para auxiliar o template de testes unitários do CMake).
    unittest_suites(atoi(argv[1]), argc, argv);

    return 0;
}