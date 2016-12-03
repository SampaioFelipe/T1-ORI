#include "Arquivo.h"
#include <iostream>
#include <string.h>
using namespace std;
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

    cout<<"Tam: "<<this->tamConteudo<<endl;
    fileOrigem.seekg(0);

    while(!fileOrigem.eof())
    {
        cout<<fileOrigem.tellg()<<endl;
        fileDestino.put(fileOrigem.get());
    }
}
void Arquivo::load(ifstream& file, string pathPai)
{
    cout<<"Load"<<endl;
    file.read(reinterpret_cast<char*>(&this->tamNome), sizeof(this->tamNome));
    cout<<this->tamNome<<endl;
    this->nome = new char[this->tamNome];
    file.read(this->nome, this->tamNome);
    cout<<this->nome<<endl;
    file.read(reinterpret_cast<char*>(&this->tamConteudo), sizeof(this->tamConteudo));
    cout<<this->tamConteudo<<endl;

    ofstream novoArquivo;
    novoArquivo.open((pathPai + "/" + this->nome).c_str(), ios::binary);

    int fim = file.tellg() + this->tamConteudo;

    while(file.tellg() <= fim)
    {
        cout<<file.tellg()<<endl;
        novoArquivo.put(file.get());
    }

    novoArquivo.close();
}

void Arquivo::setNome(string nome)
{
    this->nome = new char[nome.size()];
    strcpy(this->nome, nome.c_str());
    this->tamNome = nome.size();
    cout<<this->nome<<" "<<this->tamNome<<endl;
}