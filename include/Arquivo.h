#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <fstream>
#include <dirent.h>

using namespace std;

class Arquivo
{
public:
    Arquivo();
    void save(ofstream& fileDestino, ifstream& fileOrigem);
    void load(ifstream& file, string pathPai);
    void setNome(string nome);

private:
    int tamNome;
    char* nome;
    int tamConteudo;
};

#endif // ARQUIVO_H
