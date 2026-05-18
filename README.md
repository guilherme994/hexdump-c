# hexdump-c

## Demonstração

```
$ ./calc
00000000: 7f45 4c46 0201 0100 0000 0000 0000 0000  .ELF............
00000010: 0300 3e00 0100 0000 4010 0000 0000 0000  ..>.....@.......
00000020: 4000 0000 0000 0000 a036 0000 0000 0000  @........6......
00000030: 0000 0000 4000 3800 0f00 4000 1f00 1e00  ....@.8...@.....
00000040: 0600 0000 0400 0000 4000 0000 0000 0000  ........@.......
```

## Comandos

- `-n N` — lê só os primeiros N bytes
- `q` — começa do offset.

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
- 
- 

## Limitações conhecidas


