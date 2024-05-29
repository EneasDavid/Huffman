#include <stdio.h>
#include <locale.h> //Para podermos interpretar acentos
#include <string.h>
#include <stdlib.h> //Para podermos usar a função malloc

#define TAMANHO_ASCII 256 //estamos defininco isso aqui porque vamos usar esse tamanho com frequencia
#define TAMANHO_ENTRADA 1024 // Definimos um tamanho máximo para a entrada

typedef struct no{
    //no vai assumir o papel de dois tipos de estruturas de dados, uma lista encadeada e uma árvore binaria
    unsigned char caractere;
    unsigned int frequencia;
    struct no *esquerda, *direita, *proximo;
    //Esquerda e direita são usados para a árvore de Huffman
    //Proximo é usado para a lista encadeada
}No;

typedef struct lista{
    //E usado apenas para reduzir codigo, permitindo que a lista encadeada seja mais facilmente manipulada (remove a necessidade de uasr ponteiro de ponteiro)
    No *inicio;
    int tam;
}Lista;

void preenchendoEntrada(unsigned char *entrada) {
    printf("Digite o caminho do arquivo: ");
    char nomeArquivo[100];
    
    // Lendo o nome do arquivo
    if (scanf("%99s", nomeArquivo) !=1) {
        //o %99s garante que só sejam lidos 100 caracteres, e em caso de tentar adicionar mais, ele retorna um erro e encerra a aplicação
        printf("Erro ao ler o caminho do arquivo.\n");
        return;
    }

    // Abrindo o arquivo
    FILE *arquivo=fopen(nomeArquivo, "r");
    if (arquivo==NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lendo o conteúdo do arquivo
    size_t len=fread(entrada, sizeof(unsigned char), TAMANHO_ENTRADA - 1, arquivo);
    entrada[len]='\0'; // Assegura que a entrada é terminada com um caractere nulo

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

void criarLista(Lista *lista){
    //Cria a lista apontando o inicio para nulo e informa que o tamnaho é zero, porque não há elementos na lista
    lista->inicio=NULL;
    lista->tam=0;
}

void insercaoOrdenada(Lista *lista, No *novo){ //logica de enqueue
    //Se a lista estiver vazia ou a frequencia do novo nó for menor que a frequencia do primeiro nó da lista
    if(lista->inicio==NULL || novo->frequencia <=lista->inicio->frequencia){
        novo->proximo=lista->inicio;
        lista->inicio=novo;
    }else{
        //Se a frequencia do novo nó for maior que a frequencia do primeiro nó da lista
        No *atual=lista->inicio;
        while(atual->proximo !=NULL && atual->proximo->frequencia < novo->frequencia){
            atual=atual->proximo;
        }
        novo->proximo=atual->proximo;
        atual->proximo=novo;
    }
    lista->tam++;
}

 void preencherListaEncadeada(unsigned int *tabela, Lista *lista){
    for(int i=0; i<TAMANHO_ASCII; i++){
        if(tabela[i]){
            No *novo=(No*)malloc(sizeof(No));
            if(novo==NULL){
                printf("Erro na alocação de memoria na função preencherListaEncadeada\n");
                break;    
            }
            novo->caractere=i;
            novo->frequencia=tabela[i];
            novo->esquerda=NULL;
            novo->direita=NULL;
            novo->proximo=NULL;
            insercaoOrdenada(lista, novo);
        }
    }
}

void imprimirLista(Lista *lista){
    No *atual=lista->inicio;
    printf("\tLista Ordenada\n");
    while(atual!=NULL){
        printf("Caractere: %c, Frequencia: %u\n", atual->caractere, atual->frequencia);
        atual=atual->proximo;
    }
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
    //---------------------------------------Parte 2, Criar lista Encadeada ---------------------------------------------------
    Lista lista;
    criarLista(&lista);
    preencherListaEncadeada(tabelaFrequencia, &lista);
    imprimirLista(&lista);

    return 0;
}