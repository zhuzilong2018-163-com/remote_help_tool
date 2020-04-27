#include <stdio.h>
#include <string.h>
#include "server.h"
#include "logPrint.h"
#include "connect.h"
#include "protocol.h"

int main(int argc, char *argv[])
{
	int res;
	int sockFd;
	struct sockaddr_in clientAddr;
	
	res = connectInit(SERVER_PORT);
	if (res < 0) {
		SERVE_ERROR("connectInit error!");
		return 0;
	}

	while(1) {
		SERVE_INFO("--------main function run!--------");
		memset(&clientAddr, 0, sizeof(clientAddr));
		sockFd = waitAuthRequest(&clientAddr);
		if (sockFd < 0) continue;

		
		
	}

	return 0;
}
