#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>


#define LEN 100
pthread_key_t key;

void A(char *s)
{
	char *str = (char *)pthread_getspecific(key);
	strncpy(str, s, LEN);
}

void B(void)
{
	char *str = (char *)pthread_getspecific(key);
	printf("%s\n", str);
}

void destructor(void *ptr)
{
	free(ptr);
	printf("memory freed\n");
}

void *threadfunc1(void *pvoid)
{
	pthread_setspecific(key, malloc(LEN));
	A("Thread1");
	B();
}

void *threadfunc2(void *pvoid)
{
	pthread_setspecific(key, malloc(LEN));
	A("Thread2");
	B();
}
int main(int argc, char *argv[])
{
	pthread_t tid1, tid2;

	pthread_key_create(&key, destructor);
	pthread_create(&tid1, NULL, &threadfunc1, NULL);
	pthread_create(&tid2, NULL, &threadfunc2, NULL);
	pthread_exit(NULL);

	return 0;
}
