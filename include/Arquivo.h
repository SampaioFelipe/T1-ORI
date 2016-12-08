/*
Pré-Condição: Existência de um arquivo de qualquer tipo para ser salvo, tais como texto,imagem, e outros.

Pós-Condição: Salva o arquivo em um diretório previamente criado pelo programa ( a ser detalhado em outro arquivo), além de definir
um nome para o arquivo. Carrega o arquivo que foi salvo bem como toda a informação presente no arquivo carregado.

*/

#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <fstream>
#include <dirent.h>

#include <iostream>
#include <string.h>

using namespace std;

class Arquivo
{
public:
    Arquivo();
    void save(ofstream& fileDestino, ifstream& fileOrigem);
    void load(ifstream& file, string pathPai);
    void loadInfo(ifstream& file);
    void setNome(string nome);
    string getNome();

private:
    int tamNome;
    char* nome;
    int tamConteudo;
};

#endif // ARQUIVO_H
