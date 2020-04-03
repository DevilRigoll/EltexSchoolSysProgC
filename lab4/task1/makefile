CC=gcc
CFLAGS=-c

build: matworker.o
	${CC} -Wall ${CFLAGS} -o main.o main.c
	${CC} -o main main.o matworker.o 
	${CC} -Wall ${CFLAGS} -o fork.o  fork.c
	${CC} -o fork fork.o matworker.o

test:
	./main
clean:
	rm main fork main.o fork.o matworker.o

matworker.o: matworker.c matworker.h
	${CC} ${CFLAGS} matworker.c

