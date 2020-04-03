#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "matworker.h"



int main(int argc, char * argv[]) {
	int * shm, shmid;
	int key = atoi(argv[1]);

	int mat[N][N];

	int size = sizeof(int)*N*N;
	if ((shmid = shmget(key, size, 0666)) < 0) {
        	perror("shmget");
        	exit(1);
    	}

	if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
        	perror("shmat");
        	exit(1);
    	}
	
	int k = 0;
	int * s = shm;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			mat[i][j] = s[k++];
	
	if (!strcmp(argv[2], "max")) {
		int res = maxElem(mat);
		printf("max = %d\n", res);
	}
	else if (!strcmp(argv[2], "min")) {
		int res = minElem(mat);
		printf("min = %d\n", res);
		
	}
	else if (!strcmp(argv[2], "sum")) {
		int res = sum(mat);
		printf("sum = %d\n", res);
	}
	else if (!strcmp(argv[2], "mul")) {
		int res = mul(mat);
		printf("mul = %d\n", res);
	}

	return 0;
}
