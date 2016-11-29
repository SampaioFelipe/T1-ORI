#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h> // Para a criação de diretórios
#include <dirent.h> // directory header

/**Formato: sar [-c|-l|-e] [nome diretorio|nomeArquivo.sar]**/

using namespace std;

int arquivar(char* dir, int nivel)
{
    DIR* ptrDir = NULL; // Ponteiro para o diretório (DIR representa um stream de diretório)

    struct dirent* ptrEnt = NULL; // Usado para armazenar ifomrações sobre o diretório

    ptrDir = opendir(dir); // abre e retorna um directory stream

    if(ptrDir == NULL){
        cout<<"ERRO: diretorio não encontrado"<<endl;
        return 1;
    }

    while(ptrEnt = readdir(ptrDir)){ // readdir lê a próxima entrada do diretório (retorna um struct dirent*)
        if(ptrEnt == NULL){
            cout<<"ERRO ptrEnt"<<endl;
            return 1;
        }

        cout<<ptrEnt->d_name<<" ";

        if(ptrEnt->d_type == DT_DIR)
        {
            cout<<"Directory "<<nivel<<endl;
            char path[1024];
            int len = snprintf(path, sizeof(path)-1, "%s/%s", dir, ptrEnt->d_name);
            path[len] = 0;
            if (strcmp(ptrEnt->d_name, ".") == 0 || strcmp(ptrEnt->d_name, "..") == 0)
                continue;

            arquivar(path, nivel + 1);
        }
        else if(ptrEnt->d_type == DT_REG)
            cout<<"Regular File"<<endl;
    }

    closedir(ptrDir); // fecha o directory stream

}

int extrair(char* arquivo)
{

    /** Para a criação de um diretorio**/
    int dirStatus = mkdir("foo", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if (dirStatus == -1)
    {
        //cou("Error creating directory!n");
        //exit(1);
    }
}

int main(int argc, char* argv[])
{
    int status = 0;

    if(argc != 3)
    {
        cout<<"Formato Incorreto: Descrição do programa"<<endl;
    }
    else
    {
        cout<<"Formato Correto\nArgumentos lidos: "<<argv[1]<<" "<<argv[2]<<endl;
        switch(argv[1][1])
        {
        case 'c':
            status = arquivar(argv[2], 0);
            break;
        case 'l':
            cout<<"Listar"<<endl;
            break;
        case 'e':
            status = extrair(argv[2]);
            break;
        default:
            cout<<"Formato Incorreto: Descrição do programa"<<endl;
            status = 1;
        }
    }
    return status;
}
