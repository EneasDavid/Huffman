#include <stdio.h>
#include <locale.h> //Para podermos interpretar acentos
#include <string.h>
/*
gcc -o execucaoTabela tabelaFrequencia.c
/.execucaoTabela
bateriaDeTestes/teste.txt
*/
#define TAMANHO_ASCII 256 //estamos defininco isso aqui porque vamos usar esse tamanho com frequencia
#define TAMANHO_ENTRADA 1024 // Definimos um tamanho máximo para a entrada

void preenchendoEntrada(unsigned char *entrada) {
    printf("Digite o caminho do arquivo: ");
    char nomeArquivo[100];
    
    // Lendo o nome do arquivo
    if (scanf("%99s", nomeArquivo) != 1) {
        //o %99s garante que só sejam lidos 100 caracteres, e em caso de tentar adicionar mais, ele retorna um erro e encerra a aplicação
        printf("Erro ao ler o caminho do arquivo.\n");
        return;
    }

    // Abrindo o arquivo
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lendo o conteúdo do arquivo
    size_t len = fread(entrada, sizeof(unsigned char), TAMANHO_ENTRADA - 1, arquivo);
    entrada[len] = '\0'; // Assegura que a entrada é terminada com um caractere nulo

    // Fechando o arquivo
    fclose(arquivo);
}


void contaFrequencia(unsigned char *entrada, unsigned int *tabela){
    /*percorremos toda a entrada e sicrono a isso vamos preenchendo
    a tabela na posição referente a sua posição na tabela ASCII*/
    while(*entrada){
        tabela[*entrada]++;
        entrada++;
    }
}

void testeContaFrequencia( unsigned int *tabela, unsigned char *entrada){
    //   Teste de função contaFrequencia
    printf("\tTabela de frequencia\n");
    for(int i=0; i<TAMANHO_ASCII; i++){
        // %u na linha abaixo é usado para garantir que não vai imprimir sinal negativo
        if(tabela[i]) printf("\tO caractere %c aparece %u vezes\n", i, tabela[i]);
    }
    printf("%s\n",entrada);
}

int main(){
    setlocale(LC_ALL, "Portuguese"); //Mudamos a tabela de caracteres para português, assim interpretanto nosso acentos e cedilhas

    //unsigned força o valor a ser positivo

    /*O uso do 'unsigned char' é para que o compilador não interprete
    o valor como um caractere, mas sim como um número, isso garante a 
    possivilidade de interpertar imagens, textos e audios.*/

    /*Char tem lado possitivo e negativo o que limita seu uso entre 
    -127 a 127, mas se quisermos algo mais otimizado, ignoraremos o 
    lado negativo,  o que nos possibilita armazenar 255 bits, batendo 
    com a tabelas ASCII estendida */
    
    //---------------------------------------Parte 1, cria tabela de frequência ---------------------------------------------------
    unsigned char entrada[TAMANHO_ENTRADA];
    unsigned int tabelaFrequencia[TAMANHO_ASCII]={0};
    preenchendoEntrada(entrada);
    contaFrequencia(entrada, tabelaFrequencia);
    testeContaFrequencia(tabelaFrequencia, entrada);
    //---------------------------------------Parte 1, cria tabela de frequência ---------------------------------------------------

    return 0;
}