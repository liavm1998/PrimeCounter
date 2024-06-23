#include "../include/Queue.h"
#include <stdio.h>
#include <stdlib.h>

QueuePointer queueCreate() {
	QueuePointer queue = (QueuePointer)malloc(sizeof(Queue));

	if (queue == NULL)
	{
		fprintf(stderr, "queueCreate() failed: malloc() failed\n");
		return NULL;
	}

	queue->front = 0;
	queue->rear = -1;
	queue->size = 0;

	if (pthread_mutex_init(&queue->lock, NULL) != 0)
	{
		fprintf(stderr, "queueCreate() failed: pthread_mutex_init() failed\n");
		free(queue);
		return NULL;
	}

	if (pthread_cond_init(&queue->full, NULL) != 0)
	{
		fprintf(stderr, "queueCreate() failed: pthread_cond_init() failed\n");
		MUTEX_DESTROY(&queue->lock);
		free(queue);
		return NULL;
	}

	if (pthread_cond_init(&queue->empty, NULL) != 0)
	{
		fprintf(stderr, "queueCreate() failed: pthread_cond_init() failed\n");
		MUTEX_DESTROY(&queue->lock);
		COND_DESTROY(&queue->full);
		free(queue);
		return NULL;
	}

	return queue;
}

void queueDestroy(QueuePointer queue) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueDestroy() failed: queue is NULL\n");
		return;
	}

	MUTEX_LOCK(&queue->lock);

	MUTEX_DESTROY(&queue->lock);
	COND_DESTROY(&queue->full);
	COND_DESTROY(&queue->empty);

	free(queue);
}

void queueEnqueue(QueuePointer queue, int data) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueEnqueue() failed: queue is NULL\n");
		return;
	}

	MUTEX_LOCK(&queue->lock);

	while (queue->size == QUEUE_MAX_SIZE)
		COND_WAIT(&queue->full, &queue->lock);

	queue->rear = (queue->rear + 1) % QUEUE_MAX_SIZE;
	queue->data[queue->rear] = data;
	queue->size++;

	COND_SIGNAL(&queue->empty);
	MUTEX_UNLOCK(&queue->lock);
}

int queueDequeue(QueuePointer queue) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueDequeue() failed: queue is NULL\n");
		return -1;
	}

	MUTEX_LOCK(&queue->lock);

	while (queue->size == 0)
		COND_WAIT(&queue->empty, &queue->lock);

	int data = queue->data[queue->front];
	queue->front = (queue->front + 1) % QUEUE_MAX_SIZE;
	queue->size--;

	COND_SIGNAL(&queue->full);
	MUTEX_UNLOCK(&queue->lock);

	return data;
}

int queueIsEmpty(QueuePointer queue) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueIsEmpty() failed: queue is NULL\n");
		return -1;
	}

	MUTEX_LOCK(&queue->lock);
	int isEmpty = (queue->size == 0);
	MUTEX_UNLOCK(&queue->lock);

	return isEmpty;
}

