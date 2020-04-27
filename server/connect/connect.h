#ifndef _CONNECT_H
#define _CONNECT_H

#ifdef __cplusplus 
extern "C" { 
#endif

#include <time.h>
#include <stdbool.h>
#include <netinet/in.h> 
#include "protocol.h"

#define MAX_CLIENT_NUM

typedef struct {
	int authFd;
	int dataFd;
	unsigned short int port;
} SERVE_SOCKET;

typedef struct {
	char clientGetIp[IP_LEN];
	char clientPutIp[IP_LEN];
	time_t terminalTime;
	bool sessionStatus;
} CLIENT_QUEUE;

int connectInit(unsigned short int port);
int waitAuthRequest(struct sockaddr_in * clientAddr);



#ifdef __cplusplus 
}
#endif

#endif
