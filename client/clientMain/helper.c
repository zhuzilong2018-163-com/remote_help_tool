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
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>

#include "client.h"
#include "helper.h"
#include "logPrint.h"
#include "stdio.h"
#include "protocol.h"
#include "typeinit.h"
#include "aes.h"

//全局变量
uint32 g_sessionId;          //用于通信对话识别
uint8  g_uc_mode_change = 0; //g_uc_mode_change默认为0（为交流模式），1（协助模式）
sem_t  g_sem;                //保证线程收到命令再发送

uint8 buf[5096];



void pthread_message_come(void *argv)
{
    PTHREAD_ARGV st_come_pthread_argcv;
    memcpy(&st_come_pthread_argcv, argv, sizeof(PTHREAD_ARGV));
    while (1) {
        recvfrom(st_come_pthread_argcv.sock, &buf, sizeof(buf), 0, (struct sockaddr *)&(st_come_pthread_argcv.from_adr), &st_come_pthread_argcv.len);
    }
}

void pthread_message_outs(void *argv)
{
    PTHREAD_ARGV st_out_pthread_argcv;
    memcpy(&st_out_pthread_argcv, argv, sizeof(PTHREAD_ARGV));

    while (1) {
        sendto(st_out_pthread_argcv.sock, &buf, sizeof(buf), 0, (struct sockaddr *)&st_out_pthread_argcv.serv_adr, st_out_pthread_argcv.len);
        sem_wait(&g_sem);  //相当于P操作,数据-1
    }
}

void handler(int tmp)
{
    if (g_uc_mode_change == 0) {
        g_uc_mode_change = 1;
    } else if (g_uc_mode_change == 1) {
        g_uc_mode_change = 0;
    }
}


int32 pthread_communicate_encap_message(char *buff, uint8 message_type)
{

    if (message_type == E_COMMUNICATE) {

    } else if (message_type == E_CMD_MODE) {

    }
	sem_post(&g_sem);  //相当于V操作,数据+1

    return SUCCESS;
}


void pthread_communicate(uint32 *argv)
{
    char  ac_read_buff[1024];
    char* c_read_buff = ac_read_buff;

    signal(SIGQUIT, handler);

    while (1) {
        if (fgets(c_read_buff, 1024, stdin) == NULL) {
            ERROR_LOG(HELPER, "%s\n", "fgets error\n");
        }

        if (g_uc_mode_change == E_COMMUNICATE) {
            if (pthread_communicate_encap_message(c_read_buff, E_COMMUNICATE) != SUCCESS) {
                ERROR_LOG(HELPER, "%s, type[%d]\n", "pthread_communicate_encap_message error\n", E_COMMUNICATE);
            } 

        } else if (g_uc_mode_change == E_CMD_MODE) {
            if (pthread_communicate_encap_message(c_read_buff, E_CMD_MODE) != SUCCESS) {
                ERROR_LOG(HELPER, "%s, type[%d]\n", "pthread_communicate_encap_message error\n", E_CMD);
            } 
        }
    }
}


void helper_thread_create(void)
{   
    pthread_t message_come, messge_out, communicate;
    PTHREAD_ARGV st_come_pthread_argcv;
    PTHREAD_ARGV st_out_pthread_argcv;
    PTHREAD_ARGV st_communicate_pthread_argcv;

    //创建UDP
    int32 sock, size;
    struct sockaddr_in serv_adr, from_adr;

	sem_init(&g_sem, 0, 0); //保证命令和交流信息的一收一发

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == FAIL) {
        ERROR_LOG(HELPER, "%s\n", "udp create error\n");
    }

    size = sizeof(struct sockaddr_in);
	bzero(&serv_adr, size);
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_port = htons(SERVER_PORT); //服务器绑定的端口
	serv_adr.sin_addr.s_addr = inet_addr(SERVER_IP);//服务器的IP地址

    //任务线程相关
    st_come_pthread_argcv.sock = sock;
    st_come_pthread_argcv.len  =  size;
    st_come_pthread_argcv.from_adr = from_adr;

    st_out_pthread_argcv.sock = sock;
    st_out_pthread_argcv.len  =  size;
    st_out_pthread_argcv.serv_adr = serv_adr;

    //创建消息接收进程             参数需要
    if (pthread_create(&message_come, NULL, (void *)pthread_message_come, (void *)&st_come_pthread_argcv) != 0) {
        ERROR_LOG(HELPER, "%s\n", "pthread_create message_come error\n");
        exit(1);
    } else {
        sleep(300);
        pthread_detach(message_come);
    }

    //创建消息发送进程
    if (pthread_create(&messge_out, NULL, (void *)pthread_message_outs, (void *)&st_out_pthread_argcv) != 0) {
        ERROR_LOG(HELPER, "%s\n", "pthread_create messge_out error\n");  
        exit(1);
    } else {
        sleep(300);
        pthread_detach(messge_out);
    }

    //创建消息交互进程
    if (pthread_create(&communicate, NULL, (void *)pthread_communicate, (void *)&st_communicate_pthread_argcv) != 0) {
        ERROR_LOG(HELPER, "%s\n", "pthread_create communicate error\n");
        exit(1);
    } else {
        sleep(300);
        pthread_detach(communicate);
    }

    sem_destroy(&g_sem);
}



int32 helper_auth_request_encap( AUTH_HEADER_REQUEST  *auth_header_request, uint32 ul_auth_request_len,uint8 *uc_message_buff)
{
    //认证消息填充与发送
    auth_header_request->connectType = E_CONNECT_RELAY;
    auth_header_request->encryptType = E_ENCYRPT_NULL;
    auth_header_request->clientType = 2;

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
	bzero(&saddr, sizeof(saddr));
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

    helper_thread_create();

    return  0;
}



