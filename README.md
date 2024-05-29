##Projeto Algoritmo de Huffman

### Descrição
O projeto consiste em implementar o algoritmo de Huffman para compressão de arquivos. O algoritmo de Huffman é um método de compressão que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo. O algoritmo foi desenvolvido por David A. Huffman em 1952, enquanto era um estudante de graduação no MIT, e foi publicado em 1952.

###Etapas de criação
1. Criação de vetor de frequencia
2. Criação da árvore de Huffman
3. Criação da tabela de códigos
4. Compressão do arquivo
5. Descompressão do arquivo


### Integrantes
- [David Enéas]
- [Mayara Jacinto]
- [Julya]
- [Pedro Guloso]

### Estrutura do Projeto
```
├── README.md
├── src
│   ├── main.cpp
│   ├── huffman.cpp
│   ├── huffman.h
│   ├── node.cpp
│   └── node.h
└── test
    ├── test_huffman.cpp
    └── test_node.cpp
```

### Compilação
Para compilar o projeto, basta executar o comando `make` no terminal. O comando irá gerar um executável chamado `huffman`.

### Execução
Para executar o projeto, basta rodar o comando `./huffman` no terminal. O programa irá comprimir o arquivo `input.txt` e gerar o arquivo `output.txt`.
