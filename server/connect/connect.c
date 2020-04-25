#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"
#include "logPrint.h"
#include "connect.h"

int connectInit(unsigned short int port)
{
	int listenFd = -1;
	int res;
	socklen_t len;
	struct sockaddr_in server;
	
	listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenFd < 0) {
    	SERVE_ERROR("Create server error!");
    	return -1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port   = htons(port);
	server.sin_addr.s_addr  = htonl(INADDR_ANY);
	len = sizeof(server);
	res = bind(listenFd, (struct sockaddr *)&server, len);
	if (res < 0) {
    	close(listenFd);
		SERVE_ERROR("Bind ip error!");
    	return -1;
	}

	return listenFd;
}

