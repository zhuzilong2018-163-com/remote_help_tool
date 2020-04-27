#include <stdio.h>
#include "server.h"
#include "logPrint.h"
#include "connect.h"
#include "protocol.h"

int main(int argc, char *argv[])
{
	int listenHandle = -1;
	
	listenHandle = connectInit(SERVER_PORT);
	if (listenHandle < 0) {
		SERVE_ERROR("connectInit error!");
		return 0;
	}

	while(1) {
		SERVE_INFO("--------main function run!--------");
		waitAuthRequest();

		
	}

	return 0;
}
