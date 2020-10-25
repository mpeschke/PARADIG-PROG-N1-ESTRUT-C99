#include "exported_functions.h"

int main()
{
    // Exemplo de BAIXO ACOPLAMENTO e ALTA COESÃO entre componentes de um sistema. A interface não conhece absolutamente nenhum
    // detalhe da implementação das competições de Arremesso de Peso e Ginástica Artística. Como esse modelo é possível, 
    // por exemplo, adicionar novas competições, mudar as regras do exercício, etc, sem precisar recompilar o cliente que consome a biblioteca.

    // Inicia a competição, solicitando a entrada de dados para calcular os resultados.
    iniciaCompeticao();

    return 0;
}