CC=~/.zig/zig cc

default:; $(CC) factor.c -o factor.exe -O3 -fno-builtin; strip factor.exe
