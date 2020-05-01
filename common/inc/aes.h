#ifndef _AES_H_
#define _AES_H_

#ifdef __cplusplus 
extern "C" { 
#endif 

#include "typeinit.h"


/*   加密解密用例
	ScheduleKey(key,expansionkey,4,10);	//1、密钥扩展生成
	AesEncrypt(pt,expansionkey,10);		//2、AES 加密
    Contrary_AesEncrypt(pt,expansionkey,10);//AES 解密
*/

//宏定义
#define KEY "Woshimiyao"

uint8 g_auc_pt[17], g_auc_key[17];//pt
uint8 g_auc_expansionkey[15*16]; //密钥扩展之后的数组


extern void ScheduleKey(uint8 *inkey, uint8 *outkey, int32 Nk,int32 Nr);//扩展密钥
extern void AesEncrypt(uint8 *blk, uint8 *expansionkey, int32 Nr);//加密
extern void Contrary_AesEncrypt(uint8 *blk, uint8 *expansionkey, int32 Nr);//解密

#ifdef __cplusplus 
}
#endif

#endif

