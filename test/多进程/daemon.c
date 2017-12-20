/* daemon.c 创建守护进程 */
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	printf("Program Start!\n");

	pid_t pid;
	int i, fd, MAXFILE;
	char *buf = "	This is Daemon Program\n";
	time_t timep;

	pid = fork();	/* 子进程创建 step1 */
	if (pid < 0) {
		printf("Daemon fork error!\n");
		exit(1);
	} else if (pid > 0) {	/* 父进程退出 */
		exit(0);
	}

	setsid();	/* 创建新会话组 step 2 */
	chdir("/");	/* 设置工作目录 step 3 */
	umask(0);	/* 设置文件权限掩码 step 4 */
	MAXFILE = getdtablesize();
	for (i = 0; i < MAXFILE; i++) {	/* 关闭文件描述符 step5 */
		close(i);
	}

	/* 守护进程工作内容 */
	while (1) {
		fd = open("/tmp/daemon.log", O_CREAT|O_WRONLY|O_APPEND, 0600);
		if (fd < 0) {
			printf("Open file error!\n");
			exit(1);
		}
		time(&timep);
		write(fd, ctime(&timep), strlen(ctime(&timep)) + 1);
		write(fd, buf, strlen(buf) + 1);
		close(fd);
		sleep(10);
	}

	exit(0);	/* 守护进程正常退出 */
}