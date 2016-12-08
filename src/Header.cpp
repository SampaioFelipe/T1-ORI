#include "Header.h"

Header::Header():extensao(".sar")
{
    this->status = 1; // Inicializa o cabecalho como inconsistente, já que ainda nao foi finalizada a criacao do arquivo

}
void Header::save(ofstream& arquivo)
{
    arquivo.seekp(0, ios::beg); // Move o ponteiro de Put do arquivo para o inicio
    arquivo.write(this->extensao, sizeof(this->extensao)); // Escreve o nome da extensao nos 5 primeiros bytes do arquivo
    arquivo.write(reinterpret_cast<const char *>(&this->status), sizeof(this->status)); // Grava a flag de status
}
void Header::load(ifstream& arquivo)
{
    arquivo.seekg(0, ios::beg); // Move o ponteiro de Get do arquivo para o inicio
    arquivo.read(this->extensao, sizeof(this->extensao)); // Le os 5 bytes onde esta armazenada a extensao do arquivo
    arquivo.read(reinterpret_cast<char *>(&this->status), sizeof(this->status)); // Le a flag de status
}
int Header::getStatus()
{
    return this->status; // Retorna o status atual do cabecalho
}
string Header::getExtensao()
{
    return string(this->extensao); // Retorna a extensao presente no cabecalho
}
void Header::changeStatus()
{
    //Inverte a situacao de consistencia do cabecalho
    if(this->status == 0)
        this->status = 1;
    else
        this->status = 0;
}
