#include <stdio.h>

#include "queue.h"

#define ITER 400

int main() {

	Queue q = QUEUE_create();

	for (int i = 0; i < ITER; i++) {
		q = QUEUE_push(q, (void *) (long) ((i+1)*5));

		if (i%2 == 0) {
			printf("%d\n", (int) (long) QUEUE_pop(q));
			printf("%d\n", (int) (long) QUEUE_pop(q));
		}
	}

	for (int i = 0; QUEUE_len(q); i++) {
		printf("%d\n", (int) (long) QUEUE_pop(q));
	}

	return 0;
}
