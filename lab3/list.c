#include "list.h"

struct list * listinit(struct sClient field) {
	struct list * lst;
	lst = (struct list*)malloc(sizeof(struct list));
	lst->field = field;
	lst->next = NULL;
	lst->prev = NULL;
	return(lst);
}

struct list * addelem(struct list *lst, struct sClient elem) {		
	struct list * curr = (struct list*)malloc(sizeof(struct list));
	curr->field = elem;
	curr->prev = lst;
	curr->next = lst->next;
	lst->next = curr;
	return curr; 
	
}

struct list * deletehead(struct list * root) {
	struct list *temp;
	temp = root->next;
	if (temp != NULL)
		temp->prev = NULL;
	free(root);   
	return(temp); 
}

