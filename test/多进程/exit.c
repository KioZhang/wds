#include <stdio.h>
#include <sys/types.h>	/* 提供类型pid_t的定义 */
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argcv[])
{
	pid_t result;
	printf("Program Start!\n");

	/* 调用fork()函数 */
	result = fork();

	/* 通过调用fork函数来判断返回情况，首先处理出错状态 */
	if (-1 == result) {
		printf("Fork Error!\n");
	} else if (0 == result) {
		printf("\nChild process, result:%d, pid:%d\n", result, getpid());
		printf("\nUsing _exit...\n");
		printf("\nThis is the content in buffer");
		_exit(0);
	} else {
		printf("\nFather process, result:%d, pid:%d\n", result, getpid());
		printf("\nUsing exit...\n");
		printf("\nThis is the content in buffer");
	}

	exit(0);
}