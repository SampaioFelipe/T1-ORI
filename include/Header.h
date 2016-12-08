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
private:
    char extensao[5];

    //Status é 1 se o arquivo nao e consistente, ou seja, ouve uma falha durante a criacao do arquivo, ou 0 caso contrario.
    int status;
public:
    /*
        Construtor: Header
        Descricao: Inicializa a classe Header
    */
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
        Saida: Inteiro que representa o status
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
        Descrição: Salva as informacoes do cabecalho no arquivo passado como parametro
        Entrada: Referencia para um arquivo .sar
        Saida: O arquivo passado contem um novo cabecalho
    */
    void changeStatus();
};

#endif // HEADER_H
