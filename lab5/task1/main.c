#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include "strrev.h"

void * reverse(void * args) {
	char * str = (char *)args;
	str = strrev(str);	
	printf("%s\n", str);
	return 0;
}

int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("Enter the string!!!\n");
		return 0;
	}
	int result;
	pthread_t * threads = NULL;			
	int threads_id = 0;
	char * str = strtok(argv[1], " ");
	while(str != NULL) {
		threads = realloc(threads, (threads_id + 1) * sizeof(pthread_t));
		result = pthread_create(&threads[threads_id], NULL, reverse, (void * )str);
		str = strtok(NULL, " ");
		threads_id++;
	}
	free(threads);
	getchar();
	return 0;
}
