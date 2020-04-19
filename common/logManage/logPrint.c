#include <stdio.h>
#include <string.h>
#include <stdarg.h> 
#include "logPrint.h"


void logPrint(char level, const char *moduleName, const char *fileName, const char *functionName,int lineNum, const char *format,...)
{
	char tempPrint[2048];
	int lenOfTemp = 0;
	va_list args;

	if(level == DEBUG) {
		sprintf(tempPrint, "DEBUG] ");
	} else if (level == INFO) {
		sprintf(tempPrint, "INFO] ");
	} else if (level == WARN) {
		sprintf(tempPrint, "WARN] ");
	} else if (level == ERROR) {
		sprintf(tempPrint, "ERROR] ");
	} else return;

	lenOfTemp = strlen(tempPrint);
	if (moduleName != NULL)
		sprintf(tempPrint + lenOfTemp, "%s/",moduleName);

	lenOfTemp = strlen(tempPrint);
	if (fileName != NULL)
		sprintf(tempPrint + lenOfTemp, "%s/",fileName);

	lenOfTemp = strlen(tempPrint);
	if (functionName != NULL)
		sprintf(tempPrint + lenOfTemp, "%s:",functionName);

	lenOfTemp = strlen(tempPrint);
	sprintf(tempPrint + lenOfTemp, "%d  ",lineNum);

	va_start(args, format);
	vsprintf(&tempPrint[strlen(tempPrint)], format, args);
	va_end(args);
	
	printf("%s\n",tempPrint);

}

