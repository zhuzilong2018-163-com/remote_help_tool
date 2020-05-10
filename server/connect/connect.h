#ifndef _CONNECT_H
#define _CONNECT_H

#ifdef __cplusplus 
extern "C" { 
#endif

#include <time.h>
#include <stdbool.h>
#include <netinet/in.h> 
#include "protocol.h"

#define MAX_SESSION_NUM 32

typedef struct {
	int sockFd;
	unsigned short int port;
} SERVE_SOCKET;

typedef struct {
	char clientGetIp[IP_LEN];
	char clientPutIp[IP_LEN];
	char key[ID_CODE_LEN];
	unsigned int sessionId;
	time_t terminalTime;
	bool sessionStatus;
} CLIENT_QUEUE;


int connectInit(unsigned short int port);
int waitAuthRequest(struct sockaddr_in * clientAddr);
int processClientRequest(int sockFd,struct sockaddr_in *clientAddr);
bool findConnectOfQueue(unsigned int sessionId, CLIENT_QUEUE *conectInfo);
int removeConnectToQueue(unsigned int sessionId);
bool addConnectToQueue(CLIENT_QUEUE *info, E_CLIENT_TYPE type);


#ifdef __cplusplus 
}
#endif

#endif
