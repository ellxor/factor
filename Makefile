CC = gcc
CFLAGS = -O3 -s
DEBUG = -Wall -Wextra -Wpedantic
ARCH = -mbmi

default:; gcc factor.c -o factor.exe $(CFLAGS) $(DEBUG) $(ARCH)
format:; indent *.c -linux && rm *~
