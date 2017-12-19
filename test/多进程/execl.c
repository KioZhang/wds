#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argcv[])
{
	int ret;
	printf("Program Start!\n");
	if (0 == fork()) {	/* 在新建的子进程中执行新的程序 */
		
		/* 调用ececl()函数， 这里相当于调用了“ps -ef命令” */
		ret = execlp("/bin/ps", "ps", "-ef", NULL);
		if (ret < 0) {
			printf("Execlp Error!\n");
		}
	}

	return 0;
}