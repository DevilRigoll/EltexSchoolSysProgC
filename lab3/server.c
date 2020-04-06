#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "list.h"
#include "msgtypes.h"


struct list * Clients = NULL;

int createServer() {
	int msgqid = msgget(MSGLOGINKEY, MSGPERM|IPC_CREAT);
	if (msgqid < 0) {
		perror(strerror(errno));	
		printf("failed to create message queue with msgqid = %d\n", msgqid);
		exit(1);
	}
	else 
		printf("message queue %d created\n", msgqid);

	return msgqid;
}

void regClient(int msgqid) {
	static struct list * currCl = NULL;
	struct login_msg l_msg;
	struct sClient cl;
	int rc = msgrcv(msgqid, &l_msg, sizeof(l_msg) - sizeof(long), LOGIN, IPC_NOWAIT); 
	if (rc < 0) {
	//	perror( strerror(errno) );
	//	printf("msgrcv failed, rc=%d\n", rc);
		return;
	}
	
	cl.msgqid = msgget(l_msg.msgqid, 0660 );
	
	printf("login: %d %s\n", cl.msgqid, l_msg.name);
	//fflush(stdout);
	if (cl.msgqid < 0) {
		perror( strerror(errno) );
		printf("msgrcv failed, rc=%d\n", rc);
		return;
	}	

	strcpy(cl.name, l_msg.name);

	if (currCl == NULL) {
		Clients = listinit(cl);
		currCl = Clients;
		return;
	}

	currCl = addelem(currCl, cl);
}

char * readMsg(struct sClient cl) {
	struct msg_buf msg;
	int rc = msgrcv(cl.msgqid, &msg, sizeof(msg) - sizeof(long), TO_SERVER, IPC_NOWAIT); 
	if (rc < 0) {
		//perror( strerror(errno) );
		//printf("msgrcv failed, rc=%d\n", rc);
		return NULL;
	}

	char * str = (char *)malloc(sizeof(char) * (strlen(msg.mtext)));
	strcpy(str, msg.mtext);
	return str;	
}

void writeMsg(const char * text, struct sClient scl) {
	struct msg_buf msg;
	msg.mtype = TO_CLIENT;
	strcpy(msg.mtext, scl.name);
	strcat(msg.mtext, " >> ");
	strcat(msg.mtext, text);
	for (struct list * cl = Clients; cl != NULL; cl = cl->next) {
		if (!strcmp(cl->field.name, scl.name))
			continue;

		int rc = msgsnd(cl->field.msgqid, &msg, sizeof(msg) - sizeof(long), 0);
		if (rc < 0) {
			//perror( strerror(errno) );
			//printf("msgsnd reg failed, rc=%d\n", rc);
			return;
		}
	}
}

void mainLoop(int msgqid) {
	while(1) {
		regClient(msgqid);
		for (struct list * cl = Clients; cl != NULL; cl = cl->next) {
			struct msg_buf msg;
			int rc = msgrcv(cl->field.msgqid, &msg, sizeof(msg) - sizeof(long), TO_SERVER, IPC_NOWAIT);
			if (rc > 0) {
				printf("%s\n", msg.mtext);
				writeMsg(msg.mtext, cl->field);
			}
			
		}		
	}
}

void closeServer(int msgqid) {
	int rc;
	for (; Clients != NULL ; Clients = deletehead(Clients)) {
		rc = msgctl(Clients->field.msgqid ,IPC_RMID, NULL);
  		if (rc < 0) {
    			perror( strerror(errno) );
    			printf("msgctl (return queue) failed, rc=%d\n", rc);
  		}
	}
	rc = msgctl(msgqid,IPC_RMID,NULL);
  	if (rc < 0) {
    		perror( strerror(errno) );
    		printf("msgctl (return queue) failed, rc=%d\n", rc);
    		return;
  	}	
}


int main(int argc, char * argv[]) {
	int msgqid = createServer();
	mainLoop(msgqid);
	closeServer(msgqid);
	return 0;
}
