#ifndef _LOG_PRINT_H
#define _LOG_PRINT_H

#ifdef __cplusplus 
extern "C" { 
#endif 


#define DEBUG 0
#define INFO  1
#define WARN  2
#define ERROR 3

#define DEBUG_LOG(moduleName,format,...)   logPrint(DEBUG, moduleName, __FILE__, __FUNCTION__, __LINE__, const char *format,...)
#define INFO_LOG(moduleName,format,...)    logPrint(INFO, moduleName, __FILE__, __FUNCTION__, __LINE__, const char *format,...)
#define WARN_LOG(moduleName,format,...)    logPrint(WARN, moduleName, __FILE__, __FUNCTION__, __LINE__, const char *format,...)
#define ERROR_LOG(moduleName,format,...)   logPrint(ERROR, moduleName, __FILE__, __FUNCTION__, __LINE__, const char *format,...)
void logPrint(char level, const char *moduleName, const char *fileName, const char *functionName,int lineNum, const char *format,...);

#ifdef __cplusplus 
}
#endif

#endif
