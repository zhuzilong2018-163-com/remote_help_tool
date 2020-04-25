#include "aes.h"
#include "stdio.h"
int main(void){
	/*
	pt：原文16字节-->密文
	key：原密钥16字节
	skey：密钥扩展44long
	sbox：s盒
	*/
 
	unsigned char pt[17],key[17];
	unsigned char expansionkey[15*16];
	int i;
	printf("please input plaintext\n");//输入无格式的字符串字符个数不得少于六个！！！！尽量用不同的数字或字母
	scanf("%s",pt);
	printf("please input key\n");//输入加密钥匙密匙个数不得低于六个！！！！尽量用不同的数字或字母
	scanf("%s",key);
 
	/*加密*/
	ScheduleKey(key,expansionkey,4,10);	//1、密钥扩展生成
	AesEncrypt(pt,expansionkey,10);		//2、AES 加密
	printf("AesEncrypt text is: ");	//输出密码文件
	for (i = 0; i < 16; i++)
	{
		printf("%02x ", pt[i]);
	}
	printf("\n");
	printf("\n");
 
	/*解密*/
	Contrary_AesEncrypt(pt,expansionkey,10);//AES 解密
	printf("after Contrary_AesEncrypt,plaintext is: ");//将解密文件输出
	for (i = 0; i < 16; i++)
	{
		printf("%c ", pt[i]);
	}
	printf("\n");
	printf("\n");
	while(1);
	return 0;
}

