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
        cout<<tipo<<" "<<sizeof(tipo)<<endl;
        file.write(&tipo, sizeof(tipo));
        cout<<tamNome<<" "<<sizeof(tamNome)<<endl;
        file.write(reinterpret_cast<const char *>(&this->tamNome), sizeof(this->tamNome));
        cout<<nome<<" "<<sizeof(nome)<<endl;
        file.write(this->nome, this->tamNome);
        cout<<nFilhos<<" "<<sizeof(nFilhos)<<endl;
        file.write(reinterpret_cast<const char *>(&this->nFilhos), sizeof(this->nFilhos));
    }

}
void Diretorio::load(ifstream& file)
{
    file.read(reinterpret_cast<char *>(&this->tamNome), sizeof(this->tamNome));
    //cout<<"TamNome "<<tamNome<<endl;
    this->nome = new char[this->tamNome];
    file.read(this->nome, this->tamNome);
    //cout<<"Nome"<<nome<<endl;
    file.read(reinterpret_cast<char *>(&this->nFilhos), sizeof(this->nFilhos));
    //cout<<nFilhos<<endl;

}

void Diretorio::setNome(string nome)
{
    this->nome = new char[nome.size()];
    strcpy(this->nome, nome.c_str());
    this->tamNome = nome.size()+1;
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

