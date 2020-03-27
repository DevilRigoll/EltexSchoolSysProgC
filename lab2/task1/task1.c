#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void createMatrix(int mat[5][5]) {
	srand(time(NULL));
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			mat[i][j] = rand()%15;
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

int sum(int mat[5][5]) {
	int res = 0;
	for (int i = 0; i < 5; ++i)
	for (int j = 0; j < 5; ++j)
		res += mat[i][j];
	return res;
}


int mul(int mat[5][5]) {
	int res = 1;
	for (int i = 0; i < 5; ++i)
	for (int j = 0; j < 5; ++j)
		res *= mat[i][j];
	return res;
}

int minElem(int mat[5][5]) {
	int res = 999;
	for (int i = 0; i < 5; ++i)
	for (int j = 0; j < 5; ++j)
		if (mat[i][j] < res)
			res = mat[i][j];
	return res;
}

int maxElem(int mat[5][5]) {
	int res = 0;
	for (int i = 0; i < 5; ++i)
	for (int j = 0; j < 5; ++j)
		if (mat[i][j] > res)
			res = mat[i][j];
	return res;
}

void fork_proc(int mat[5][5], int (*f)(int mat[5][5] ), int * m_pipe) {
	int result;	
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0) {
		close(fd[0]);
		result = f(mat);
		write(fd[1], &result, sizeof(int));
		exit(0);
	} 
	else {
		close(fd[1]);
		*m_pipe = fd[0];
	}
}

int main(int argc, char * argv[]) {
	
	int mat[5][5];
	createMatrix(mat);
	
	int max_pipe;
	fork_proc(mat, maxElem, &max_pipe);
	int min_pipe;
	fork_proc(mat, minElem, &min_pipe);
	int sum_pipe;
	fork_proc(mat, sum, &sum_pipe);
	int mul_pipe;
	fork_proc(mat, mul, &mul_pipe);

	
	int res;
	read(max_pipe, &res, sizeof(int));
	printf("max = %d\n", res);
	read(min_pipe, &res, sizeof(int));
	printf("min = %d\n", res);
	read(sum_pipe, &res, sizeof(int));
	printf("sum = %d\n", res);
	read(mul_pipe, &res, sizeof(int));
	printf("mul = %d\n", res);
	
	getchar();
	return 0;
}
