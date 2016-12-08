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
/*
 Classe: Arquivo

 Descricao: Armazena e gerencia as informacoes sobre um arquivo:
    tamNome - Tamanho do nome do diretorio lido;
    nome - Nome do diretorio;
    tamConteudo - Tamanho total do arquivo que será lido ou arquivado
*/
class Arquivo
{
public:
    Arquivo();
    /*
        Método: save
        Descrição: Salva as informacoes do objeto Arquivo no arquivo passado como parametro
        Entrada: Referencia para um arquivo .sar
        Saida: O arquivo passado contem um novo Arquivo salvo
    */
    void save(ofstream& fileDestino, ifstream& fileOrigem);
    /*
        Método: load
        Descrição: Carrega as informacoes de um arquivo dentro do arquivo passado como parametro e popula o objeto
        Entrada: Referencia para um arquivo .sar
        Saida: Objeto com as informacoes do arquivo
    */
    void load(ifstream& file, string pathPai);
    void loadInfo(ifstream& file);
    /*
        Método: setNome
        Descrição: Atribui o nome para o arquivo
        Entrada: String com o nome
        Saida: Objeto contem o nome passado como parametro
    */
    void setNome(string nome);
    /*
        Método: getNome
        Descrição: Retorna o nome atual do arquivo
        Entrada: -
        Saida: String com o nome do objeto
    */
    string getNome();

private:
    int tamNome;
    char* nome;
    unsigned long long int tamConteudo;
};

#endif // ARQUIVO_H
