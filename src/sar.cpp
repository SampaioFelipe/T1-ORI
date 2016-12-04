#include "sar.h"

int arquivar(char* dir)
{
    ofstream newFile;
    newFile.open("nome.sar", ios::binary|ios::trunc);

    Header head;
    head.save(newFile);

    //dividir nome

    arquivaRecursivo("x", dir, newFile);

    head.changeStatus();
    head.save(newFile);
    newFile.close();

    return 0; // precisa retornar se teve sucesso ou não
}

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


        if(ptrEnt->d_type == DT_REG)
        {
            cout<<"Nome: "<<ptrEnt->d_name<<" : ";
            cout<<"Regular File"<<endl;
            contador++;
            nomeArquivos.push_back(string(ptrEnt->d_name));
        }

        else if(ptrEnt->d_type == DT_DIR)
        {
            if(strcmp(ptrEnt->d_name, ".") != 0 && strcmp(ptrEnt->d_name, "..") != 0)
            {
                cout<<"Nome: "<<ptrEnt->d_name<<" : ";
                cout<<"Directory"<<endl;
                contador++;
                nomeDiretorios.push_back(string(ptrEnt->d_name));
            }
        }
    }

    cout<<"Contador "<<contador<<endl;
    cout<<"Fim Listagem"<<endl;

    dirAtual.setNome(nomeDir);
    dirAtual.setNFilhos(contador);
    dirAtual.save(file);

    string nomeArquivo;
    string path;

    while(!nomeArquivos.empty())
    {
        cout<<"Salvando Arquivos"<<endl;

        nomeArquivo = nomeArquivos.back();
        cout<<nomeArquivo<<" : ";
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
        cout<<"Salvando Diretorios"<<endl;
        arquivaRecursivo(dir, nomeDiretorios.back(), file);
        nomeDiretorios.pop_back();
    }

    closedir(ptrDir); // fecha o directory stream

}

int extrair(char* nomeArquivo)
{
    ifstream sarFile;
    sarFile.open(nomeArquivo, ios::binary);

    if(!sarFile.is_open())
        return 2; // Não é um arquivo válido

    Header head;
    head.load(sarFile);

    if(head.getExtensao().compare(".sar") != 0 || head.getStatus() == 1)
    {
        cout<<"Arquivo inconsistente."<<endl;
        return 3;
    }

    char tipoAtual;
    sarFile.read(&tipoAtual, sizeof(tipoAtual));
    int dirStatus = mkdir("PastaTeste", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if (dirStatus == -1)
    {
        cout<<"Não é possível criar uma pasta."<<endl;
        return 3;
    }

    extraiRecursivo(sarFile, "PastaTeste");

    sarFile.close();
}

int extraiRecursivo(ifstream& sarFile, string pathPai)
{
    Diretorio dirAtual;
    dirAtual.load(sarFile);

    string pathCorrente = pathPai+"/"+dirAtual.getNome();

    int dirStatus = mkdir(pathCorrente.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if (dirStatus == -1)
    {
        cout<<"Não é possível criar uma pasta."<<endl;
        return 3;
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

int listar(char* nomeArquivo)
{
    cout<<"Entrou Listar"<<endl;
    ifstream sarFile;
    sarFile.open(nomeArquivo, ios::binary);

    if(!sarFile.is_open())
        return 2; // Não é um arquivo válido

    Header head;
    head.load(sarFile);

    if(head.getExtensao().compare(".sar") != 0 || head.getStatus() == 1)
    {
        cout<<"Arquivo inconsistente."<<endl;
        return 3;
    }

    char tipoAtual;
    sarFile.read(&tipoAtual, sizeof(tipoAtual));

    listarRecursivo(sarFile, 0);


}

void listarRecursivo(ifstream& file, int nivel)
{
    cout<<"Entrou em ListarRecursivo"<<endl;
    int i;

    Diretorio dirAtual;
    dirAtual.load(file);

    for(i = 0; i<=nivel; i++)
        cout<<"-";

    cout<<dirAtual.getNome()<<"/"<<endl;

    for(int i = 0; i < dirAtual.getNFilhos(); i++)
    {
        char tipoFilho;

        file.read(&tipoFilho, sizeof(tipoFilho));

        if(tipoFilho == 'D')
        {
            listarRecursivo(file, nivel++);
        }
        else
        {
            Arquivo novoArquivo;
            novoArquivo.loadInfo(file);
            for(i = 0; i<=nivel+1; i++)
                cout<<"-";

            cout<<novoArquivo.getNome()<<endl;
        }
    }

}

void info()
{
    cout<<"[Descrição do programa]"<<endl;
}
