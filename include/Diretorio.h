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
/*
 Classe: Diretorio

 Descricao: Armazena e gerencia as informacoes sobre um diretorio:
    tamNome - Tamanho do nome do diretorio lido;
    nome - Nome do diretorio;
    nFilhos - Quantidade de pastas e arquivos que o diretorio contem
*/
class Diretorio
{
public:
    Diretorio();
    /*
        Método: save
        Descrição: Salva as informacoes do diretorio no arquivo passado como parametro
        Entrada: Referencia para um arquivo .sar
        Saida: O arquivo passado contem um novo diretorio salvo
    */
    void save(ofstream& file);
    /*
        Método: load
        Descrição: Carrega as informacoes de um diretorio do arquivo passado como parametro e popula o objeto
        Entrada: Referencia para um arquivo .sar
        Saida: Objeto com as informacoes do diretorio
    */
    void load(ifstream& file);
    /*
        Método: setNome
        Descrição: Atribui o nome para o diretorio
        Entrada: String com o nome
        Saida: Objeto com o nome passado como parametro
    */
    void setNome(string nome);
    /*
        Método: getNome
        Descrição: Retorna o nome atual do diretorio
        Entrada: -
        Saida: String com o nome do objeto
    */
    string getNome();
    /*
        Método: setNFilhos
        Descrição: Atribui o a quantidade de filhos que o diretorio contem
        Entrada: Int com a quantidade de filhos
        Saida: Objeto com o numero de filhos configurado
    */
    void setNFilhos(int valor);
    /*
        Método: getNFilhos
        Descrição: Retorna a quantidade de filhos
        Entrada: -
        Saida: Int com a quantidade
    */
    int getNFilhos();

private:
    int tamNome;
    char* nome;
    int nFilhos;
};

#endif // DIRETORIO_H
