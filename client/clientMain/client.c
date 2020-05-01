#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "logPrint.h"
#include "helper.h"
#include "client.h"
#include "typeinit.h"

//全局变量
//模式判断变量
uint8 g_mode = 0;

int main(int argc, char *argv[])
{
    if ((argc == 2) && (strcmp(HELPER, argv[1]) == 0)) {
        g_mode = E_MODE_HELPER;
        INFO_LOG(DEBUG_CLIENT, "%s\n", "You select Helper mode\n");
    } else if ((argc == 2) && (strcmp(BENEFICIARY, argv[1]) == 0)) {
        g_mode = E_MODE_BENEFICIARY;
        INFO_LOG(DEBUG_CLIENT, "%s\n", "You select Beneficiary mode\n");
    } else {
        ERROR_LOG(DEBUG_CLIENT, "%s\n", "Parameter error\n");
    }

    if (g_mode == E_MODE_HELPER) {
        INFO_LOG(DEBUG_CLIENT, "%s\n", "It's initing\n");
        helper_mode_start();
    } else if (g_mode == E_MODE_BENEFICIARY) {
        INFO_LOG(DEBUG_CLIENT, "%s\n", "It's initing\n");
    } else {
        WARN_LOG(DEBUG_CLIENT, "%s\n", "Please select mode again!!\n");
    }

    return 0;
}
