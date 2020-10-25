# PARADIG-PROG-N1-ESTRUT-C99

Tutorial em vídeo demonstrando a aplicação do paradigma estruturado e detalhando as escolhas e implementações dessa aplicação: https://drive.google.com/drive/folders/1ZE8VH6yoOUFDHSy5b-DT3kto_GEmtxVS?usp=sharing  

Atividade de entrega para a aula de Paradigmas de Linguagens de Programação (prof. Bruno Moritani).  

Paradigmas: Estruturado  
Linguagem: C (C99 standard)  
Compilador: GCC com CMake (também compatível com MingW no Windows)  

## Passo 1: Dependências

Uma distribuição Linux  
Git >= 2.17.1, CMake >= 3.5 e (GCC >= 7.5.0 ou CLang >= 6.0.0)  
ou  
MacOS  
Git >= 2.17.1, CMake >= 3.5 e CLang >= 6.0.0  
Leia: https://code.visualstudio.com/docs/cpp/lldb-mi  

Exemplo de instalação num Ubuntu 18.04:  
>*#apt install -y git cmake make gcc clang*

Visual Studio Code  
Extensões:  
C/C++ (ms-vscode.cpptools)  
CMake Tools (ms-vscode.cmake-tools)  

## Passo 2: Build, depuração e Testes Unitários (Visual Studio Code)

Abra a pasta desse repositório git baixado localmente no Visual Studio Code. Visual Studio Code imediatamente irá procurar pelos compiladores disponíveis e perguntar qual vc quer utilizar (CLang ou GCC). Caso prefira GCC, escolha a opção do C99 standard, pois várias configurações (CMake) e funções utilizadas nesse projeto dependem dessa versão da linguagem C.

Você pode ir agora em 'Run' e encontrar as seguintes opções de build e depuração:  
*CMake build and debug GDB* (Build e depuração da aplicação usando GCC + GDB)  
*CMake build and unittest GDB* (Build e depuração dos testes unitários usando GCC + GDB)  
*CMake build and debug LLDB* (Build e depuração da aplicação usando CLang + LLDB)  
*CMake build and debug unittest LLDB* (Build e depuração da aplicação usando CLang + LLDB)  

No canto inferior direito do VSCode, você pode rodar os testes clicando em 'Run CTest'.

## Passo 3: Build e Testes Unitários (Linha de Comando - sem IDE)

Num terminal:  

(Até a entrega, esse repositório é PRIVADO)  
*$git clone https://github.com/mpeschke/PARADIG-PROG-N1-ESTRUT-C99.git*  
*$cd PARADIG-PROG-N1-ESTRUT-C99/*  
*$mkdir build*  
*$cd build/*  
*$cmake -DCMAKE_BUILD_TYPE=Debug ../.*  
*$cmake --build .*  
*$ctest*