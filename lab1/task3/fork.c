#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int comp(const float * i, const float * j) {
	if (*i > *j) return 1;
	if (*i < *j) return -1;
	return 0;
}

void cmd_exec(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-m")) {
			int n = atoi(argv[i + 1]);
			int m = atoi(argv[i + 2]);

			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < m; ++k)
					printf("0 ");
				printf("\n");
			}

			i += 2; 
		}
		else if (!strcmp(argv[i], "-s")) {
			printf("%s\n", argv[i + 1]);
			i++;
		}
		else if (!strcmp(argv[i], "-a")) {
			int n = atoi(argv[i + 1]);
			i += 2;
			float * arr = (float *)malloc(n * sizeof(float));
			for (int j = 0; j < n; ++j, ++i)
				arr[j] = atof(argv[i]);
			qsort(arr, n, sizeof (float), (int(*) (const void *, const void *)) comp);
			for (int j = 0; j < n; ++j)
				printf("%f ", arr[j]);
			free(arr);	
		}
	}
}


int main(int argc, char * argv[]) {
	
	if (argc < 2)
		return 0;
	else {
		cmd_exec(argc, argv);
	}
	return 0;
}
