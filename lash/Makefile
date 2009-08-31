## Copy this Makefile to your source directory and type `make' to build.

CC = gcc
OUTPUT = lash
CFLAGS = -g -Wall

all: shell

shell : main.c lex.c lex.h
	${CC} ${CFLAGS} -o ${OUTPUT} -DDEBUG=0 main.c lex.c

test_lex : test_lex.c lex.c lex.h
	${CC} ${CFLAGS} -o test_lex -DDEBUG=1 test_lex.c lex.c

clean :
	rm -f *.o *.a *~ core shell  

