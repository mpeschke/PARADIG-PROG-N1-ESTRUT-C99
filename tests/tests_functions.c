#include "tests_functions.h"

static const char* const strTRUE = "TRUE";
static const char* const strFALSE = "FALSE";

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
            float arremessos[3] = {0.0f};
            BOOL ret = validaArremessos(buff, arremessos);
            printf("Retorno: %s.", ret ? strTRUE : strFALSE);
            break;
        }
        default:
            break;
    };
}

int main(int argc, char* argv[])
{
    unittest_suites(atoi(argv[1]), argc, argv);

    return 0;
}