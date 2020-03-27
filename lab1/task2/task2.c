#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void wait_proc() {
	int status;
	if (wait(&status) == -1)
		perror("wait() error\n");
	else if (WIFEXITED(status))
		printf("%d\n", WEXITSTATUS(status));
	else 
		perror("Child isn't finished successful\n");
}

int main(int argc, char * argv[]) {
	printf("pid = %d ppid = %d \n", getpid(), getppid());
	pid_t pid = fork();
	if (pid == 0) {
		printf("pid = %d ppid = %d \n", getpid(), getppid());
		for (int i = 0; i < 3; ++i) {
			pid_t m_pid = fork();
			if (m_pid == 0) {
				printf("pid = %d ppid = %d \n", getpid(), getppid());
				exit(i*3);	
			}
			else
				wait_proc();
		}
		exit(10);
	}
	else
		wait_proc();
	
	pid = fork();
	if (pid == 0) {
		printf("pid = %d ppid = %d \n", getpid(), getppid());
		for (int i = 0; i < 2; ++i) {
			pid_t m_pid = fork();
			if (m_pid == 0) {
				printf("pid = %d ppid = %d \n", getpid(), getppid());
				exit((i + 1) * 2);	
			}
			else
				wait_proc();
		}
		exit(20);
	}
	else
		wait_proc();
	
	
	getchar();
	return 0;
}
