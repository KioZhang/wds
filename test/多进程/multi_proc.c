/* multi_proc.c */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	printf("Program Start!\n");

	pid_t child1, child2, child;

	/* 先创建子进程1 */
	child1 = fork();
	if (-1 == child1) {
		printf("Child1 fork error!\n");
		exit(1);
	} else if (0 == child1) {
		printf("I'm Child1 and I execute 'ls -l'\n");
		if (execlp("ls", "ls", "-l", NULL) < 0) {
			printf("child1 execlp error!\n");
		}
	} else {	
		/* 创建子进程2 */
		child2 = fork();
		if (-1 == child2) {
			printf("child2 fork error!\n");
			exit(1);
		} else if (0 == child2) {
			printf("I'm Child2 and I sleep 5s\n");
			sleep(5);
			printf("I'm Child2 and I exit\n");
			exit(0);
		}

		printf("I'm father process!\n");
		child = waitpid(child1, NULL, 0);	/* 阻塞式等待 */
		if(child == child1) {
			printf("I'm the father process, I get child1 exit code: %d\n",child);
		} else {
			printf("error occured!\n");
		}

		do{
			child = waitpid(child2, NULL, WNOHANG); /* 非阻塞式等待 */
			if (0 == child) {
				printf("I'm the father process, child2 has not exited!\n");
				sleep(1);
			}
		} while (0 == child);
	}

	if (child == child2) {
		printf("I'm the father process, I get child2 exit code: %d\n",child);
	} else {
		printf("error occured\n");
	}

	exit(0);
}