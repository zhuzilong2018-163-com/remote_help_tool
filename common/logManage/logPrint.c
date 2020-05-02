#include <stdio.h>
#include <string.h>
#include <stdarg.h> 
#include <pthread.h>
#include <time.h>
#include "logPrint.h"

 pthread_mutex_t g_printLock = PTHREAD_MUTEX_INITIALIZER;
void logPrint(char level, const char *moduleName, const char *fileName, const char *functionName,int lineNum, const char *format,...)
{
	pthread_mutex_lock(&g_printLock);
	char tempPrint[2048];
	int lenOfTemp = 0;
	va_list args;

	if(level == DEBUG) {
		sprintf(tempPrint, "[DEBUG]");
	} else if (level == INFO) {
		sprintf(tempPrint, "[INFO ]");
	} else if (level == WARN) {
		sprintf(tempPrint, "[WARNG]");
	} else if (level == ERROR) {
		sprintf(tempPrint, "[ERROR]");
	} else {
		pthread_mutex_unlock(&g_printLock);
		return;
	}

	lenOfTemp = strlen(tempPrint);
	sprintf(tempPrint + lenOfTemp, "[%lu|",time(NULL));
	
	lenOfTemp = strlen(tempPrint);
	if (moduleName != NULL)
		sprintf(tempPrint + lenOfTemp, "%s|",moduleName);

	lenOfTemp = strlen(tempPrint);
	if (fileName != NULL)
		sprintf(tempPrint + lenOfTemp, "%s|",fileName);

	lenOfTemp = strlen(tempPrint);
	if (functionName != NULL)
		sprintf(tempPrint + lenOfTemp, "%s,",functionName);

	lenOfTemp = strlen(tempPrint);
	sprintf(tempPrint + lenOfTemp, "%d]  ",lineNum);
	


	va_start(args, format);
	vsprintf(&tempPrint[strlen(tempPrint)], format, args);
	va_end(args);
	
	printf("%s\n",tempPrint);

	lenOfTemp = strlen(tempPrint);
	sprintf(tempPrint + lenOfTemp, "\n");
	FILE *fp = fopen("/home/myshare/remote_help_tool/common/logManage/log.txt","a+");
	fwrite(tempPrint,1,strlen(tempPrint),fp);
	fclose(fp);
	
	pthread_mutex_unlock(&g_printLock);
}

