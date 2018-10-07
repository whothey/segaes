# AES

A personal implementation of AES, an assignment for Security classes @ UFFS.

Note: some operations are passive of optimization (see the MatMul in
aes.c#mix_cols and even the live generation of S-Box and revS-Box), they were
chosen to be implemented this way until assignment completion (due to time
schedule issues).

## Compile Options

Two release options: debug and release. Debug carries with it symbols and
non-optimized operations, while release applies GCC optimizations and tear off
debug code.

Binaries could be found at `bin` directory.

```sh
$ make debug # Create a debuggable binary
$ make relase # Create an optimized binary
```

## Debug Loop

Clean binaries, compile with debug options, then run it.

```sh
$ make clean debug run
```

## Release bin

Clean binaries and recompile with optimizations:

```sh
$ make clean release
```
