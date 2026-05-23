# hexdump-c

hexdump é uma ferramenta de linha de comando que mostra o conteúdo bruto de um arquivo. Ele simplesmente mostra os bytes — em hexadecimal — e, ao lado, qual caractere ASCII cada byte representa (quando representa um caractere imprimível). Esta versão foi inspirada no `hexdump -C`.

## Demonstração

```
$ ./hexdump <NOME_ARQUIVO.bin>
00000000  7f 45 4c 46 02 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
00000010  03 00 3e 00 01 00 00 00  00 11 00 00 00 00 00 00  |..>.............|
00000020  40 00 00 00 00 00 00 00  38 47 00 00 00 00 00 00  |@.......8G......|
00000030  00 00 00 00 40 00 38 00  0f 00 40 00 27 00 26 00  |....@.8...@.'.&.|
00000040  06 00 00 00 04 00 00 00  40 00 00 00 00 00 00 00  |........@.......|
00000050  40 00 00 00 00 00 00 00  40 00 00 00 00 00 00 00  |@.......@.......|
```

## Build

Requer `gcc` e `make`. Testado em Linux (Arch via WSL2).

```
make           # compila e gera ./hexdump
make clean     # remove .o e binário
```
## Uso

``` 
$ ./hexdump [-n N] [-s OFFSET] [-c] [arquivo]
```

## Estrutura

```
hexdump-c/
├── Makefile
├── README.md
├── .gitignore
└── src/
    └── main.c
```
## Flags suportadas

| Flag         | Argumento | Descrição                                              |
|--------------|-----------|--------------------------------------------------------|
| `-n N`       | inteiro   | Limita a leitura aos primeiros `N` bytes.              |
| `-s OFFSET`  | inteiro   | Pula `OFFSET` bytes do início do arquivo.              |
| `-c`         | —         | Ativa modo conciso (substitui linhas idênticas por `*`). |

## Exemplos

| Comando                                    | O que faz                                          |
|--------------------------------------------|----------------------------------------------------|
| `./hexdump arquivo.bin`                    | Dump completo do arquivo.                          |
| `./hexdump -n 64 arquivo.bin`              | Lê só os primeiros 64 bytes.                       |
| `./hexdump -s 256 arquivo.bin`             | Começa do byte 256.                                |
| `./hexdump -s 100 -n 32 arquivo.bin`       | Lê 32 bytes a partir do offset 100.                |
| `./hexdump -c arquivo.bin`                 | Modo conciso (linhas repetidas viram `*`).         |

## Decisões de design

- Uso de `hexdump -C` como referência, não `xxd`.
- Implementei `-c` em vez de `-v` para ativar squeeze (oposto do `hexdump -C` real).

## Limitações conhecidas
 
- Não suporta arquivos > 2 GB devido ao uso de `long`.
- Não implementa flags de formato customizado (`-e`, `-f` do `hexdump` original).
## Próximos passos possíveis

- Refatorar em módulos
- Suporte a stdin com `-s`
