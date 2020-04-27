#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "server.h"
#include "logPrint.h"
#include "connect.h"

SERVE_SOCKET g_serverListenFd = {
	.authFd = -1,
	.dataFd = -1,
	.port = 0,
};


int connectInit(unsigned short int port)
{
	int listenFd = -1;
	int res;
	socklen_t len;
	struct sockaddr_in server;

	do {

		g_serverListenFd.port = port;
	
		g_serverListenFd.authFd = socket(AF_INET, SOCK_STREAM, 0);
		if (listenFd < 0) {
	    	SERVE_ERROR("Create server auth listen error!");
	    	break;
		}

		g_serverListenFd.dataFd = socket(AF_INET, SOCK_DGRAM, 0);
		if (listenFd < 0) {
	    	SERVE_ERROR("Create server error!");
	    	break;
		}

		memset(&server, 0, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port   = htons(port);
		server.sin_addr.s_addr = htonl(INADDR_ANY);
		len = sizeof(server);
		res = bind(listenFd, (struct sockaddr *)&server, len);
		if (res < 0) {
	    	close(listenFd);
			SERVE_ERROR("Bind ip error!");
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

int addConnectToqueue(int sockFd,struct sockaddr_in *clientAddr)
{
	return 0;
}
