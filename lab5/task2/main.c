#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include "strrev.h"

#define THREADS_COUNT 3

struct {
	pthread_mutex_t mutex;
	FILE * f; 

} shared;


void * reverse(void * args) {
	int id = (int)args;
	while (1) { 
		pthread_mutex_lock(&shared.mutex);
		char buff[64];
		char * res = fgets(buff, 64, shared.f);
		pthread_mutex_unlock(&shared.mutex);
		if (res == NULL)
			return 0;
		res = strrev(buff);
		printf("%d >> %s\n", id, res);
	}
	return 0;
}

int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("Enter the file path!!!\n");
		return 0;
	}
	FILE * f = fopen(argv[1], "r");
	if (f == NULL) {
		printf("Can't open the file: %s\n", argv[1]);
		return 1;
	}

	shared.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	shared.f = f;

	pthread_t threads[THREADS_COUNT];
	for (int i = 0; i < THREADS_COUNT; ++i)
		pthread_create(&threads[i], NULL, reverse, (void *)i);

	for (int i = 0; i < THREADS_COUNT; ++i)
		pthread_join(threads[i], NULL);

	fclose(f);		
	
	getchar();
	return 0;
}
