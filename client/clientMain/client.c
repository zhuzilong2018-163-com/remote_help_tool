#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "logPrint.h"
#include "client.h"

//全局变量
//模式判断变量
unsigned char g_mode = 0;

int main(int argc, char *argv[])
{
    if ((argc == 2) && (strcmp(HELPER, argv[1]) == 0)) {
        g_mode = E_MODE_HELPER;
	    printf("You select Helper mode\n");
        INFO_LOG(CLIENT, "%s\n","You select Helper mode\n");
    } else if ((argc == 2) && (strcmp(HELPER, argv[1]) == 0)) {
        g_mode = E_MODE_BENEFICIARY;
	    printf("You select Beneficiary mode\n");
        INFO_LOG(CLIENT, "%s\n","You select Beneficiary mode\n");
    } else {
        printf("Parameter error\n");
        ERROR_LOG(CLIENT, "%s\n","Parameter error\n");
    }
    
    return 0;
}
