CC=gcc
CFLAGS=-c
path=./textfiles

build:
	${CC} -Wall ${CFLAGS} -o main.o main.c
	${CC} -o main main.o
test:
	./main
	wc -c ${path}/text1.txt ${path}/text2.txt ${path}/text3.txt
clean:
	rm main main.o

