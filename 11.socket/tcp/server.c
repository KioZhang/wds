#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

/* socket
 * bind
 * listen
 * accept
 * send/recv
 */

#define SERVER_PORT 8888
#define BACKLOG 10

int main(int argc, char *argv[])
{
	int iSocketServer;
	int iSocketClient;
	int iRet;
	int iAddrLen;
	struct sockaddr_in tSocketServerAddr;
	struct sockaddr_in tSocketClientAddr;
	int iRecvLen;
	unsigned char ucRecvBuf[1000];

	int iClientNum = -1;
	
	signal(SIGCHLD, SIG_IGN);	/* 	清理僵尸子进程 */
	
	iSocketServer = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == iSocketServer) {
		printf("socket error!");
		return -1;
	}

	tSocketServerAddr.sin_family 		= AF_INET;
	tSocketServerAddr.sin_port 			= htons(SERVER_PORT);	/* host to net*/
	tSocketServerAddr.sin_addr.s_addr	= INADDR_ANY;
	memset(tSocketServerAddr.sin_zero, 0, 8);
	
	iRet = bind(iSocketServer, (const struct sockaddr *) &tSocketServerAddr, sizeof(struct sockaddr)); 
	if (-1 == iRet) {
		printf("bind error!");
		return -1;
	}

	iRet = listen(iSocketServer,BACKLOG);
	if (-1 == iRet) {
		printf("listen error!");
		return -1;
	}

	while (1) {
		iAddrLen = sizeof(struct sockaddr);
		iSocketClient = accept(iSocketServer, (struct sockaddr *) &tSocketClientAddr, &iAddrLen);
	
		if (-1 != iSocketClient) {
			iClientNum++;
			printf("Get connect from client%d : %s\n", iClientNum, inet_ntoa(tSocketClientAddr.sin_addr));
			
			if (!fork()) {
				
				/* 子进程代码 */
				while (1) {
					/* 接受客户端发送来的数据并显示出来 */
					iRecvLen = recv(iSocketClient, ucRecvBuf, 999, 0);
					
					if (iRecvLen <= 0) {
						close(iSocketClient);
						return -1;
					} else {
						ucRecvBuf[iRecvLen] = '\0';
						printf("Get Msg From Client %d: %s\n", iSocketClient, ucRecvBuf);
					}	
				}
			}
		}	
	}

	close(iSocketServer);	
	return 0;
}
