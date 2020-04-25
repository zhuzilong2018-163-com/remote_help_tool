#ifndef _CLIENT_H_
#define _CLIENT_H_

#ifdef __cplusplus 
extern "C" { 
#endif 

//宏定义
//模式选择相关
#define HELPER "helper"
#define BENEFICIARY "beneficiary"
#define adas "beneficiary"

//调试相关
#define CLIENT "CLINET"

//枚举
//模式选择
typedef enum {
	E_MODE_HELPER = 1,      //HELPER模式
	E_MODE_BENEFICIARY = 2, //BENEFICIARY模式
	E_MODE_BUTT,
} E_CLIENT_TYPE;



#ifdef __cplusplus 
}
#endif

#endif

