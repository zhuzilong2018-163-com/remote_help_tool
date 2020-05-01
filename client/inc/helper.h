#ifndef _HELPER_H_
#define _HELPER_H_

#ifdef __cplusplus 
extern "C" { 
#endif 
#include "typeinit.h"
extern uint8 g_auc_pt[17], g_auc_key[17];//pt
extern uint8 g_auc_expansionkey[15*16]; //密钥扩展之后的数组


//函数
extern int32 helper_mode_start(void);
extern int32 helper_thread_creat(void);


#ifdef __cplusplus 
}
#endif

#endif

