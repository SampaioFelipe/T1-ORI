#include "Diretorio.h"

Diretorio::Diretorio()
{
    this->nFilhos = -1;
}
void Diretorio::save(ofstream& file)
{
    if(this->nFilhos >= 0)
    {
        char tipo = 'D';
        file.write(&tipo, sizeof(tipo));
        file.write(reinterpret_cast<const char *>(&this->tamNome), sizeof(this->tamNome));
        file.write(this->nome, this->tamNome);
        file.write(reinterpret_cast<const char *>(&this->nFilhos), sizeof(this->nFilhos));
    }
}
void Diretorio::load(ifstream& file)
{
    file.read(reinterpret_cast<char *>(&this->tamNome), sizeof(this->tamNome));
    this->nome = new char[this->tamNome];
    file.read(this->nome, this->tamNome);
    file.read(reinterpret_cast<char *>(&this->nFilhos), sizeof(this->nFilhos));
}

void Diretorio::setNome(string nome)
{
    this->nome = new char[nome.size()];
    strcpy(this->nome, nome.c_str());
    this->tamNome = nome.size()+1;
}
string Diretorio::getNome()
{
    return this->nome;
}

void Diretorio::setNFilhos(int valor)
{
    this->nFilhos = valor;
}
int Diretorio::getNFilhos()
{
    return this->nFilhos;
}

