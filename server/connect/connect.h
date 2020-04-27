#ifndef _CONNECT_H
#define _CONNECT_H

#ifdef __cplusplus 
extern "C" { 
#endif

typedef struct {
	int authFd;
	int dataFd;
	unsigned short int port;
} SERVE_SOCKET;

int connectInit(unsigned short int port);


#ifdef __cplusplus 
}
#endif

#endif
