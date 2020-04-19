#ifndef _SERVER_H_
#define _SERVER_H_

#define SERVE_DEBUG(format,...) DEBUG_LOG("SERVER",format,##__VA_ARGS__)
#define SERVE_INFO(format,...) INFO_LOG("SERVER",format,##__VA_ARGS__)
#define SERVE_WARN(format,...) WARN_LOG("SERVER",format,##__VA_ARGS__)
#define SERVE_ERROR(format,...) ERROR_LOG("SERVER",format,##__VA_ARGS__)

#endif
