#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void print_reverse(char * str, pid_t pid) {
	for (int i = 0; i < strlen(str) / 2; ++i) {
		char c = str[i];
		str[i] = str[strlen(str) - 1 - i];
		str[strlen(str) - 1 - i] = c;	
	}		
	printf("pid=%d : %s\n",pid, str);
}


int main(int argc, char * argv[]) {

	for (int i = 1; i < argc; ++i) {
		pid_t pid = fork();
		if (pid == 0) {
			print_reverse(argv[i], pid);
			exit(0);
		}
		else if ( pid < 0)
			fprintf(stderr, "Can't create a child proc!!!\n");
			
	}
	getchar();
	return 0;
}
