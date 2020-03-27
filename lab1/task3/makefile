build:
	gcc -Wall -c -o fork.o fork.c
	gcc -o fork fork.o
	gcc -Wall -c -o task3.o task3.c
	gcc -o task3 task3.o
test:
	${PWD}/task3 -m 4 4 -a 5 5 4 3 2 1 -s "Hi, my friend!"
clean:
	rm task3 task3.o fork fork.o
