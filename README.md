# hexdump-c

hexdump é uma ferramenta de linha de comando que mostra o conteúdo bruto de um arquivo. Ele simplesmente mostra os bytes — em hexadecimal — e, ao lado, qual caractere ASCII cada byte representa (quando representa um caractere imprimível).

## Demonstração

```
$ ./hexdump <NOME_ARQUIVO.bin>
00000000: 7f45 4c46 0201 0100 0000 0000 0000 0000  .ELF............
00000010: 0300 3e00 0100 0000 4010 0000 0000 0000  ..>.....@.......
00000020: 4000 0000 0000 0000 a036 0000 0000 0000  @........6......
00000030: 0000 0000 4000 3800 0f00 4000 1f00 1e00  ....@.8...@.....
00000040: 0600 0000 0400 0000 4000 0000 0000 0000  ........@.......
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
