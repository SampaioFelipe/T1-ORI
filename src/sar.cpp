#include "sar.h"

vector<string> splitPath(string path, const char* delimitador)
{
    string nome, aux;

    vector<string> splited;

    aux = path.back(); // Pega o ultimo caracter do path

    while(aux.compare(delimitador) == 0) // Enquanto o ultimo caracter for igual ao delimitador, ele é retirado da string
    {
        path.pop_back();
        aux = path.back();
    }

    while(!path.empty())
    {
        aux = path.back(); // Pega o ultimo caracter de path
        path.pop_back(); // Retira-o da string original

        if(aux.compare(delimitador) == 0) // Se esse caracter for igual ao delimitador quer dizer que conseguimos separar o caminho do nome da pasta
        {
            reverse(nome.begin(),nome.end()); // Como armazenamos o nome invertido, revertemos ele para voltar ao seu nome correto
            splited.push_back(path);
            splited.push_back(nome);
            return splited;
        }
        else
        {
            nome.append(aux); // Senao e o delimitador entao crescentamos na string de nome
        }
    }

    reverse(nome.begin(),nome.end()); // Como armazenamos o nome invertido, revertemos ele para voltar ao seu nome correto
    splited.push_back("."); // Como não achou o delimitador, o diretorio pai e o mesmo diretorio do executavel
    splited.push_back(nome);

    return splited;
}

int arquivar(char* dir)
{
    vector<string> dirPath = splitPath(dir,"/"); // Separa o caminho passado em 2: caminho pai e nome do diretorio
    string nome = dirPath.back() + ".sar"; // Definimos o nome do arquivo que sera criado como nome.sar

    ofstream newFile;
    newFile.open(nome.c_str(), ios::binary|ios::trunc); // Abrimos um novo arquivo binario com o nome que definimos anteriormente

    Header head; // Criacao de um novo cabecalho
    head.save(newFile); // Salva o novo cabecalho no arquivo

    int status = arquivaRecursivo(dirPath[0], dirPath[1], newFile); // Arquiva recursivamente o conteudo do diretorio e subdiretorios

    if(status == 0)
    {
        head.changeStatus(); // Apos finalizar a inclusao do conteudo do diretorio no arquivo, mudamos o status do header para consistente
        head.save(newFile); // Gravamos o header modificado
    }


    newFile.close(); // Fecha o arquivo que havia sido aberto

    return status; // Retorna o status da operacao
}

int arquivaRecursivo(string pai, string nomeDir, ofstream& file)
{
    string dir;
    if(pai==".") // Se o pai é . basta criar um diretorio na raiz como o nome fornecido
        dir = nomeDir;
    else
        dir = pai + "/" + nomeDir; // Senao, concatenamos o caminho com o nome para preservar a hierarqui de diretorios

    DIR* ptrDir = opendir(dir.c_str()); // Ponteiro para o diretório atual (DIR representa um stream de diretório), abre e retorna um directory stream

    if(ptrDir == NULL) // Se nao foi possivel abrir o diretorio retornamos imediatamente
    {
        return 1;
    }

    Diretorio dirAtual; // Criamos um objeto do Tipo Diretorio para guardar as informacoes do diretorio atual que sera gravado posteriormente

    struct dirent* ptrEnt = NULL; // Usado para armazenar informações sobre o diretório aberto

    int contador = 0; // Inicia o contador de filhos do diretorio com 0

    vector<string> nomeArquivos; // Guarda os nomes dos arquivos contidos no diretorio
    vector<string> nomeDiretorios; // Guarda os dos subdiretorios contidos no diretorio atual

    while(ptrEnt = readdir(ptrDir))  // Le o proximo filho do diretório a cada iteracao (retorna um struct dirent*)
    {
        if(ptrEnt == NULL) // Se houve uma falha nessa leitura, retorna-se imediatamente o problema
        {
            return 1;
        }

        if(ptrEnt->d_type == DT_REG) // Se o filho for do tipo Arquivo Regular
        {
            contador++; // Incrementamos o contador de filhos
            nomeArquivos.push_back(string(ptrEnt->d_name)); // Guardamos o nome do arquivo filho
        }

        else if(ptrEnt->d_type == DT_DIR) // Se o filho for um Diretorio
        {
            if(strcmp(ptrEnt->d_name, ".") != 0 && strcmp(ptrEnt->d_name, "..") != 0) // Se esse diretorio nao for os diretorios triviais ("." ou "..")
            {
                contador++; // Incrementa o numero de filhos
                nomeDiretorios.push_back(string(ptrEnt->d_name)); // Guarda o nome do diretorio filho
            }
        }
    }

    dirAtual.setNome(nomeDir); // Atribui o nome do diretorio atual ao objeto que guarda as informacoes do diretorio
    dirAtual.setNFilhos(contador); // Tambem atribui-se o seu numero de filhos
    dirAtual.save(file); // E salva as informacoes no arquivo

    string nomeArquivo; // String auxiliar para guradar o nome de um arquivo filho
    string path; // Guarda o caminho onde esta localizado o arquivo para abri-lo

    while(!nomeArquivos.empty()) // Recupera todos os nomes dos arquivos filhos
    {
        nomeArquivo = nomeArquivos.back(); // Recupera o nome do aquivo da pilha de arquivos
        path = dir + "/" + nomeArquivo; // Constroi o caminho do arquivo para ser lido

        ifstream readFile;
        readFile.open(path.c_str(), ios::binary);  // Abre o arquivo filho

        if(readFile.is_open()) // Se a operacao de abertura ocorreu com sucesso
        {
            Arquivo fileAtual; // Cria-se um objeto do tipo Arquivo para guradar e gerenciar o salvamento o das informacoes do arquivo
            fileAtual.setNome(nomeArquivo); // Guardamos o nome
            fileAtual.save(file, readFile); // Salvamos as informacoes e conteudo no arquivo destino ".sar"
        }

        nomeArquivos.pop_back(); // Retiramos da pilha o arquivo ja salvo
    }

    while(!nomeDiretorios.empty()) // Recupera o nome de todos os subdiretorios filhos
    {
        arquivaRecursivo(dir, nomeDiretorios.back(), file); // Arquiva o diretorio e seu conteudo
        nomeDiretorios.pop_back(); // Retira da pilha o diretorio que ja foi arquivado
    }

    closedir(ptrDir); // fecha o diretorio atual

    return 0; // Retorna sucesso
}

