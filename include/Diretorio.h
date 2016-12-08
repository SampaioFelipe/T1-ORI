/*

Pré-Condição: Existência ou não de um diretório.

Pós-Condição: Criação de um diretório para armazenar arquivos. Definir o nome para o diretório criado, e a quantidade de filhos que esse
diretório terá. Além disso, pode carregar um diretório já existente.

*/

#ifndef DIRETORIO_H
#define DIRETORIO_H

#include <fstream>
#include <dirent.h>

#include <iostream>
#include <string.h>

using namespace std;

class Diretorio
{
public:
    Diretorio();
    void save(ofstream& file);
    void load(ifstream& file);

    void setNome(string nome);
    string getNome();

    void setNFilhos(int valor);
    int getNFilhos();

private:
    int tamNome;
    char* nome;
    int nFilhos;
};

#endif // DIRETORIO_H
