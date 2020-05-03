#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include "server.h"
#include "logPrint.h"
#include "connect.h"

SERVE_SOCKET g_serverListenFd = {
	.authFd = -1,
	.dataFd = -1,
	.port = 0,
};

CLIENT_QUEUE g_connecQueue[MAX_SESSION_NUM];
pthread_mutex_t g_connecQueueLock = PTHREAD_MUTEX_INITIALIZER;
int connectInit(unsigned short int port)
{
	int listenFd = -1;
	int res;
	socklen_t len;
	struct sockaddr_in server;
	int b_reuse = 1;

	do {

		memset(g_connecQueue, 0, sizeof(g_connecQueue));

		g_serverListenFd.port = port;
	
		g_serverListenFd.authFd = socket(AF_INET, SOCK_STREAM, 0);
		if (g_serverListenFd.authFd < 0) {
	    	SERVE_ERROR("Create server auth listen error!");
	    	break;
		}

		res = setsockopt(g_serverListenFd.authFd,SOL_SOCKET,SO_REUSEADDR,&b_reuse,sizeof(int));
		if (res < 0) {
			SERVE_WARN("set auth sock reuser error!");
		}

		listenFd = g_serverListenFd.authFd;
		
		g_serverListenFd.dataFd = socket(AF_INET, SOCK_DGRAM, 0);
		if (g_serverListenFd.authFd < 0) {
	    	SERVE_ERROR("Create server error!");
	    	break;
		}

		res = setsockopt(g_serverListenFd.dataFd,SOL_SOCKET,SO_REUSEADDR,&b_reuse,sizeof(int)); 
		if (res < 0) {
			SERVE_WARN("set data sock reuser error!");
		}
		memset(&server, 0, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port   = htons(port);
		server.sin_addr.s_addr = htonl(INADDR_ANY);
		len = sizeof(server);
		errno = 0;
		res = bind(listenFd, (struct sockaddr *)&server, len);
		if (res < 0) {
	    	close(listenFd);
			SERVE_ERROR("Bind ip error!errno:%d,%s\n",errno,strerror(errno));
	    	break;
		}

		errno = 0;
		res = listen(listenFd, 20);
		if (res < 0) {
			SERVE_ERROR("listen error!errno:%d,%s\n",errno,strerror(errno));
			break;
		}
		
		return 0;
	} while(0);

	if (g_serverListenFd.authFd > 0) close(g_serverListenFd.authFd);
	if (g_serverListenFd.dataFd > 0) close(g_serverListenFd.dataFd);
	g_serverListenFd.port = 0;	
	
	return -1;
}

int waitAuthRequest(struct sockaddr_in * clientAddr)
{
	int socfFd;
	socklen_t len;
	do {
       socfFd = accept(g_serverListenFd.authFd, (struct sockaddr *)&clientAddr, &len);
    	if(socfFd < 0) {
        	continue;
    	}
    	break;
	} while (1);
	return socfFd;
}
/*
 * 没有sessionID时分配ID并加入队列，否则回复对应sessionID对应的信息
 */
int processClientRequest(int sockFd,struct sockaddr_in *clientAddr)
{
	AUTH_HEADER_REQUEST request;
	AUTH_HEADER_RESPONSE response;
	int res;
	bool ret;
	int size;
	CLIENT_QUEUE connectiInfo;
	
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));

	size =  recv(sockFd, (void *)&request, sizeof(request), 0);
	if (size < sizeof(request)) {
		return -1;
	}

	SERVE_INFO("client type:%d\t connect type:%d",request.clientType, request.connectType);
	
	if (request.clientType == E_CLIENT_GET) {
		//bool addConnectToQueue(CLIENT_QUEUE info);
	} else if (request.clientType == E_CLIENT_PUT) {
		memset(&connectiInfo, 0, sizeof(connectiInfo));
		ret = findConnectOfQueue(request.sessionId, &connectiInfo);
		if (!ret) {
			response.result = -1;
		} else {
			response.result = 0;
			//strcpy(connectiInfo.clientPutIp, server.sin_addr.s_addr);
			response.connectType = request.connectType;
			response.encryptType = request.encryptType;
			response.sessionId = connectiInfo.sessionId;
			strcpy(response.ip, connectiInfo.clientGetIp);
		}
		
	}

	size = send(sockFd, (const void *) &response, sizeof(AUTH_HEADER_RESPONSE), 0);
	if (size < 0) {
		SERVE_ERROR("send auth data error!\n");
	}

	close(sockFd);	
	return 0;
}

int removeConnectToQueue(unsigned int ssionId)
{
	return 0;
}

bool findConnectOfQueue(unsigned int sessionId, CLIENT_QUEUE *conectInfo)
{
	int i;
	bool result = false;
	time_t timeNow;

	pthread_mutex_lock(&g_connecQueueLock);
	for(i = 0; i < MAX_SESSION_NUM; i++) {
		if (!g_connecQueue[i].sessionStatus) continue;
		if (g_connecQueue[i].sessionId == sessionId) {
			result = true;
		}
	}
	do {
		timeNow = time(NULL);

		if (timeNow > g_connecQueue[i].terminalTime) {
			g_connecQueue[i].sessionStatus = false;
			result = false;
			break;
		}
		
		if (result) {
			memcpy(conectInfo, &g_connecQueue[i], sizeof(CLIENT_QUEUE));
		}
	} while (0);
	pthread_mutex_unlock(&g_connecQueueLock);
	return result;
}

bool addConnectToQueue(CLIENT_QUEUE info)
{
	return true;
}
