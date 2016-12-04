#ifndef HEADER_H
#define HEADER_H
#include <fstream>
#include <dirent.h>

using namespace std;
class Header
{
public:
//private:
    char extensao[5];
    int status;
public:
    Header();
    void save(ofstream& arquivo);
    void load(ifstream& arquivo);
    int getStatus();
    string getExtensao();
    void changeStatus();
};

#endif // HEADER_H
