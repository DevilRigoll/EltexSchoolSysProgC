CC=gcc
CFLAGS=-c
SRC_INC= strrev.c strrev.h

build: strrev.o
	${CC} -Wall  ${CFLAGS} -o main.o  main.c
	${CC} -o main main.o strrev.o -lpthread

test:
	./main "First man want to be a perfect programmer"

clean:
	rm main main.o strrev.o

list.o: ${SRC_INC}
	${CC} ${CFLAGS} strrev.c
