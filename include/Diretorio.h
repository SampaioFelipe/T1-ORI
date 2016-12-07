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
