#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include "logPrint.h"
#include "server.h"
#include "connect.h"

bool g_pthreadRunFlag = false;
pthread_t g_taskProcessId = 0;

void *pthreadTaskProcess(void *arg);

int taskProcessInit(void)
{
	int res;
	
	res = pthread_create(&g_taskProcessId, NULL, pthreadTaskProcess, NULL);
	if (res < 0) {
		SERVE_ERROR("create taskProcess pthread error!\n");
	}
	return 0;
}

void stopTaskProcess(void)
{
	
}

void *pthreadTaskProcess(void *arg)
{
	while (g_pthreadRunFlag) {
		
	}
	return NULL;
}
