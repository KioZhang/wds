/* UDP Client*/
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

/* socket
 * connect
 * send/recv	
 */

#define SERVER_PORT 8888

int main(int argc, char * argv [ ])
{
	int iSocketclient;
	struct sockaddr_in tSocketServerAddr;
	int iRet;
	int iSendLen;
	unsigned char ucSendBuf[1000];

	if(argc != 2) {
		printf("Usage:\n");
		printf("%s <server_ip>\n", argv[0]);
		return -1;	
	}
	iSocketclient = socket(AF_INET, SOCK_DGRAM, 0);

	tSocketServerAddr.sin_family		= AF_INET;
	tSocketServerAddr.sin_port			= htons(SERVER_PORT);	/* host to net*/
	//tSocketServerAddr.sin_addr.s_addr	= INADDR_ANY;
	if (0 ==inet_aton(argv[1], &tSocketServerAddr.sin_addr)) {
		printf("invalid server_ip!\n");
		return -1;
	}
	memset(tSocketServerAddr.sin_zero, 0, 8);

/* 可以不用连接      直接用sendto函数发送 */
	iRet = connect(iSocketclient, (const struct sockaddr *) &tSocketServerAddr, sizeof(struct sockaddr));
	if (-1 == iRet) {
		printf("connect error!\n");
		return -1;
	}

	while (1) {
		if (fgets(ucSendBuf, 999, stdin)) {
			iSendLen = send(iSocketclient, ucSendBuf, strlen(ucSendBuf), 0);
			if (iSendLen <= 0) {
				close(iSocketclient);
				return -1;
			}
				
		}
	}
	
	return 0;
}
