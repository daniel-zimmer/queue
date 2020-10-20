/*
	Made by Caio and Zimmer - 2020
*/

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue * Queue;

Queue QUEUE_create();

Queue QUEUE_push(Queue q, void *elem);

void *QUEUE_pop(Queue q);

void QUEUE_delete(Queue q, void (*deleteFunc) (void *));

void QUEUE_deleteFree(void *elem);

int QUEUE_len(Queue q);

int QUEUE_cap(Queue q);

#endif // QUEUE_Hz