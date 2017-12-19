#include <stdio.h>
#include <sys/types.h>	/* 提供类型pid_t的定义 */
#include <unistd.h>

int main()
{
	pid_t result;

	/* 调用fork()函数 */
	result = fork();

	/* 通过调用fork函数来判断返回情况，首先处理出错状态 */
	if (-1 == result) {
		printf("Fork Error!\n");
	} else if (0 == result) {
		printf("Child process, result:%d, pid:%d\n", result, getpid());
	} else {
		printf("Father process, result:%d, pid:%d\n", result, getpid());
	}

	return result;
}