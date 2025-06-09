#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpt_queue.h"

void initQueue(GPTQueue* q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

int enqueue(GPTQueue* q, const char* prompt) {
    if (q->count == MAX_GPT_QUEUE) return 0;

    strncpy(q->queue[q->rear].prompt, prompt, MAX_PROMPT_LEN);
    q->queue[q->rear].handled = 0;
    q->queue[q->rear].response[0] = '\0';

    q->rear = (q->rear + 1) % MAX_GPT_QUEUE;
    q->count++;
    return 1;
}

GPTRequest* dequeue(GPTQueue* q) {
    if (q->count == 0) return NULL;

    GPTRequest* req = &q->queue[q->front];
    q->front = (q->front + 1) % MAX_GPT_QUEUE;
    q->count--;
    return req;
}

int isEmpty(GPTQueue* q) {
    return q->count == 0;
}