#include "Diretorio.h"
#include <iostream>
#include <string.h>

using namespace std;
Diretorio::Diretorio()
{
    this->nFilhos = -1;
}
void Diretorio::save(ofstream& file)
{
    char tipo = 'D';
    file.write(&tipo, sizeof(tipo));
    file.write(reinterpret_cast<const char *>(&this->tamNome), sizeof(this->tamNome));
    file.write(this->nome, this->tamNome);
    file.write(reinterpret_cast<const char *>(&this->nFilhos), sizeof(this->nFilhos));
}
void Diretorio::load(ifstream& file)
{
    file.read(reinterpret_cast<char *>(&this->tamNome), sizeof(this->tamNome));
    cout<<tamNome<<endl;
    this->nome = new char[this->tamNome];
    file.read(this->nome, this->tamNome);
    cout<<nome<<endl;
    file.read(reinterpret_cast<char *>(&this->nFilhos), sizeof(this->nFilhos));
    cout<<nFilhos<<endl;

}

void Diretorio::setNome(string nome)
{
    this->nome = new char[nome.size()];
    strcpy(this->nome, nome.c_str());
    this->tamNome = nome.size();
    cout<<this->nome<<" "<<this->tamNome<<endl;
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

