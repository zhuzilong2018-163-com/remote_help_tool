#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "client.h"
#include "helper.h"
#include "logPrint.h"
#include "stdio.h"
#include "protocol.h"
#include "typeinit.h"

int32 helper_mode_start(void)
{
    int32 l_res;
	int32 sockfd,size;
	struct sockaddr_in saddr;
    AUTH_HEADER_REQUEST  auth_header_request;
	size = sizeof(struct sockaddr_in);
 
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(SERVER_PORT); //服务器绑定的端口
	saddr.sin_addr.s_addr = inet_addr(SERVER_IP);//服务器的IP地址
 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //创建一个套接字用于连接服务器，并且这个套接字可用作对服务器操作的文件描述符。
	if (sockfd == -1) {
       return  sockfd;
    }
	l_res = connect(sockfd, (struct sockaddr*)&saddr, size);
    if (l_res == -1) {
        return l_res;
    }

    auth_header_request.connectType = E_CONNECT_RELAT;
    auth_header_request.encryptType = E_ENCYRPT_NULL;
    auth_header_request.clientType = E_CLIENT_GET;
    auth_header_request.commType = 2;

	write(sockfd, (uint8 *)&auth_header_request, sizeof(AUTH_HEADER_REQUEST));

    return  0;

}

