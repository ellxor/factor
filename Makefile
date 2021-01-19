CC = clang -std=c++98
CFLAGS = -O3 -s

default:; clang factor.cc -o factor.exe $(CFLAGS)
format:; clang-format -i factor.cc
