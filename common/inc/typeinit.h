#ifndef __TYPEINIT_H
#define __TYPEINIT_H


#ifdef __cplusplus 
extern "C" { 
#endif 

typedef signed char          int8;
typedef unsigned char        uint8;
typedef short                int16;
typedef unsigned short       uint16;
typedef int                  int32;
typedef unsigned             uint32;
typedef long long            int64;
typedef unsigned long long   uint64;

typedef enum {
    FALSE = 0,
	TURE  = 1,
} E_BOOL_TYPE;

typedef enum {
	FAIL   = -1,
	STR_NULL   = 0,
	SUCCESS = 1, 
} E_RETURN_TYPE;


#ifdef __cplusplus 
}
#endif


#endif
