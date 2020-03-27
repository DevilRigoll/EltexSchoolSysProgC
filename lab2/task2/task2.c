#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LENGTH 1024
#define FIFOPIPE "/tmp/fifopipe"


int main(int argc, char * argv[]) {
	if (argc < 2)
		exit(1);

	char buff[MAX_LENGTH + 1] = "";
	int readfd, writefd;
	ssize_t len;
	mkfifo(FIFOPIPE, 0666);
	if (!strcmp(argv[1], "-r")) {
		printf("Write the text!\n");
		printf("If you write '-q' you finish writting and reading!\n");
		writefd = open(FIFOPIPE, O_WRONLY, 0);
		while(strcmp(buff, "-q") != 0) {
			scanf("%s", buff);
			len = strlen(buff);
			write(writefd, buff, len);
		}
		close(writefd);		
	} 
	else if (!strcmp(argv[1], "-w")) {
		printf("Read the text!\n");
		readfd = open(FIFOPIPE, O_RDONLY, 0);
		while(1) {
			len = read(readfd, buff, MAX_LENGTH + 1);
			printf("%s\n", buff);
			if (!strncmp(buff, "-q", len))
				break;		
		}
		close(readfd);
	}
	return 0;	
}
