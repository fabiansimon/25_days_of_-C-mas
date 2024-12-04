#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 100

typedef struct Queue {
    int items[MAX_SIZE];
    int front, rear;
} Queue;

void init_q(Queue *q);

int is_empty(Queue *q);

int is_full(Queue *q);

void enqueue(Queue *q, int value);

int dequeue(Queue *q);

int peek(Queue *q);

int size(Queue *q);

void print_q(Queue *q);

#endif