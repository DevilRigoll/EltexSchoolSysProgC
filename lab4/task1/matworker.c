#include "matworker.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
