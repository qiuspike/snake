#include <stdio.h>
#include <stdlib.h>
#include "snake.h"


void
init_queue(queue Q)
{
	Q->front = NULL;
	Q->rear = NULL;
}

void
destroy_queue(queue Q)
{
	while (Q->front) {
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
}

int
is_exist(position X, queue Q)
{
	ptr_snake s;

	s = Q->front; // TODO
	while (s->next != NULL) {
		if (s->pos.x == X.x && s->pos.y == X.y)
			return 1;
		else
			s = s->next;
	}

	return 0;
}

position	// TODO
get_front(queue Q)
{
	return Q->front->pos;
}

void
front_enqueue(position X, queue Q)
{
	ptr_snake tmp;

	tmp = (ptr_snake)malloc(sizeof(struct snake));
	if (tmp == NULL)
		fatal_error("Out of space!");

	if (Q->front == NULL) {		//Enqueue the first element
		tmp->pos = X;
		tmp->next = NULL;
		tmp->pre = NULL;
		Q->front = tmp;
		Q->rear = tmp;
	} else {				//Enqueue other element
		tmp->pos = X;
		tmp->next = Q->front;
		Q->front->pre = tmp;
		tmp->pre = NULL;
		Q->front = tmp;
	}
}

position
rear_dequeue(queue Q)
{
	ptr_snake tmp;
	position p;

	if (Q->rear == NULL)				 //Empty queue
		error("Empty queue!");
	else if (Q->rear == Q->front) {	//Only one element in the queue. //OK?
		tmp = Q->rear;
		p = tmp->pos;
		Q->front = NULL;
		Q->rear = NULL;
		free(tmp);
	} else {
		tmp = Q->rear->pre;	//tmp point to the one before rear
		tmp->next = NULL;
		p = Q->rear->pos;
		free(Q->rear);
		Q->rear = tmp;
	}

	return p;
}

// For error handling
// TODO The error info should be writen to file as the journal.
void
fatal_error(const char s[])
{
	fprintf(stderr, "Fatal errors: %s\n", s);
	exit(-1);
}

void
error(const char s[])
{
	fprintf(stderr, "errors: %s\n", s);
	exit(0);
}
// End
