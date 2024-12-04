#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void init_q(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int is_empty(Queue* q) {
    return q->front == -1;
}

int is_full(Queue* q) {
    return q->rear == MAX_SIZE - 1;
}

void enqueue(Queue* q, int value) {
    if (is_full(q)) {
        printf("Queue is full, cannot add %d.\n", value);
        return;
    }

    if (is_empty(q)) {
        q->front = 0;
    }

    q->rear++;
    q->items[q->rear] = value;
    printf("%d added to queue.\n", value);
}

int dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty, cannot dequeue.\n");
        return -1;
    }

    int value = q->items[q->front];
    if (q->front == q->rear) {
        // Reset queue when it becomes empty
        q->front = q->rear = -1;
    } else {
        q->front++;
    }

    printf("%d removed from the queue.\n", value);
    return value;
}

int peek(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty, nothing to show.\n");
        return -1;
    }

    return q->items[q->front];
}

int size(Queue* q) {
    if (is_empty(q)) {
        return 0;
    }
    return q->rear - q->front + 1;
}

void print_q(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty, nothing to show.\n");
        return;
    }

    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

