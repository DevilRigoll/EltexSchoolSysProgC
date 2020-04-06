CC=gcc
CFLAGS=-c -lpthread
TERMINAL=gnome-terminal -e
SRC_INC= list.c list.h msgtypes.h

build: list.o msgtypes.h
	${CC} -Wall ${CFLAGS} -o server.o server.c
	${CC} -o server list.o server.o 
	${CC} -Wall  ${CFLAGS} -o client.o  client.c
	${CC} -o client client.o -lpthread

test:
	${TERMINAL} "${PWD}/server"
	sleep 1
	${TERMINAL} "${PWD}/client"
	${TERMINAL} "${PWD}/client"

clean:
	rm server server.o client client.o list.o

list.o: ${SRC_INC}
	${CC} ${CFLAGS} list.c


