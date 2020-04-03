#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "matworker.h"

const char * keys[] = {"max", "min", "sum", "mul"};

int main(int argc, char * argv[]) {
	
	key_t key = 5678;
	int *shm, *s, shmid;
	int mat[N][N];
	createMatrix(mat);

	int size = sizeof(int)*N*N;

	if ((shmid = shmget(key, size, IPC_CREAT | 0666)) < 0) {
        	perror("shmget");
        	exit(1);
    	}

	if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
        	perror("shmat");
        	exit(1);
    	}

	s = shm;
	int k = 0;
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j) {
			s[k] = mat[i][j]; 
			k++;
		}
	}
	for (int i = 0; i < 4; ++i) {
		pid_t pid = fork();
		if (pid == 0) {
			char _key[32];
			sprintf(_key, "%d", key);
			int rc = execl("./fork", "fork", _key, keys[i], NULL);
			if (rc < 0) {
				perror(strerror(errno));
			}
			exit(0);
		}
	}
	
	wait(NULL);
	getchar();		
	if (shmctl(shmid, IPC_RMID, 0) < 0) {
		printf("Невозможно удалить область\n");
		exit(1);
	}

	return 0;
}
