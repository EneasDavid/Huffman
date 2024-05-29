[![Badge em desenvolvimento](https://img.shields.io/badge/Andamento%20do%20projeto-15%-39E09B)]
[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)]

## Projeto Algoritmo de Huffman

### Descrição
O projeto consiste em implementar o algoritmo de Huffman para compressão de arquivos. O algoritmo de Huffman é um método de compressão que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo. O algoritmo foi desenvolvido por David A. Huffman em 1952, enquanto era um estudante de graduação no MIT, e foi publicado em 1952.

###Etapas de criação
| Etapas | Status | Branch |
| -------- | -------- | -------- |
| 1. Criação de vetor de frequencia | <ul><li>- [x] feito</li><ul> | contarFrequencia |
| 2. Criação da árvore de Huffman | <ul><li>- [ ] feito</li><ul>| arvoreHuffman |
| 3. Criação da tabela de códigos | <ul><li>- [ ] feito</li><ul>| tabelaCodigos |
| 4. Compressão do arquivo | <ul><li>- [ ] feito</li><ul>| compressao |
| 5. Descompressão do arquivo | <ul><li>- [ ] feito</li><ul>| descompressao |
| 6. Testes | <ul><li>- [ ] feito</li><ul>| testes |
| 7. Documentação | <ul><li>- [ ] feito</li><ul>| documentacao |
| 8. porjeto Final | <ul><li>- [ ] feito</li><ul>| main |

### Integrantes
| Discente | Curso | 
| -------- | -------- |
| David Enéas | Ciência da Computação |  
| Mayara Jacinto | Engenharia de Computação |
| Julya | Engenharia de Computação | 
| Pedro Guloso | Engenharia de Computação |

### Estrutura do Projeto
```
├── README.md
├── tabelaFrequencia.c
├── execucaotabela.exe
└── bateriaDeTestes
    ├── teste.txt
    └── 20240110_122255.jpg
```

### Compilação
Para compilar o projeto, basta executar o comando `gcc -o execucaoTabela tabelaFrequencia.c` no terminal. O comando irá gerar um executável chamado `execucaoTabela`.

### Execução
Para executar o projeto, basta rodar o comando `./execucaoTabela` no terminal. O programa irá solicitar o arquivo a ser comprimido, `bateriaDeTestes/teste.txt` o teste padrão é realizado nesse arquivo.

### De forma resumida:

```
gcc -o execucaoTabela tabelaFrequencia.c
```
`Gera o executavel do projeto`

```
./execucaoTabela
```
`Inicia o executavel do projeto`

```
bateriaDeTestes/teste.txt
```
`fornece o caminho do arquivo teste`
