/* wait.c */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	printf("Program Start!\n");

	pid_t pc, pr;
	pc = fork();	/* 创建新子进程 */

	if (pc < 0) {
		printf("Error, Fork!\n");
	} else if (0 == pc) { 	/* 子进程 */
		/* 子进程暂停5s */
		printf("I'm the child process. I'm going sleep!\n");
		sleep(5);
		/* 子进程正常退出 */	
		printf("I'm the child process. I'm going exit!\n");
		exit(0);
	} else {	/* 父进程 */
		pr = wait(NULL);
		if (pr < 0) {
			printf("Some Error Occured!\n");
		}
		printf("I'm the father process. I get child exit code:%d\n", pr);
	}

	exit(0);
}