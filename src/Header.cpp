#include "Header.h"
#include <iostream>
Header::Header():extensao(".sar") //{'.','s','a','r'}
{
    this->status = 1; // mudar

}
void Header::save(ofstream& arquivo)
{
    arquivo.seekp(0, ios::beg); //move o ponteiro de put
    arquivo.write(this->extensao, sizeof(this->extensao));
    arquivo.write(reinterpret_cast<const char *>(&this->status), sizeof(this->status));
}
void Header::load(ifstream& arquivo)
{
    arquivo.seekg(0, ios::beg); // move o ponteiro de get
    arquivo.read(this->extensao, sizeof(this->extensao));
    arquivo.read(reinterpret_cast<char *>(&this->status), sizeof(this->status));
}
int Header::getStatus()
{
    return this->status;
}
string Header::getExtensao()
{
    return string(this->extensao);
}
void Header::changeStatus()
{
    if(this->status == 0)
        this->status = 1;
    else
        this->status = 0;
}
