#include <iostream>
#include <fstream>

#include <string.h>

#include <sys/stat.h> // Para a criação de diretórios
#include <dirent.h> // directory header

/**Formato: sar [-c|-l|-e] [nome diretorio|nomeArquivo.sar]**/

using namespace std;

int arquivar(char* dir, int nivel)
{
    streampos size;
    char * memblock;
    /**Abertura de novo Arquivo**/
    ofstream arquivo;
    ifstream imagem;

    arquivo.open("nome.png", ios::binary|ios::trunc); // Temos que verificar se já não exite arquivo com o mesmo nome (?)
    imagem.open("ghibli.png", ios::binary);

    //size = imagem.tellg();
    //cout<<size<<endl;
    //memblock = new char [size];
    //imagem.read(memblock, size);
    //arquivo.write(memblock, size);

    if(imagem.is_open() && arquivo.is_open())
	{
		while(!imagem.eof())
		{
			arquivo.put(imagem.get());
		}
	}

    imagem.close();
    arquivo.close();

    /**Parte dos diretórios**/

    DIR* ptrDir = NULL; // Ponteiro para o diretório (DIR representa um stream de diretório)

    struct dirent* ptrEnt = NULL; // Usado para armazenar ifomrações sobre o diretório

    ptrDir = opendir(dir); // abre e retorna um directory stream

    if(ptrDir == NULL)
    {
        cout<<"ERRO: diretorio não encontrado"<<endl;
        return 1;
    }

    while(ptrEnt = readdir(ptrDir))  // readdir lê a próxima entrada do diretório (retorna um struct dirent*)
    {
        if(ptrEnt == NULL)
        {
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

void info()
{
    cout<<"[Descrição do programa]"<<endl;
}

int main(int argc, char* argv[])
{
    int status = 0;

    if(argc != 3)
    {
        info();
        status = 3;
    }
    else
    {
        string op = argv[1];
        if(op.compare("-c") == 0)
            status = arquivar(argv[2], 0);
        else if(op.compare("-l") == 0)
            cout<<"Listar"<<endl;
        else if(op.compare("-e") == 0)
            status = extrair(argv[2]);
        else
        {
            info();
            status = 3;
        }
    }
    return status;
}
