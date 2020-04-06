#include <stdio.h>
#include <stdlib.h>
#include "msgtypes.h"
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

void regOnServer(int msgqid, char * name) {
	int lmsgqid = msgget(MSGLOGINKEY, MSGPERM);

	if (lmsgqid < 0) {
		perror(strerror(errno));
		printf("failed to create message queue with msgqid = %d\n", lmsgqid);
		exit(1);
	} else 
		printf("message queue %d created\n", lmsgqid);

	struct login_msg l_msg;
	l_msg.type = LOGIN;
	l_msg.msgqid = msgqid;
	strcpy(l_msg.name, name);
	
	int rc = msgsnd(lmsgqid, &l_msg, sizeof(l_msg) - sizeof(long), 0);
	if (rc < 0) {
			perror( strerror(errno) );
			printf("msgsnd reg failed, rc=%d\n", rc);
			exit(1);
	}

}

void sendLoop(int msgqid) {

	while(1) {
		struct msg_buf msg;
		msg.mtype = TO_SERVER;
		scanf("%s", msg.mtext);
		int rc = msgsnd(msgqid, &msg, sizeof(msg) - sizeof(long), 0);
		if (rc < 0) {
			//perror( strerror(errno) );
			//printf("msgsnd failed, rc=%d\n", rc);
			return;
		}	
	}	
}

void * readLoop(void * msgqid) {
	struct msg_buf msg;
	
	int qid = (int)msgqid;

	while(1) {
		int rc = msgrcv(qid, &msg, sizeof(msg) - sizeof(long), TO_CLIENT, IPC_NOWAIT); 
		if (rc < 0) {
			//perror( strerror(errno) );
			//printf("msgrcv failed, rc=%d\n", rc);
		}
		if (rc > 0)
			printf("%s\n", msg.mtext);
		sleep(1);	
	}
	return 0;	
}


int main(int argc, char * argv[]) {
	srand(time(NULL));
	printf("Enter your name:\n");
	char name[NAMELEN];
	scanf("%s", name);

	key_t key = ftok(".", 'm');
	key += rand() % 10000;
	int msgqid = msgget(key, IPC_CREAT|MSGPERM);
	if (msgqid < 0) {
		perror(strerror(errno));
		printf("failed to create message queue with msgqid = %d\n", msgqid);
		exit(1);
	} else 
		printf("message queue %d created\n", msgqid);
	
	regOnServer(key, name);
	
	pthread_t read_thread;
	int status = pthread_create(&read_thread, NULL, readLoop, (void*)msgqid);
	if (status != 0) {
        	printf("main error: can't create thread, status = %d\n", status);
        	exit(1);
    	}

	sendLoop(msgqid);

	return 0;
}
