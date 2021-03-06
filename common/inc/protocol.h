#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#ifdef __cplusplus 
extern "C" { 
#endif 

#include <stdbool.h>
#include <time.h>
#include <sys/socket.h>
#include "typeinit.h"

#define SERVER_IP    "47.93.49.83"
#define SERVER_PORT  443
#define ID_CODE_LEN  128
#define IP_LEN       128

typedef enum {
	E_CONNECT_P2P   = 0, //客户端通过P2P方式连接
	E_CONNECT_RELAY = 1, //客户端通过服务器中转连接
	E_CONNECT_NULL  = 2
} E_CONNECT_TYPE;

typedef enum {
	E_ENCYRPT_NULL = 0,
} E_ENCYRPT_TYPE;

typedef enum {
	E_CLIENT_GET = 1, //提供支持的一方
	E_CLIENT_PUT = 2, //接收支持的一方
} E_CLIENT_TYPE;

typedef enum {
	E_CMD_MODE = 1, //提供支持的一方
	E_COMMUNICATE_MODE = 2, //接收支持的一方
} E_COMMUNICATE_TYPE;


typedef enum {
	E_COMMUNICATE = 0,
    E_CMD    = 1,
} E_MESSAGE_TYPE;

/*
typedef enum {
	E_CONNECT_CTL_STOP = 1,
	E_CONNECT_CTL_RENEW = 2,
	E_CONNECT_CTL_PAUSE = 3,
} E_CONNECT_CTL_TYPE;
*/

typedef struct {
	E_CONNECT_TYPE connectType;
	E_ENCYRPT_TYPE encryptType;
	E_CLIENT_TYPE clientType;
	time_t sessionId;           //发起方该成员无效
	char key[ID_CODE_LEN];     //用于后续数据发送时加密
} AUTH_HEADER_REQUEST;

typedef struct {
	E_CONNECT_TYPE connectType;
	E_ENCYRPT_TYPE encryptType;
	time_t sessionId;
	int result;                // 等于0表示请求成功，小于0代表失败，数值为错误码
	char ip[IP_LEN];           // p2p连接时存储对方客户端的IP地址 格式 ip:port
	char key[ID_CODE_LEN];     //用于后续数据发送时加密
} AUTH_HEADER_RESPONSE;

typedef  struct {
	E_ENCYRPT_TYPE encryptType;
	unsigned int sessionId;
	unsigned int totalNum;
	unsigned int index;
	time_t	timeStamp;       
	unsigned int data_len;
	char *data;
} DATA_TRANSPORT_REQUEST;

typedef  struct {
	E_ENCYRPT_TYPE encryptType;
	unsigned int sessionId;
	unsigned int totalNum;
	unsigned int index;
	bool result;              // 数据包接收结果
	bool reSend;              // 是否需要重新发送
} DATA_TRANSPORT_RESPONSE;

typedef  struct {
	int32 sock;
    socklen_t len;
    struct sockaddr_in serv_adr;
    struct sockaddr_in from_adr;
} PTHREAD_ARGV;


/*
typedef  struct {
	E_CONNECT_CTL_TYPE cmd;
	unsigned int sessionId;
	time_t timeout;
	unsigned int dataLen;
	char *data;
} DATA_TRANSPORT_CTL_REQUEST;

typedef  struct {
	E_CONNECT_CTL_TYPE cmd;
	unsigned int sessionId;
	int result;
} DATA_TRANSPORT_CTL_RESPOSE;
*/

#ifdef __cplusplus 
}
#endif

#endif
