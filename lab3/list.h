#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <sys/types.h>
#include "msgtypes.h"

struct list {
	struct sClient field; 
	struct list * next; 
	struct list * prev;
};

struct list * listinit(struct sClient cl);
struct list * addelem(struct list *lst, struct sClient cl);
struct list * deletehead(struct list * root);

#endif
