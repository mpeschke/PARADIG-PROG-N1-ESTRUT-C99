set(C_STANDARD 99)
set(C_STANDARD ON)
cmake_minimum_required(VERSION 3.5)

include_directories(../lib)

file(GLOB_RECURSE UNITTESTSOURCES
    *.h
    *.c
)

add_executable(
    App-Unit-Tests
    ${UNITTESTSOURCES}
    )
target_link_libraries (App-Unit-Tests LINK_PUBLIC applib)

# Template to create unit tests for the applib
function(do_test_two_args testname target testid arg1 arg2 result)
  add_test(NAME ${testname}_${testid} COMMAND ${target} ${arg1} ${arg2})
  set_tests_properties(${testname}_${testid}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test_two_args)

do_test_two_args("Modalidade_converteTerminadorEmZero_Windows_CaminhoFeliz" App-Unit-Tests 1 1 "1\r\n" "Retorno: TRUE. Modalidade: '1'.")
do_test_two_args("Modalidade_converteTerminadorEmZero_Linux_CaminhoFeliz" App-Unit-Tests 2 1 "1\n" "Retorno: TRUE. Modalidade: '1'.")
do_test_two_args("Modalidade_converteTerminadorEmZero_Windows_ModalidadeErrada" App-Unit-Tests 3 1 "2\r\n" "Retorno: FALSE. Modalidade: '2'.")
do_test_two_args("Modalidade_converteTerminadorEmZero_Linux_ModalidadeErrada" App-Unit-Tests 4 1 "2\n" "Retorno: FALSE. Modalidade: '2'.")
do_test_two_args("Modalidade_converteTerminadorEmZero_Windows_ModalidadeErrada" App-Unit-Tests 5 1 "22222\r\n" "Retorno: FALSE. Modalidade: '22222'.")
do_test_two_args("Modalidade_converteTerminadorEmZero_Linux_ModalidadeErrada" App-Unit-Tests 6 1 "22222\n" "Retorno: FALSE. Modalidade: '22222'.")

# Notar que essa função jamais receberá um buffer vazio - se o usuário apenas aperta enter, fgets adiciona os caracteres terminadores de linha.
do_test_two_args("Modalidade_converteTerminadorEmZero_Windows_ModalidadeVazia" App-Unit-Tests 7 1 "\n\r" "Retorno: FALSE. Modalidade: ''.")
do_test_two_args("Modalidade_converteTerminadorEmZero_Linux_ModalidadeVazia" App-Unit-Tests 8 1 "\n" "Retorno: FALSE. Modalidade: ''.")

do_test_two_args("ArremessoDePeso_CaminhoFeliz" App-Unit-Tests 9 2 "1.0,2.0,3.0" "Retorno: TRUE.")
do_test_two_args("ArremessoDePeso_MenosArremessosQueOEsperado" App-Unit-Tests 10 2 "1.0,2.0" "Retorno: FALSE.")
do_test_two_args("ArremessoDePeso_MaisArremessosQueOEsperado" App-Unit-Tests 11 2 "1.0,2.0,3.0,4.0" "Retorno: FALSE.")
do_test_two_args("ArremessoDePeso_NenhumArremessoFornecido_Linux" App-Unit-Tests 12 2 "\n" "Retorno: FALSE.")
do_test_two_args("ArremessoDePeso_NenhumArremessoFornecido_Windows" App-Unit-Tests 13 2 "\r\n" "Retorno: FALSE.")
do_test_two_args("ArremessoDePeso_ArremessoNaoEhFloat" App-Unit-Tests 14 2 "1.0,oi,3.0" "Retorno: FALSE.")
do_test_two_args("ArremessoDePeso_ArremessoFloatMaximo" App-Unit-Tests 15 2 "3.40282e+38,2.0,3.0" "Retorno: TRUE.")
do_test_two_args("ArremessoDePeso_ArremessoFloatMinimo" App-Unit-Tests 16 2 "1.17548e-37,2.0,3.0" "Retorno: TRUE.")
do_test_two_args("ArremessoDePeso_ArremessoFloatOverflow" App-Unit-Tests 17 2 "3.40283e+38,2.0,3.0" "Retorno: FALSE.")
do_test_two_args("ArremessoDePeso_ArremessoFloatUnderflow" App-Unit-Tests 18 2 "1.17548e-40,2.0,3.0" "Retorno: FALSE.")
