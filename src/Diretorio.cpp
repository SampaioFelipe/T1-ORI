#include "Diretorio.h"

Diretorio::Diretorio()
{
    this->nFilhos = -1; // Inicializa o diretorio como não consistente, pois ainda nao fizemos a leitura de suas informacoes
}
void Diretorio::save(ofstream& file)
{
    if(this->nFilhos >= 0) // Verifica se o diretorio e valido, se for entao pode gravar no arquivo
    {
        char tipo = 'D'; // Indica o tipo do registro como Diretorio
        file.write(&tipo, sizeof(tipo)); // Grava o tipo no arquivo
        file.write(reinterpret_cast<const char *>(&this->tamNome), sizeof(this->tamNome)); // Grava o tamanho do nome do diretorio
        file.write(this->nome, this->tamNome); // Grava o nome do diretorio
        file.write(reinterpret_cast<const char *>(&this->nFilhos), sizeof(this->nFilhos)); // Grava o numero de filhos do diretorio
    }
}
void Diretorio::load(ifstream& file)
{
    file.read(reinterpret_cast<char *>(&this->tamNome), sizeof(this->tamNome)); // Carrega o tamanho do nome do direto
    this->nome = new char[this->tamNome]; // Aloca uma string para carregar o nome do diretorio
    file.read(this->nome, this->tamNome); // Carrega o nome
    file.read(reinterpret_cast<char *>(&this->nFilhos), sizeof(this->nFilhos)); // Carrega o numero de filhos
}

void Diretorio::setNome(string nome)
{
    this->nome = new char[nome.size()]; // Aloca memoria para guardar o nome
    strcpy(this->nome, nome.c_str()); // Copia o nome passado como parametro para o atributo nome do objeto
    this->tamNome = nome.size()+1; // Atribui o tamanho do nome passado ao atributo tamNome (soma mais 1 devido ao \0 do final de uma string)
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

