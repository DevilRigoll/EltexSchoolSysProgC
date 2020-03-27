#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {
	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-m")) {
			pid_t pid = fork();
			if (pid == 0) {
				execl("./fork", "fork", argv[i], argv[i + 1], argv[i + 2], NULL);
				exit(0);
			}
			i += 2;		
		}
		else if (!strcmp(argv[i], "-s")) {
			pid_t pid = fork();
			if (pid == 0) {
				execl("./fork", "fork", argv[i], argv[i + 1], NULL);
				exit(0);
			}	
			i++;
		}
		else if (!strcmp(argv[i], "-a")) {
			pid_t pid = fork();
			if (pid == 0) {
				argv += i - 1;
				execv("./fork", argv);
				exit(0);
			}	
		}
	}
	
		
	getchar();
	return 0;
}
