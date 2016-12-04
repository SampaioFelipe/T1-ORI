#include "sar.h"

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
            status = listar(argv[2]);
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
