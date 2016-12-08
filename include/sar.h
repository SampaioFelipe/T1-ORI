/*

Pré-Condição: Existência de um ou mais arquivos presentes nos diretórios existentes.

Pós-Condição: Permite Arquivar  arquivos, direta ou recursivamente. Permite extrair  arquivos, direta ou recursivamente bem como
permite que seja feita uma listagem, direta ou recursivamente de arquivos.

*/

#ifndef SAR_H
#define SAR_H

#include <iostream>
#include <fstream>

#include<algorithm>
#include <string.h>
#include <vector>

#include <sys/stat.h> // Para a criação de diretórios
#include <dirent.h> // directory header

#include "Header.h"
#include "Diretorio.h"
#include "Arquivo.h"

using namespace std;

/*
    Função: arquivar
    Descrição: Arquiva (salva em um .sar) um diretorio passado como parametro
    Entrada: String com o nome do diretorio
    Saida: Status da operacao
*/
int arquivar(char* dir);
/*
    Função: arquivaRecursivo
    Descrição: Arquiva cada subpasta de um diretorio
    Entrada: String com o caminho (pai), String como o nome do diretorio, referencia para um arquivo .sar
    Saida: Status da operacao
*/
int arquivaRecursivo(string pai, string nomeDir, ofstream& file);
/*
    Função: extrair
    Descrição: Extrai (de um arquivo .sar) todos a estrutura de diretorios e arquivos armazenada
    Entrada: String com o nome do arquivo .sar
    Saida: Status da operacao
*/
int extrair(char* nomeArquivo);
/*
    Função: extraiRecursivo
    Descrição: Extrai o conteudo de cada subdiretorio que esta arquivado
    Entrada: Referência para um arquivo .sar, String com o caminho do diretorio pai
    Saida: Status da operacao
*/
int extraiRecursivo(ifstream& sarFile, string pathPai);
/*
    Função: listar
    Descrição: Lista todo o conteudo de um arquivo .sar
    Entrada: Nome do arquivo .sar
    Saida: Status da operacao
*/
int listar(char* nomeArquivo);
/*
    Função: listaRecursivo
    Descrição: Lista o conteudo de cada diretorio arquivado em um arquivo .sar
    Entrada: Referencia para um arquivo .sar, Int com o nível atual na hierarquia
    Saida: Status da operacao
*/
void listarRecursivo(ifstream&, int nivel);
/*
    Função: info
    Descrição: Imprime as informacoes de como utilizar o programa
    Entrada: -
    Saida: -
*/
void info();

#endif // SAR_H
