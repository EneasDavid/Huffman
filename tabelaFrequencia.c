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

int testeMalloc(void *ponteiro, char *funcao){
    //Testa se a alocação de memória foi bem sucedida
    if(ponteiro==NULL){
        printf("Erro na alocação de memória na função %s\n", funcao);
        return 1;
    }
    return 0;
}

void preenchendoEntrada(unsigned char *entrada) {
    printf("Digite o caminho do arquivo: ");
    char nomeArquivo[100];
    
    // Lendo o nome do arquivo
    if (scanf("%99s", nomeArquivo) != 1) {
        // O %99s garante que só sejam lidos 100 caracteres, e em caso de tentar adicionar mais, ele retorna um erro e encerra a aplicação
        printf("Erro ao ler o caminho do arquivo.\n");
        return;
    }

    // Abrindo o arquivo no modo binário - rb
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    // Lendo o conteúdo do arquivo byte a byte
    
    size_t len = 0;
    int byte;
    while ((byte = fgetc(arquivo)) != EOF && len < TAMANHO_ENTRADA - 1) entrada[len++] = (unsigned char)byte;
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

void imprimirFrequencia( unsigned int *tabela, unsigned char *entrada){
    //   Teste de função contaFrequencia
    printf("\tTabela de frequencia\n");
    for(int i=0; i<TAMANHO_ASCII; i++){
        // %u na linha abaixo é usado para garantir que não vai imprimir sinal negativo
        if(tabela[i]) printf("O caractere %c aparece %u vezes\n", i, tabela[i]);
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
            testeMalloc(novo, "preencherListaEncadeada");
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

No *removerPrimeiro(Lista *lista){
    //Logica de dequeue
    No *removido=lista->inicio;
    if(removido!=NULL){
        lista->inicio=removido->proximo;
        removido->proximo=NULL;
        lista->tam--;
    }
    return removido;
}

No *montandoArvore(Lista *lista){
    /*
    Apos ordenar a frequencia, sabemos que vamos pegar
    os dois elementos com menos frequencia e juntar em 
    um novo nó na nossa arvore nessa logica, vamos pegar 
    os dois primeiros elementos da lista e juntar em 
    esquerdo e direto na arvore de huffman, e declarar 
    o proximo como nulo
    */
    while(lista->tam>1){
        No *novo=(No*)malloc(sizeof(No));
        testeMalloc(novo, "montandoArvore");
        novo->esquerda=removerPrimeiro(lista);
        novo->direita=removerPrimeiro(lista);
        novo->frequencia=novo->esquerda->frequencia + novo->direita->frequencia;
        novo->caractere=0;
        novo->proximo=NULL;
        insercaoOrdenada(lista, novo);
    }
    return removerPrimeiro(lista);
}

void imprimirArvoreHuffmanFormatada(No *raiz) {
    if (raiz == NULL) return;
    printf("(");
    if (raiz->esquerda == NULL && raiz->direita == NULL) {
        printf("%c", raiz->caractere);
    } else {
        imprimirArvoreHuffmanFormatada(raiz->esquerda);
        imprimirArvoreHuffmanFormatada(raiz->direita);
    }
    printf(") ");
}

/*
Imprimir arvore sem formatação
void imprimirArvoreHuffman(No *raiz, int tamanho){
    //logica de impressão de arvore
    if(raiz->esquerda==NULL && raiz->direita==NULL){
        printf("Caractere: %c\tFrequencia: %u\n", raiz->caractere, raiz->frequencia);
    }else{
        imprimirArvoreHuffman(raiz->esquerda, tamanho+1);
        imprimirArvoreHuffman(raiz->direita, tamanho+1);
    }
}*/

int alturaArvore(No *raiz){
    //logica de altura de arvore
    //Se a raiz for nula, a altura é -1
    //Se a raiz tiver filhos, a altura é 1 + a maior altura entre os filhos
    if(raiz==NULL) return -1;
    int alturaEsquerda=alturaArvore(raiz->esquerda);
    int alturaDireita=alturaArvore(raiz->direita);
    return 1+(alturaEsquerda>alturaDireita?alturaEsquerda:alturaDireita);
}
//Poderia ser ignorado com strdup??
char ** alocaoDicionario(int alturaArvore){
    //logica de alocação de dicionario
    char **dicionario=(char**)malloc(TAMANHO_ASCII*sizeof(char*));
    testeMalloc(dicionario, "alocaDicionario");
    for(int i=0; i<TAMANHO_ASCII; i++){
        dicionario[i]=calloc(alturaArvore, sizeof(char));
        //calloc aloca e inicializa a memória com 0, já o malloc mantem o lixo de memoria 
        testeMalloc(dicionario[i], "alocaDicionario");
    }
    return dicionario;
}
//REVER URGENTE 
void preencherDicionario(char **dicionario, No *raiz, char *caminho, int alturaArvore){
    if (raiz->esquerda == NULL && raiz->direita == NULL){ 
        /*Se passar, estamos em uma folha e estando em ponto sem filhos
        podemos interpretar que chegamos ao fim de um galho e podeoms
        preencher o dicionario com o caminho percorrido até aqui
        */
        caminho[alturaArvore] = '\0';
        strcpy(dicionario[raiz->caractere], caminho);
        //se preferiu usar strcpy porque já foi pre alocado o espaço, já o strdup aloca memória suficiente para a string e copia a string para a memória alocada
        return; //serve para evitar o else
   
    }

    // Cria uma cópia local do caminho para manipulação
    char caminhoEsquerda[alturaArvore + 2]; 
    char caminhoDireita[alturaArvore + 2];
    // +2 para o caractere nulo e o caractere que será adicionado
    strcpy(caminhoEsquerda, caminho);
    strcpy(caminhoDireita, caminho);

    //Zero significa que o caminho está a esquerda
    caminhoEsquerda[alturaArvore] = '0'; 
    caminhoEsquerda[alturaArvore + 1] = '\0';
    // +1 para o caractere nulo que é \0
    preencherDicionario(dicionario, raiz->esquerda, caminhoEsquerda, alturaArvore + 1);

    //Um significa que o caminho está a direita
    caminhoDireita[alturaArvore] = '1'; 
    caminhoDireita[alturaArvore + 1] = '\0';
    preencherDicionario(dicionario, raiz->direita, caminhoDireita, alturaArvore + 1);
}


void imprimirDicionario(char **dicicionario){
    printf("\tDicionario\n");
    for(int i=0;i<TAMANHO_ASCII; i++){
        if (dicicionario[i][0]) printf("Codigo: %3d\tCaractere: %c\tCaminho: %s\n", i, i, dicicionario[i]);
        // %3d formata para que a saida sempre seja (000),(099), (222)
        //dicionario[i][0] o [0] é usado para garantir que o dicionario[i] não é uma string vazia
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
    //Teste de contarFrequencia
    imprimirFrequencia(tabelaFrequencia, entrada);
    //---------------------------------------Parte 2, Criar lista Encadeada ---------------------------------------------------
    Lista lista;
    criarLista(&lista);
    preencherListaEncadeada(tabelaFrequencia, &lista);
    //Teste de lista
    imprimirLista(&lista);
    //---------------------------------------Parte 3, cria arvore de Huffman ---------------------------------------------------
    No *raiz=montandoArvore(&lista);
    printf("\tArvore de Huffman\n");
    //Teste de arvore
    imprimirArvoreHuffmanFormatada(raiz);
    printf("\n");
    //---------------------------------------Parte 4, cria um dicionario ---------------------------------------------------
    int altura=alturaArvore(raiz)+1; 
        /*
        vai ser usado em todo o codigo como indicador de colunas
        Possue um +1 porque a raiz não é contada na altura
        */
    alocaoDicionario(altura);
    char **dicionario=alocaoDicionario(altura);
    preencherDicionario(dicionario, raiz, "", 0);
    //Teste de dicionario
    imprimirDicionario(dicionario);
    //---------------------------------------Parte 4, codificando ---------------------------------------------------\
    
    return 0;
}