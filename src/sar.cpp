#include "sar.h"

vector<string> splitPath(string path, const char* delimitador)
{
    string nome, aux;
    vector<string> splited;

    aux = path.back();

    while(aux.compare(delimitador) == 0)
    {
        path.pop_back();
        aux = path.back();
    }

    while(!path.empty())
    {
        aux = path.back();
        path.pop_back();

        if(aux.compare(delimitador) == 0)
        {
            reverse(nome.begin(),nome.end());
            splited.push_back(path);
            splited.push_back(nome);
            return splited;
        }
        else
        {
            nome.append(aux);
        }
    }

    reverse(nome.begin(),nome.end());
    splited.push_back(".");
    splited.push_back(nome);

    return splited;
}

int arquivar(char* dir)
{
    vector<string> dirPath = splitPath(dir,"/");
    string nome = dirPath.back() + ".sar";

    ofstream newFile;
    newFile.open(nome.c_str(), ios::binary|ios::trunc);

    Header head;
    head.save(newFile);

    int status = arquivaRecursivo(dirPath[0], dirPath[1], newFile);

    head.changeStatus();
    head.save(newFile);

    newFile.close();

    return status; // precisa retornar se teve sucesso ou não
}

int arquivaRecursivo(string pai, string nomeDir, ofstream& file)
{
    string dir;
    if(pai==".")
        dir = nomeDir;
    else
        dir = pai + "/" + nomeDir;

    DIR* ptrDir = opendir(dir.c_str()); // Ponteiro para o diretório (DIR representa um stream de diretório), abre e retorna um directory stream

    if(ptrDir == NULL)
    {
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
            return 1;
        }


        if(ptrEnt->d_type == DT_REG)
        {
            contador++;
            nomeArquivos.push_back(string(ptrEnt->d_name));
        }

        else if(ptrEnt->d_type == DT_DIR)
        {
            if(strcmp(ptrEnt->d_name, ".") != 0 && strcmp(ptrEnt->d_name, "..") != 0)
            {
                contador++;
                nomeDiretorios.push_back(string(ptrEnt->d_name));
            }
        }
    }

    dirAtual.setNome(nomeDir);
    dirAtual.setNFilhos(contador);
    dirAtual.save(file);

    string nomeArquivo;
    string path;

    while(!nomeArquivos.empty())
    {
        nomeArquivo = nomeArquivos.back();
        path = dir + "/" + nomeArquivo;

        ifstream readFile;
        readFile.open(path.c_str(), ios::binary);

        if(readFile.is_open())
        {
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

    return 0;
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
        return 2;
    }

    char tipoAtual;
    sarFile.read(&tipoAtual, sizeof(tipoAtual));

    int status = extraiRecursivo(sarFile, ".");

    sarFile.close();

    return status;
}

int extraiRecursivo(ifstream& sarFile, string pathPai)
{
    Diretorio dirAtual;
    dirAtual.load(sarFile);

    string pathCorrente = pathPai+"/"+dirAtual.getNome();

    int dirStatus = mkdir(pathCorrente.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if (dirStatus == -1)
    {
        return 4;
    }

    for(int i = 0; i < dirAtual.getNFilhos(); i++)
    {
        char tipoFilho;

        sarFile.read(&tipoFilho, sizeof(tipoFilho));

        if(tipoFilho == 'D')
        {
            if(extraiRecursivo(sarFile, pathCorrente) == 4)
            {
                return 4;
            }
        }
        else
        {
            Arquivo novoArquivo;
            novoArquivo.load(sarFile, pathCorrente);
        }
    }

    return 0;
}

int listar(char* nomeArquivo)
{
    ifstream sarFile;
    sarFile.open(nomeArquivo, ios::binary);

    if(!sarFile.is_open())
        return 2; // Não é um arquivo válido

    Header head;
    head.load(sarFile);

    if(head.getExtensao().compare(".sar") != 0 || head.getStatus() == 1)
    {
        return 2; // Não é um arquivo .sar ou é inconsistente
    }

    char tipoAtual;
    sarFile.read(&tipoAtual, sizeof(tipoAtual));

    listarRecursivo(sarFile, 0);

    return 0;
}

void listarRecursivo(ifstream& file, int nivel)
{
    Diretorio dirAtual;
    dirAtual.load(file);

    if(dirAtual.getNFilhos() < 0)
        return;

    for(int i = 0; i<=nivel; i++)
        cout<<"-";

    cout<<dirAtual.getNome()<<"/"<<endl;

    if(file.eof())
        return;

    for(int i = 0; i < dirAtual.getNFilhos(); i++)
    {
        char tipoFilho;

        file.read(&tipoFilho, sizeof(tipoFilho));

        if(tipoFilho == 'D')
        {
            listarRecursivo(file, nivel+1);
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
    cout<<"NAME \n\tsar - cria e extrai uma estrutura de diretórios em um arquivo"<<endl;
    cout<<"SYNOPSIS \n\
     \tsar -c diretório\n\
     \tsar [-e|-l] arquivo_sar"<<endl;
    cout<<"DESCRIPTION\n\t-c diretório: Arquiva um diretorio.\n\
     \t-e arquivo_sar: Extração de arquivos .sar.\n\
     \t-l arquivo_sar: Listagem de arquivo .sar."<<endl;
    cout<<"RETURN CODES\n\
     \t0: Execução bem sucedida\n\
     \t1: O argumento passado na criação não é um diretório\n\
     \t2: O argumento passado na listagem ou extração não é um arquivo .sar válido\n\
     \t3: Nao é possível criar um diretório\n\
     \t4: Descrição inválida"<<endl;
}
