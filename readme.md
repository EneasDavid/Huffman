![Badge em desenvolvimento](https://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=YELLOW&style=for-the-badge)
![C](https://img.shields.io/badge/C-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)


# Projeto de Estrutura de Dados II - REAV
Huffman 
O projeto consiste em implementar o algoritmo de Huffman para compressão de arquivos. O algoritmo de Huffman é um método de compressão que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo. O algoritmo foi desenvolvido por David A. Huffman em 1952, enquanto era um estudante de graduação no MIT, e foi publicado em 1952.


## Tabela de conteúdos
- [Alterações no cabeçalho do arquivo compactado](#alterações-no-cabeçalho-do-arquivo-compactado)
- [Instalação](#instalação)
- [Método de Uso](#método-de-uso)
- [Integrantes](#Integrantes)
- [Licença](#licença)

## Alterações no cabeçalho do arquivo compactado
- [x] Byte 1: IGUAL
- [x] Byte 2: IGUAL
- [x] Bytes seguintes: Árvore (IGUAL)
- [x] Byte após a árvore: os três primeiros bits (esquerda para direita) devem conter o tamanho do nome da extensão do arquivo original. O maior valor possível é 6, isto é, 110. Caso seja acima, informar ao usuário que não é possível! Os outros 5 bits são lixo.
- [x] Bytes seguintes (no máximo 6): extensão do arquivo original
- [x] Bytes seguintes: dados compactados


## Instalação

```bash
git clone https://github.com/EneasDavid/Huffman/tree/reav
```

## Método de Uso
Para compilar o projeto, basta executar o comando `gcc -o huff src/utils.c src/algoritimo_compressao.c src/algoritimo_descompressao.c src/huffman.c src/main.c` no terminal. O comando irá gerar um executável chamado `huff`.


Para executar o projeto, basta rodar o comando `./huff` no terminal. O programa irá solicitar o arquivo a ser comprimido.
#### de forma resumida

```bash
gcc -o huff src/utils.c src/algoritimo_compressao.c src/algoritimo_descompressao.c src/huffman.c src/main.c
```
```bash
./huff
```

## Integrantes
| Discente | Curso | 
| -------- | -------- |
| David Enéas | Ciência da Computação |  

## License

...