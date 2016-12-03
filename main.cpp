#include <iostream>
#include <fstream>

#include <string.h>
#include <vector>

#include <sys/stat.h> // Para a criação de diretórios
#include <dirent.h> // directory header

#include "Header.h"
#include "Diretorio.h"
#include "Arquivo.h"
/**Formato: sar [-c|-l|-e] [nome diretorio|nomeArquivo.sar]**/

using namespace std;

int arquivaRecursivo(string pai, string nomeDir, ofstream& file)
{
    string dir;
    if(pai=="x")
        dir = nomeDir;
    else
        dir = pai + "/" + nomeDir;

    DIR* ptrDir = opendir(dir.c_str()); // Ponteiro para o diretório (DIR representa um stream de diretório), abre e retorna um directory stream

    if(ptrDir == NULL)
    {
        cout<<"ERRO: Nao foi possivel abrir o diretorio"<<endl;
        return 1;
    }

    Diretorio dirAtual;

    struct dirent* ptrEnt = NULL; // Usado para armazenar informações sobre o diretório

    int contador = 0;

    vector<string> nomeArquivos;
    vector<string> nomeDiretorios;

    while(ptrEnt = readdir(ptrDir))  // readdir lê a próxima entrada do diretório (retorna um struct dirent*)
    {
        if(ptrEnt == NULL)
        {
            cout<<"ERRO ptrEnt"<<endl;
            return 1;
        }

        cout<<ptrEnt->d_name<<" : ";

        if(ptrEnt->d_type == DT_REG)
        {
            cout<<"Regular File"<<endl;
            contador++;
            nomeArquivos.push_back(string(ptrEnt->d_name));

        }

        else if(ptrEnt->d_type == DT_DIR)
        {
            if(strcmp(ptrEnt->d_name, ".") != 0 && strcmp(ptrEnt->d_name, "..") != 0)
            {
                cout<<"Directory"<<endl;
                contador++;
                nomeDiretorios.push_back(string(ptrEnt->d_name));
            }
        }
    }

    cout<<contador<<endl;

    dirAtual.setNome(nomeDir);
    dirAtual.setNFilhos(contador);
    dirAtual.save(file);

    string nomeArquivo;
    string path;

    while(!nomeArquivos.empty())
    {
        nomeArquivo = nomeArquivos.back();
        cout<<nomeArquivo<<endl;
        path = dir + "/" + nomeArquivo;
        cout<<path<<endl;

        ifstream readFile;
        readFile.open(path.c_str(), ios::binary);

        if(readFile.is_open())
        {
            cout<<"Abriu"<<endl;
            Arquivo fileAtual;
            fileAtual.setNome(nomeArquivo);
            fileAtual.save(file, readFile);
        }

        nomeArquivos.pop_back();
    }

    while(!nomeDiretorios.empty())
    {
        arquivaRecursivo(dir, nomeDiretorios.back(), file);
        nomeDiretorios.pop_back();
    }

    closedir(ptrDir); // fecha o directory stream

}

int arquivar(char* dir)
{
    ofstream newFile;
    newFile.open("nome.sar", ios::binary|ios::trunc);

    Header head;
    head.save(newFile);

    //dividir nome

    arquivaRecursivo("x", dir, newFile);

    newFile.close();

    return 0; // precisa retornar se teve sucesso ou não
}

int extraiRecursivo(ifstream& sarFile, string pathPai)
{
    cout<<"Entrou em recursivo"<<endl;

    Diretorio dirAtual;
    dirAtual.load(sarFile);
    cout<<dirAtual.getNome()<<endl;

    string pathCorrente = pathPai+"/"+dirAtual.getNome();

    int dirStatus = mkdir(pathCorrente.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if (dirStatus == -1)
    {
        //cou("Error creating directory!n");
        //exit(1);
    }

    for(int i = 0; i < dirAtual.getNFilhos(); i++)
    {
        char tipoFilho;

        sarFile.read(&tipoFilho, sizeof(tipoFilho));

        if(tipoFilho == 'D')
        {
            extraiRecursivo(sarFile, pathCorrente);
        }
        else
        {
            Arquivo novoArquivo;
            novoArquivo.load(sarFile, pathCorrente);
        }

    }


}

int extrair(char* nomeArquivo)
{
    cout<<"Entrou em extrair"<<endl;

    ifstream sarFile;
    sarFile.open(nomeArquivo); // verificar se o arquivo existe

    Header head;
    head.load(sarFile); // tratar a flag de consistência
    cout<<head.extensao<<" "<<head.getStatus()<<endl;
    char tipoAtual;
    sarFile.read(&tipoAtual, sizeof(tipoAtual));
    cout<<tipoAtual<<endl;

    /*Diretorio dirAtual;
    dirAtual.load(sarFile);

    for(int i = 0; i < dirAtual.getNFilhos(); i++)
    {
        char tipoFilho;
        file.read(&tipoFilho, sizeof(tipo));

        if(tipoFilho == "D")
        {
            extraiRecursivo(sarFile);
        }
        else
        {

        }

    }*/

    int dirStatus = mkdir("PastaTeste", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if (dirStatus == -1)
    {
        //cou("Error creating directory!n");
        //exit(1);
    }

    extraiRecursivo(sarFile, "PastaTeste");

    sarFile.close();
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
            status = arquivar(argv[2]);
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

    /*
    ofstream file;
    file.open("teste.sar", ios::binary|ios::trunc);

    Header head;
    head.save(file);

    ifstream imagem;
    imagem.open("ghibli.png",ios::binary);

    if(imagem.is_open() && file.is_open())
    {
        while(!imagem.eof())
        {
            file.put(imagem.get());
        }
    }

    imagem.close();
    file.close();*/

}
