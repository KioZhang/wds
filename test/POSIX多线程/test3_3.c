#include <stdio.h>
#include <pthread.h>

void *threadfunc(void *pvoid)
{
	int id = (int) pvoid;
	printf("Child%d say : Hello World!\n", id);

	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, &threadfunc, 1);
	pthread_create(&tid2, NULL, &threadfunc, 2);
	pthread_detach(tid1);
	pthread_join(tid2, NULL);
	printf("Main thread says: Hello World!\n");

	return 0;
	
}
