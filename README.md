# hexdump-c

hexdump é uma ferramenta de linha de comando que mostra o conteúdo bruto de um arquivo. Ele simplesmente mostra os bytes — em hexadecimal — e, ao lado, qual caractere ASCII cada byte representa (quando representa um caractere imprimível).

## Demonstração

```
$ ./hexdump <NOME_ARQUIVO.bin>
00000000: 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 |.ELF............|
00000010: 03 00 3e 00 01 00 00 00 00 11 00 00 00 00 00 00 |..>.............|
00000020: 40 00 00 00 00 00 00 00 38 47 00 00 00 00 00 00 |@.......8G......|
00000030: 00 00 00 00 40 00 38 00 0f 00 40 00 27 00 26 00 |....@.8...@.'.&.|
00000040: 06 00 00 00 04 00 00 00 40 00 00 00 00 00 00 00 |........@.......|
00000050: 40 00 00 00 00 00 00 00 40 00 00 00 00 00 00 00 |@.......@.......|
```

## Build

Requer `gcc` e `make`. Testado em Linux (Arch via WSL2).

```
make           # compila e gera ./hexdump
make clean     # remove .o e binário
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

## Decisões de design

-
-

## Limitações conhecidas

-
-

## Próximos passos possíveis

Implementar os comandos:

- `-n N` — lê só os primeiros N bytes
- `-s OFFSET` — começa do offset.
