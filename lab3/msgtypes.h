#ifndef __MSGTYPES_H__
#define __MSGTYPES_H__

#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>

#define MSGPERM 0660
#define MSGTXTLEN 1024
#define MSGLOGINKEY 1000
#define NAMELEN 64

enum MSG_TYPE {
	TO_SERVER = 1,
	TO_CLIENT = 2,
	LOGIN = 3	
};

struct msg_buf {
  long mtype;
  char mtext[MSGTXTLEN];
};

struct login_msg {
  long type;
  int msgqid;
  char name[NAMELEN];
};

struct sClient {
	char name[NAMELEN];
	int msgqid;
};

#endif
