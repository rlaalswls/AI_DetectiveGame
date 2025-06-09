#ifndef GPT_QUEUE_H
#define GPT_QUEUE_H

#define MAX_GPT_QUEUE 10
#define MAX_PROMPT_LEN 512
#define MAX_RESPONSE_LEN 1024

typedef struct {
    char prompt[MAX_PROMPT_LEN];
    char response[MAX_RESPONSE_LEN];
    int handled;  // 0: 대기, 1: 응답 처리 완료
} GPTRequest;

typedef struct {
    GPTRequest queue[MAX_GPT_QUEUE];
    int front;
    int rear;
    int count;
} GPTQueue;

void initQueue(GPTQueue* q);
int enqueue(GPTQueue* q, const char* prompt);
GPTRequest* dequeue(GPTQueue* q);
int isEmpty(GPTQueue* q);

#endif