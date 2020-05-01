#ifndef _CLIENT_H_
#define _CLIENT_H_

#ifdef __cplusplus 
extern "C" { 
#endif 

//宏定义
//模式选择相关
#define HELPER "helper"
#define BENEFICIARY "beneficiary"

//调试宏定义
#define DEBUG_CLIENT "CLINET"
#define DEBUG_HELPER "HELPER"
#define DEBUG_BENEFICIARY "BENEFICIARY"
#define DEBUG_MONITOR "MONITOR"

//认证加密的密钥
#define KEY "Woshimiyao"

//显示进程的生成脚本
#define CREAT_PROCESS_MONITOR "sh run_monitor.sh"

//枚举
//模式选择
typedef enum {
	E_MODE_HELPER = 1,      //HELPER模式
	E_MODE_BENEFICIARY = 2, //BENEFICIARY模式
	E_MODE_BUTT,
} E_CLIENT_MDOE_TYPE;

#ifdef __cplusplus 
}
#endif

#endif

