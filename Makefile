CC = clang
CFLAGS = -O3 -s -fno-builtin

default:; clang factor.c -o factor.exe $(CFLAGS)
format:; clang-format -i factor.c
