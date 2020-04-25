#ifndef _AES_H_
#define _AES_H_

#ifdef __cplusplus 
extern "C" { 
#endif 

extern void ScheduleKey(unsigned char *inkey,unsigned char *outkey,int Nk,int Nr);//安排一个保密密钥使用
extern void AesEncrypt(unsigned char *blk,unsigned char *expansionkey,int Nr);
extern void Contrary_AesEncrypt(unsigned char *blk,unsigned char *expansionkey,int Nr);

#ifdef __cplusplus 
}
#endif

#endif

