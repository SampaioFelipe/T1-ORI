/*

Pré-Condição: Um arquivo já existente em algum diretório.

Pós-Condição: Cria um cabeçalho para esse arquivo. Possui as funções de salvar o cabeçalho do arquivo, carregar um cabeçalho já existente
com informações, retornar o status do cabeçalho atual, mudar o status do cabeçalho e por fim pode obter a extensão de um cabeçalho
já criado.

*/

#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <dirent.h>

using namespace std;

/*
 Classe: Header

 Descricao: Contem as informacoes de cabecalho do arquivo:
    Extensao - Tipo do arquivo, neste caso ".sar";
    Status - Situacao de consistencia do arquivo;
*/
class Header
{
public:

    Header();
    /*
        Método: save
        Descrição: Salva as informacoes do cabecalho no arquivo passado como parametro
        Entrada: Referencia para um arquivo .sar
        Saida: O arquivo passado contem um novo cabecalho
    */
    void save(ofstream& arquivo);
    /*
        Método: load
        Descrição: Carrega as informacoes do cabecalho do arquivo passado como parametro e popula o objeto
        Entrada: Referencia para um arquivo .sar
        Saida: Objeto com as informacoes do cabecalho do arquivo passado como parametro
    */
    void load(ifstream& arquivo);
    /*
        Método: getStatus
        Descrição: Retorna o atual status do cabecalho
        Entrada: -
        Saida: Inteiro que representa o status do cabecalho
    */
    int getStatus();
    /*
        Método: getExtensao
        Descrição: Salva as informacoes do cabecalho no arquivo passado como parametro
        Entrada: Referencia para um arquivo .sar
        Saida: O arquivo passado contem um novo cabecalho
    */
    string getExtensao();
    /*
        Método: changeStatus
        Descrição: Muda os status do cabecalho
        Entrada: -
        Saida: O atribuito status se torna 0 se antes era 1 e vice-versa
    */
    void changeStatus();

private:
    char extensao[5];
    int status; //Status é 1 se o arquivo nao e consistente, ou seja, ouve uma falha durante a criacao do arquivo, ou 0 caso contrario.

};

#endif // HEADER_H
