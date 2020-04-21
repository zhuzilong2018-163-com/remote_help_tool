#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#ifdef __cplusplus 
extern "C" { 
#endif 

#define ID_CODE_LEN  128
#define IP_LEN       128
typedef enum {
	E_CONNECT_P2P   = 0, //客户端通过P2P方式连接
	E_CONNECT_RELAT = 1, //客户端通过服务器中转连接
	E_CONNECT_NULL  = 2
} E_CONNECT_TYPE;

typedef enum {
	E_ENCYRPT_NULL = 0,
} E_ENCYRPT_TYPE;

typedef enum {
	E_CLIENT_GET = 1, //提供支持的一方
	E_CLIENT_PUT = 2, //接收支持的一方
} E_CLIENT_TYPE;

typedef struct {
	E_CONNECT_TYPE connectType;
	E_ENCYRPT_TYPE encryptType;
	E_CLIENT_TYPE clientType;
	char commType; // 1 UDP 2 TCP
	char idCode[ID_CODE_LEN];
} AUTH_HEADER_REQUEST;

typedef struct {
	E_CONNECT_TYPE connectType;
	E_ENCYRPT_TYPE encryptType;
	unsigned int connCode;     // 用于后续客户端通信时的识别ID，由服务器分配
	char IP_TYPE;              //  1 ipv4 2 ipv6
	char ip[IP_LEN];           // p2p连接时存储对方客户端的IP地址 格式 ip:port
} AUTH_HEADER_RESPONSE;

typedef  struct {
	E_CONNECT_TYPE connectType;
	E_ENCYRPT_TYPE encryptType;
	unsigned int connCode;
	unsigned int totalNum;
	unsigned int index;
	unsigned int data_len;
	char *data;
} DATA_TRANSPORT_REQUEST;

typedef  struct {
	E_CONNECT_TYPE connectType;
	E_ENCYRPT_TYPE encryptType;
	unsigned int totalNum;
	unsigned int index;
	bool result;              // 数据包接收结果
	bool reSend;              // 是否需要重新发送
} DATA_TRANSPORT_REQUEST;

#ifdef __cplusplus 
}
#endif

#endif
