/*
	Made by Caio and Zimmer - 2020
*/

#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define START_CAPACITY 6

struct queue {
	int len;
	int capacity;
	int head;
	int tail;
	void *elems[];
};

Queue QUEUE_create() {
	Queue q = malloc(sizeof(struct queue) + sizeof(void *) * START_CAPACITY);
	q->len = 0;
	q->capacity = START_CAPACITY;
	q->head = 0;
	q->tail = q->capacity - 1;

	return q;
}

Queue QUEUE_push(Queue q, void *elem) {
	if (q->capacity == q->len) {

		Queue temp = malloc(sizeof(struct queue) + sizeof(void *) * (q->capacity<<1));

		int offset = q->capacity - q->head;
		memcpy(temp->elems, q->elems + q->head, offset * sizeof(void *));
		memcpy(temp->elems + offset, q->elems, ((q->tail + 1)%q->capacity) * sizeof(void *));

		temp->capacity = q->capacity<<1; // capacity *= 2
		temp->len = q->len;
		temp->head = 0;
		temp->tail = temp->len-1;

		Queue freeTemp = q;
		q = temp;
		free(freeTemp);
	}

	q->tail = (q->tail + 1)%(q->capacity);
	q->elems[q->tail] = elem;
	q->len++;

	return q;
}

void *QUEUE_pop(Queue q) {
	if (q->len == 0) {
		return NULL;
	} 

	void *elem = q->elems[q->head];
	q->head = (q->head + 1)%q->capacity;
	q->len--;

	return elem;
}

void QUEUE_delete(Queue q, void (*deleteFunc) (void *)) {
	for (int i = q->head; i <= q->tail; i++) {
		if (i > q->capacity) {
			i = 0;
		}
		deleteFunc(q->elems[i]);
	}

	free(q);
}

void QUEUE_deleteSimple(void *elem) {

}

void QUEUE_deleteFree(void *elem) {
	free(elem);
}

int QUEUE_len(Queue q) {
	return q->len;
}
