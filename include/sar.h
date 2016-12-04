#ifndef SAR_H
#define SAR_H

#include <iostream>
#include <fstream>

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
void info();

void listar();
void listarRecursivo(ifstream&, int nivel);


#endif // SAR_H
