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

int arquivar(char* dir);
int arquivaRecursivo(string pai, string nomeDir, ofstream& file);

int extrair(char* nomeArquivo);
int extraiRecursivo(ifstream& sarFile, string pathPai);

int listar(char* nomeArquivo);
void listarRecursivo(ifstream&, int nivel);

void info();

#endif // SAR_H
