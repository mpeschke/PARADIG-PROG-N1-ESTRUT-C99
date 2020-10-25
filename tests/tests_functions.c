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
        case 5: //validaModalidadeGinasticaArtistica
        {
            char buff[1024] = {'\0'};
            strncpy(buff, argv[2], 1024);
            BOOL ret = validaModalidadeGinasticaArtistica(buff);
            printf("Retorno: %s. Modalidade: '%s'.", ret ? strTRUE : strFALSE, buff);
            break;
        }
        case 6: //validaNotas
        {
            char buff[1024] = {'\0'};
            strncpy(buff, argv[2], 1024);
            float notas[NUMERO_NOTAS] = {0.0f};
            BOOL ret = validaNotas(buff, notas);
            printf("Retorno: %s.", ret ? strTRUE : strFALSE);
            break;
        }
        case 7: //OrdenaRankingNotas
        {
            char buff[1024] = {'\0'};
            strncpy(buff, argv[2], 1024);
            float notas[NUMERO_NOTAS] = {0.0f};
            BOOL ret = validaNotas(buff, notas);
            // Segundo: 'instancia' o AdversarioGinasticaArtistica
            // e ordena suas notas.
            // O propósito desse teste unitário é demonstrar
            // que a última nota é sua melhor.
            struct AdversarioGinasticaArtistica adversario;
            for(int a = 0; a < NUMERO_NOTAS; a++)
                adversario.notas[a] = notas[a];
            OrdenaRankingNotas(0, notas, &adversario);
            printf("Melhor nota: %.2f", adversario.notas[NUMERO_NOTAS-1]);

            break;
        }
        case 8: //vencedorGinasticaArtistica
        {
            struct AdversarioGinasticaArtistica adversarios[2];
            // Primeiro: instancia e ordena as notas do primeiro adversário.
            char adversario1notas[1024] = {'\0'};
            strncpy(adversario1notas, argv[2], 1024);
            float notas1[NUMERO_ARREMESSOS] = {0.0f};
            validaNotas(adversario1notas, notas1);
            OrdenaRankingNotas(1, notas1, &adversarios[0]);
            // Segundo: instancia e ordena as notas do segundo adversário.
            char adversario2notas[1024] = {'\0'};
            strncpy(adversario2notas, argv[3], 1024);
            float notas2[NUMERO_ARREMESSOS] = {0.0f};
            validaNotas(adversario2notas, notas2);
            OrdenaRankingNotas(2, notas2, &adversarios[1]);
            // Terceiro: identifica o vencedor.
            const struct AdversarioGinasticaArtistica* const pvencedor = vencedorGinasticaArtistica(adversarios);
            printf("Adversário vencedor: %s", pvencedor == EMPATE_GINASTICA_ARTISTICA ? strEMPATE : pvencedor->NOME);

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