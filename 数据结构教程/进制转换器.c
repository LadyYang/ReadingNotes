#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERROR -2
#define VAR_IS_NULL -1
#define STACK_SPACK_FULL -3
#define QUEUE_SPACK_FULL -4
#define QUEUE_SIZE 1024
#define STACK_SIZE 1024

// 顺序栈 顺序队列
typedef struct Queue {
	int data[QUEUE_SIZE];
	int head;
	int tail;
}Queue;

typedef struct Stack {
	int data[STACK_SIZE];
	int top;
}Stack;

int queue_init(Queue * q /* in */) {
	if (q == NULL)
		return VAR_IS_NULL;

	if (q->data == NULL)
		return MALLOC_ERROR;

	q->tail = 0 ;
	q->head = 0;

	return 0;
}

int queue_push(Queue *q, int x) {
	if ((q->tail - q->head) == QUEUE_SIZE) {
		return QUEUE_SPACK_FULL;
	}


	


	return 0;
}

int queue_pop(Queue *q) {

	return 0;
}


int main() {

	Queue *q = (Queue*)malloc(sizeof(Queue));

	if (queue_init(NULL) == VAR_IS_NULL ){

}

	//printf("%d\n", a);

	system("pause");
	return 0;
}