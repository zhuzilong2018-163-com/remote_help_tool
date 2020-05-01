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
#include "aes.h"

int32 helper_mode_start(void)
{
    int32 l_res;
	int32 sockfd, size;
    int32 l_write_len;
    uint8 uc_read_buff[1024];
	struct sockaddr_in saddr;

    system(CREAT_PROCESS_MONITOR); //创建新的窗口，并在新的窗口运行monitor进程
    
    AUTH_HEADER_REQUEST  auth_header_request;
	size = sizeof(struct sockaddr_in);
 
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(SERVER_PORT); //服务器绑定的端口
	saddr.sin_addr.s_addr = inet_addr(SERVER_IP);//服务器的IP地址
 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //创建一个套接字用于连接服务器，并且这个套接字可用作对服务器操作的文件描述符。
	if (sockfd == -1) {
       ERROR_LOG(HELPER, "%s\n", "Create socked error\n");
       return  sockfd;
    }
	l_res = connect(sockfd, (struct sockaddr*)&saddr, size);
    if (l_res == -1) {
        ERROR_LOG(HELPER, "%s\n", "Connect error\n");
        return l_res;
    }

    //对key进行加密
	ScheduleKey((uint8 *)KEY, g_auc_expansionkey, 4, 10);	//1、密钥扩展生成
	AesEncrypt(g_auc_pt, g_auc_expansionkey, 10);		//2、AES 加密

    auth_header_request.connectType = E_CONNECT_RELAY;
    auth_header_request.encryptType = E_ENCYRPT_NULL;
    auth_header_request.clientType = E_CLIENT_GET;
    if (memcpy(&auth_header_request.key, g_auc_pt, sizeof(g_auc_pt)) == NULL) {
        ERROR_LOG(HELPER, "%s\n", "helper_mode_start memcopy error\n");
    }

	l_write_len = write(sockfd, (uint8 *)&auth_header_request, sizeof(AUTH_HEADER_REQUEST));
    if (l_write_len) {
        INFO_LOG(HELPER, "%s\n", "Auth start!!!\n");
    } else {
        ERROR_LOG(HELPER, "%s\n", "Auth fail!!!\n");
    }

    read(sockfd, uc_read_buff, 1024); //这里需要确定怎么读取服务器过来的内容
    return  0;

}

//开始创建put和get进程
int32 helper_thread_creat(void)
{
    return 0;
}

