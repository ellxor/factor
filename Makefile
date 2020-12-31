CC = clang
CFLAGS = -O3 -s -fno-builtin

default:; $(CC) factor.c -o factor.exe $(CFLAGS)
