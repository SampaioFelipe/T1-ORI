#include "Arquivo.h"

Arquivo::Arquivo()
{
    this->tamConteudo = 0; // Inicializa o arquivo com tamanho 0, uma vez que nao carregamos nada ainda
    this->tamNome = 0; // Tambem nao lemos o nome do arquivo, por isso inicializamos com 0
}
void Arquivo::save(ofstream& fileDestino, ifstream& fileOrigem)
{
    char tipo = 'F'; // Indica o tipo do registro como Arquivo
    fileDestino.write(&tipo, sizeof(tipo)); // Grava o tipo
    fileDestino.write(reinterpret_cast<const char *>(&this->tamNome), sizeof(this->tamNome)); // Grava o tamanho do nome do Arquivo
    fileDestino.write(this->nome, this->tamNome); // Grava o nome do objeto no arquivo

    fileOrigem.seekg(0, ios::end); // Coloca o ponteiro de Get do arquivo Origem no final
    tamConteudo = fileOrigem.tellg(); // Com o ponteiro Get no final, calculamos o tamanho do arquivo
    fileDestino.write(reinterpret_cast<const char *>(&this->tamConteudo), sizeof(this->tamConteudo)); // Grava o tamanho do conteudo do arquivo origem no arquivo destino

    fileOrigem.seekg(0); // Retorna o ponteiro Get para o Inicio do arquivo

    while(!fileOrigem.eof()) // Enquanto não chegar no final do arquivo origem gravamos cada byte dele no arquivo destino
    {
        fileDestino.put(fileOrigem.get());
    }
}
void Arquivo::load(ifstream& file, string pathPai)
{
    file.read(reinterpret_cast<char*>(&this->tamNome), sizeof(this->tamNome)); // Carrega o tamanho do nome do registro que representa um arquivo
    this->nome = new char[this->tamNome]; // Aloca memoria para guardar o nome que sera lido
    file.read(this->nome, this->tamNome); // Le o nome
    file.read(reinterpret_cast<char*>(&this->tamConteudo), sizeof(this->tamConteudo)); // Carrega o tamanho do conteudo do arquivo

    ofstream novoArquivo;
    novoArquivo.open((pathPai + "/" + this->nome).c_str(), ios::binary); // Abre um novo arquivo para transferir o conteudo do arquivo .sar

    int fim = file.tellg() + this->tamConteudo; // Calcula ate onde vai o conteudo do arquivo que queremos recuperar

    while(file.tellg() <= fim) // Enquanto nao chegar no ultimo byte do conteudo desse arquivo, gravamos no novo arquivo criado
    {
        novoArquivo.put(file.get());
    }

    novoArquivo.close(); // Fecha o arquivo que haviamos aberto nesse metodo
}

void Arquivo::loadInfo(ifstream& file)
{
    file.read(reinterpret_cast<char*>(&this->tamNome), sizeof(this->tamNome)); // Le o tamanho do nome
    this->nome = new char[this->tamNome]; // Aloca memoria para comportar o nome que sera lido
    file.read(this->nome, this->tamNome); // Le o nome
    file.read(reinterpret_cast<char*>(&this->tamConteudo), sizeof(this->tamConteudo)); // Carrega o tamanho do conteudo

    file.seekg(file.tellg() + this->tamConteudo + 1, ios::beg); // Move o ponteiro de get para o proximo registro (pula todo o conteudo do arquivo)
}

void Arquivo::setNome(string nome)
{
    this->nome = new char[nome.size()]; // Aloca memoria para guardar o nome
    strcpy(this->nome, nome.c_str()); // Copia o nome passado como parametro para o atributo nome do objeto
    this->tamNome = nome.size()+1; // Atribui o tamanho do nome passado ao atributo tamNome (soma mais 1 devido ao \0 do final de uma string)
}

string Arquivo::getNome()
{
    return this->nome;
}