int extrair(char* nomeArquivo)
{
    ifstream sarFile;
    sarFile.open(nomeArquivo, ios::binary); // Abre-se um arquivo para leitura

    if(!sarFile.is_open())
        return 2; // Se nao foi possivel abri-lo, retornamos que o arquivo nao e valido

    Header head; // Cria-se um Header para ser populado com as informacoes do cabecalho do arquivo aberto
    head.load(sarFile); // Carrega o cabecalho

    if(head.getExtensao().compare(".sar") != 0 || head.getStatus() == 1)
    {
        return 2; // Se a extensao nao e compativel ou se o arquivo e inconsistente, retornamos que o arquivo nao e valido
    }

    char tipoAtual; // Guarda o tipo do primeiro registro
    sarFile.read(&tipoAtual, sizeof(tipoAtual)); // Recupera o tipo do registro. Note que o primeiro registro sempre sera um diretorio,\
    porem essa leitura e necessaria para mover o ponteiro para o proximo campo do registro, escolhemos fazer dessa maneira para diminuir a complexidade do algoritmo

    int status = extraiRecursivo(sarFile, "."); // Extrai o conteudo do diretorio raiz. Como na descricao do projeto nao havia especificado o local para gerar o arquivo .sar\
    decidimos coloca-lo no mesmo diretorio em que se encontra o executavel, por isso o segundo parametro e "."

    sarFile.close(); // Fechamos o arquivo que tinhamos aberto para leitura

    return status; // Retorna o status da operacao
}

int extraiRecursivo(ifstream& sarFile, string pathPai)
{
    Diretorio dirAtual;
    dirAtual.load(sarFile);

    string pathCorrente = pathPai+"/"+dirAtual.getNome(); // Cria-se o nome do caminho onde sera criado o novo diretorio lido

    int dirStatus = mkdir(pathCorrente.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // Cria o diretorio no caminho especificado em modo de permissao total

    if (dirStatus == -1) // Se nao foi possivel criar o diretorio
    {
        return 3;
    }

    for(int i = 0; i < dirAtual.getNFilhos(); i++) // Para cada filho do diretorio (que esta guardado no objeto dirAtual)
    {
        char tipoFilho;

        sarFile.read(&tipoFilho, sizeof(tipoFilho)); // Le o tipo do filho

        if(tipoFilho == 'D') // Se for diretorio extrai recursivamente
        {
            if(extraiRecursivo(sarFile, pathCorrente) == 4) // se a operacao nao ocorreu com sucesso retorna imediatamente o erro
            {
                return 3;
            }
        }
        else // Se for arquivo
        {
            Arquivo novoArquivo; // Cria-se um objeto para guardar as informacoes do arquivo que sera lido
            novoArquivo.load(sarFile, pathCorrente); // Recupera o arquivo no seu devido diretorio
        }
    }

    return 0; // Retorna sucesso
}

int listar(char* nomeArquivo)
{
    ifstream sarFile;
    sarFile.open(nomeArquivo, ios::binary); // Abre o arquivo para leitura

    if(!sarFile.is_open()) // Se nao abriu retorna o erro
        return 2;

    Header head;
    head.load(sarFile);

    if(head.getExtensao().compare(".sar") != 0 || head.getStatus() == 1) // Verifica se a extensao e valida e se o arquivo e consistente
    {
        return 2; // Não é um arquivo .sar ou é inconsistente
    }

    char tipoAtual;
    sarFile.read(&tipoAtual, sizeof(tipoAtual));

    listarRecursivo(sarFile, 0); // Lista recursivamente o conteudo e inicia com o nivel da arvore 0

    return 0;
}

void listarRecursivo(ifstream& file, int nivel)
{
    Diretorio dirAtual;
    dirAtual.load(file);

    if(dirAtual.getNFilhos() < 0) // Se o arquivo nao contem mais registro pra le, apenas retorna
        return;

    for(int i = 0; i<=nivel; i++) // Desenha o a quantidade de niveis
        cout<<"-";

    cout<<dirAtual.getNome()<<"/"<<endl;

    for(int i = 0; i < dirAtual.getNFilhos(); i++) // Le todos os filhos e lista
    {
        char tipoFilho;

        file.read(&tipoFilho, sizeof(tipoFilho));

        if(tipoFilho == 'D') // Se for um diretorio lista recursivamente no nivel superior
        {
            listarRecursivo(file, nivel+1);
        }
        else if(tipoFilho == 'F')
        {
            Arquivo novoArquivo;
            novoArquivo.loadInfo(file);

            for(int j = 0; j<=nivel+1; j++)
                cout<<"-";

            cout<<novoArquivo.getNome()<<endl;

            if(file.eof())
            {
                return;
            }
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
