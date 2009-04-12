## Copy this Makefile to your source directory and type `make' to build.

CC = gcc
CFLAGS = -g 

all: shell 

shell : main.c lex.c lex.h string.c mystring.h linkedlist.c linkedlist.h builtincmd.c builtincmd.h common.c
	${CC} ${CFLAGS} main.c lex.c string.c linkedlist.c builtincmd.c common.c -o shell

clean :
	rm -f *.o *.a *~ core shell  

