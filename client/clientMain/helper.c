#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "client.h"
#include "helper.h"
#include "logPrint.h"
#include "stdio.h"
#include "protocol.h"
#include "typeinit.h"
#include "aes.h"

//全局变量
uint32 g_sessionId; //用于通信对话识别

//开始创建put和get进程
int32 helper_enter_cmd(void)
{
    return 0;
}

int32 helper_enter_communicate(void)
{
    return 0;
}

int32 helper_choose_mode(void)
{
    return 0;
}


int32 helper_auth_request_encap( AUTH_HEADER_REQUEST  *auth_header_request, uint32 ul_auth_request_len,uint8 *uc_message_buff)
{
    //对key进行加密
 	ScheduleKey((uint8 *)KEY, g_auc_expansionkey, 4, 10);	//1、密钥扩展生成
	AesEncrypt(g_auc_pt, g_auc_expansionkey, 10);		//2、AES 加密

    //认证消息填充与发送
    auth_header_request->connectType = E_CONNECT_RELAY;
    auth_header_request->encryptType = E_ENCYRPT_NULL;
    auth_header_request->clientType = 2;
    if (memcpy(auth_header_request->key, g_auc_pt, sizeof(g_auc_pt)) == NULL) {
        ERROR_LOG(HELPER, "%s\n", "helper_mode_start memcopy1 error\n");
        return FAIL;
    }

    if (memcpy(uc_message_buff, (uint8 *)auth_header_request, ul_auth_request_len)) {
        uc_message_buff[ul_auth_request_len] = '\n';
    } else {
        ERROR_LOG(HELPER, "%s\n", "helper_mode_start memcopy1 error\n");
        return FAIL;
    }

    return SUCCESS;
}

int32 helper_mode_start(void)
{
    int32 l_res = -1;
	int32 sockfd, size;    
    uint8 uc_message_buff[1024];
    uint32 ul_auth_request_len = 0;
	struct sockaddr_in saddr;

    AUTH_HEADER_REQUEST  *auth_header_request;
    AUTH_HEADER_RESPONSE *auth_header_response;

    system(CREAT_PROCESS_MONITOR); //创建新的窗口，并在新的窗口运行monitor进程

	ul_auth_request_len = sizeof(AUTH_HEADER_REQUEST);
    auth_header_request = (AUTH_HEADER_REQUEST  *)malloc(ul_auth_request_len);

    size = sizeof(struct sockaddr_in);
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(SERVER_PORT); //服务器绑定的端口
	saddr.sin_addr.s_addr = inet_addr(SERVER_IP);//服务器的IP地址

	sockfd = socket(AF_INET, SOCK_STREAM, 0); //创建一个套接字用于连接服务器，并且这个套接字可用作对服务器操作的文件描述符。
	if (sockfd == FAIL) {
       ERROR_LOG(HELPER, "%s\n", "Create socked error\n");
       free(auth_header_request);
       return  sockfd;
    }

	l_res = connect(sockfd, (struct sockaddr*)&saddr, size);
    if (l_res == FAIL) {
        ERROR_LOG(HELPER, "%s\n", "Connect error\n");
        ERROR_LOG(HELPER, "%d %s\n", errno, strerror(errno));
        free(auth_header_request);
        return l_res;
    }

    l_res = helper_auth_request_encap(auth_header_request, ul_auth_request_len, uc_message_buff);
    if (l_res != SUCCESS) {
        ERROR_LOG(HELPER, "%s\n", "helper_auth_encap error\n");
        free(auth_header_request);
        return FAIL;
    }
    

	l_res = write(sockfd, uc_message_buff, sizeof(uc_message_buff));
    if (l_res < 0) {
        ERROR_LOG(HELPER, "%s\n", "write fail!!!\n");
        free(auth_header_request);
        return FAIL;
    }

    //认证响应
    memset(uc_message_buff, 0, sizeof(uc_message_buff));
    l_res = read(sockfd, uc_message_buff, 1024); //这里需要确定怎么读取服务器过来的内容
    if (l_res < 0) {
        ERROR_LOG(HELPER, "%s\n", "read fail!!!\n");
    }
    auth_header_response = (AUTH_HEADER_RESPONSE  *)uc_message_buff;

    for (int i = 0; i < sizeof(AUTH_HEADER_RESPONSE); i++) {
        printf("%d\n", uc_message_buff[i]);
    }

    if (auth_header_response->result == 1) {
        g_sessionId = auth_header_response->sessionId;
        INFO_LOG(HELPER, "%s\n", "auth success!!!\n");
    } else {
        ERROR_LOG(HELPER, "%s\n", "auth fail!!!\n");
    }

    //申请的内存的释放
    free(auth_header_request);

    //helper_thread_creat();

    return  0;
}



