#include "../libs/utils.h"
#include "../libs/huffman.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int escolha;
    char caminho[TAMANHO_ASCII];

    do
    {
        escolha = mensagem_inicial();
        if (!escolha)
        {
            break;
        }
        else if (escolha != 1 && escolha != 2)
        {
            printf("Digite uma escolha válida!\n");
            continue;
        }
        printf("Digite o caminho do arquivo: ");
        scanf("%s", caminho);
        switch (escolha)
        {
        case 1:
            comprimir(caminho);
            break;

        case 2:
            printf("Digite como deve ser salvo o arquivo. Exemplo: 'imagem.png': ");
            char caminho_descompressao[TAMANHO_ASCII];
            scanf("%s", caminho_descompressao);
            descomprimir(caminho, caminho_descompressao);
            break;

        default:
            printf("Digite uma escolha válida!\n");
            break;
        }
    } while (escolha != 0);

    return 0;
}