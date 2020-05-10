#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include "logPrint.h"
#include "server.h"
#include "connect.h"

bool g_pthreadRunFlag = false;
pthread_t g_taskProcessId = 0;
SERVE_SOCKET g_dataFd;


void *pthreadTaskProcess(void *arg);
int sendToPut(char *data);

int taskProcessInit(unsigned short int port)
{
	int res;
	int b_reuse = 1;

	memset(&g_dataFd, 0, sizeof(g_dataFd));

	g_dataFd.port = port;

	g_dataFd.sockFd = socket(AF_INET, SOCK_DGRAM, 0);
	if (g_dataFd.sockFd < 0) {
	   	SERVE_ERROR("Create server error!");
	   	return -1;
	}

	res = setsockopt(g_dataFd.sockFd, SOL_SOCKET,SO_REUSEADDR,&b_reuse,sizeof(int)); 
	if (res < 0) {
		SERVE_WARN("set data sock reuser error!");
	}
	
	res = pthread_create(&g_taskProcessId, NULL, pthreadTaskProcess, NULL);
	if (res < 0) {
		SERVE_ERROR("create taskProcess pthread error!\n");
		g_pthreadRunFlag = false;
		return -1;
	}
	g_pthreadRunFlag = true;
	return 0;
}

void stopTaskProcess(void)
{
	g_pthreadRunFlag = false;
	pthread_join(g_taskProcessId, NULL);
}

void *pthreadTaskProcess(void *arg)
{
	DATA_TRANSPORT_REQUEST recvHeader;
	struct sockaddr clientAddr;
	socklen_t addrLen;
	char *data;
	int res;

	while (g_pthreadRunFlag) {
		memset(&clientAddr, 0, sizeof(clientAddr));
		res = recvfrom(g_dataFd.sockFd, &recvHeader, recvHeader.data_len, 0, &clientAddr, &addrLen);
		if (res < 0) continue;

		data = (char*)malloc(recvHeader.data_len);
		res = recvfrom(g_dataFd.sockFd, data, recvHeader.data_len, 0, &clientAddr, &addrLen);
		if (res < 0) continue;

		res = sendToPut(data);
		if (res < 0) continue;

		//res = send
	}
	return NULL;
}

int sendToPut(char *data)
{
	return 0;
}
