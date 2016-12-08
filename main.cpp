/*
* Nome: SAR
* Autores: Felipe Sampaio de Souza, Pedro Henrique Mauad, Pedro Henrique Migliatti
* Pre-requisitos: Sistema Operacional Linux
* Entrada: [-c|-e|-l] + [nome diretorio| arquivo.sar]
* Descricao: Programa para execucao na linha de comando que arquiva e recupera o conteudo de um diretorio.
* 1)Argumentos: O primeiro argumento passado se refere a operacao que se deseja fazer e o segundo, com o que se deseja
  realizar a operacao indicada.
    -c = arquivar (passa se um diretorio)
    -e = extrair (passa se um arquivo.sar)
    -l = listar (passa se um arquivo.sar)
*
* 2) Estrutura do arquivo gerado: O arquivo .sar gerado apos o processo de arquivamento de um diretorio consiste, basicamente de:
*    - Um cabecalho contendo a extensao do arquivo (.sar) e uma flag de consistencia (que indica que o arquivo nao foi corrompido
    durante a sua criação, que pode ocorrer com um crash do programa, o desligamento repentino da máquina...)
*    - Registros do tipo Diretorio: Contem o informacoes sobre um diretorio que foi arquivado. Esse tipo de registro possui os
    seguintes campos: |Tipo (1 byte)|Tamanho do Nome (4 bytes)|Nome (variavel)|Numero de Filhos (4 bytes)|.
    Com o campo "Numero de Filhos" conseguimos gravar a hierarquia de diretorios (filhos = pastas + arquivos em um diretorio).
*    - Registros do tipo Arquivo: Contem informacoes sobre um arquivo pertencente a um diretorio. Possui os seguintes campos:
    |Tipo (1 byte)|Tamanho do Nome (4 bytes)|Nome (variavel)|Tamanho do Conteudo (8 bytes)|Conteudo (variavel)|.
    Com o campo "Tamanho do Conteudo" sabemos exatamente quando o registro acaba e comeca o proximo.
*
* 3) Retornos: apos uma iniciar uma operacao, o programa pode retornar os seguintes resultados
    0: execucao bem sucedida
    1: o argumento passado na criação nao e um diretorio valido
    2: o argumento passado na listagem ou extração nao e um arquivo .sar válido
    3: nao foi possivel criar um diretorio na operacao de extracao
    4: Argumentos inválidos
*/

#include "sar.h"

int main(int argc, char* argv[])
{
    int status;

    if(argc != 3)
    {
        info();
        status = 4;
    }
    else
    {
        string op = argv[1];
        if(op.compare("-c") == 0) // Operacao de extracao
            status = arquivar(argv[2]);
        else if(op.compare("-l") == 0) // Operacao de listagem
            status = listar(argv[2]);
        else if(op.compare("-e") == 0) // Operacao de extracao
            status = extrair(argv[2]);
        else
        {
            info();
            status = 4;
        }
    }
    return status;
}
