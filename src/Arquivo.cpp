#include "Arquivo.h"

Arquivo::Arquivo()
{
    this->tamConteudo = 0;
    this->tamNome = 0;
}
void Arquivo::save(ofstream& fileDestino, ifstream& fileOrigem)
{
    char tipo = 'F';
    fileDestino.write(&tipo, sizeof(tipo));
    fileDestino.write(reinterpret_cast<const char *>(&this->tamNome), sizeof(this->tamNome));
    fileDestino.write(this->nome, this->tamNome);

    fileOrigem.seekg(0, ios::end);
    tamConteudo = fileOrigem.tellg();
    fileDestino.write(reinterpret_cast<const char *>(&this->tamConteudo), sizeof(this->tamConteudo));

    fileOrigem.seekg(0);

    while(!fileOrigem.eof())
    {
        fileDestino.put(fileOrigem.get());
    }
}
void Arquivo::load(ifstream& file, string pathPai)
{
    file.read(reinterpret_cast<char*>(&this->tamNome), sizeof(this->tamNome));
    this->nome = new char[this->tamNome];
    file.read(this->nome, this->tamNome);
    file.read(reinterpret_cast<char*>(&this->tamConteudo), sizeof(this->tamConteudo));

    ofstream novoArquivo;
    novoArquivo.open((pathPai + "/" + this->nome).c_str(), ios::binary);

    int fim = file.tellg() + this->tamConteudo;

    while(file.tellg() <= fim)
    {
        novoArquivo.put(file.get());
    }

    novoArquivo.close();
}

void Arquivo::loadInfo(ifstream& file)
{
    file.read(reinterpret_cast<char*>(&this->tamNome), sizeof(this->tamNome));
    this->nome = new char[this->tamNome];
    file.read(this->nome, this->tamNome);
    file.read(reinterpret_cast<char*>(&this->tamConteudo), sizeof(this->tamConteudo));

    file.seekg(file.tellg() + this->tamConteudo + 1, ios::beg); // ??
}

void Arquivo::setNome(string nome)
{
    this->nome = new char[nome.size()];
    strcpy(this->nome, nome.c_str());
    this->tamNome = nome.size()+1;
}

string Arquivo::getNome()
{
    return this->nome;
}
