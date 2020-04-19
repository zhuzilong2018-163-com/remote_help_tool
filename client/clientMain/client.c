#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "logPrint.h"

//宏定义
//模式选择相关
#define HELPER "helper"
#define BENEFICIARY "beneficiary"



int main(int argc, char *argv[])
{
	if ((argc == 2) && (strcmp(HELPER, argv[1]) == 0)) {
		
	} else if ((argc == 2) && (strcmp(HELPER, argv[1]) == 0)) {
		    
	} else {
		ERROR_LOG("client", "Parameter error");
	}

	return 0;
}
