#ifndef LI_BASE_LOGGING_H
#define LI_BASE_LOGGING_H

#include "base/base_defines.h"
#include "base/base_types.h"

typedef enum {
	LI_LOG_LEVEL_FATAL,
	LI_LOG_LEVEL_ERROR,
	LI_LOG_LEVEL_WARN,
	LI_LOG_LEVEL_INFO,
	LI_LOG_LEVEL_DEBUG,
	LI_LOG_LEVEL_TRACE,
	LI_LOG_LEVEL_COUNT
} LiLogLevel;

LIAPI void liLog(LiLogLevel level, const char *file, U32 line, const char *format, ...);

#define liLogFatal(message, ...) liLog(LI_LOG_LEVEL_FATAL, __FILE__, __LINE__, message, ##__VA_ARGS__)
#define liLogError(message, ...) liLog(LI_LOG_LEVEL_ERROR, __FILE__, __LINE__, message, ##__VA_ARGS__)
#define liLogWarn(message, ...)  liLog(LI_LOG_LEVEL_WARN,  __FILE__, __LINE__, message, ##__VA_ARGS__)
#define liLogInfo(message, ...)  liLog(LI_LOG_LEVEL_INFO,  __FILE__, __LINE__, message, ##__VA_ARGS__)
#define liLogDebug(message, ...) liLog(LI_LOG_LEVEL_DEBUG, __FILE__, __LINE__, message, ##__VA_ARGS__)
#define liLogTrace(message, ...) liLog(LI_LOG_LEVEL_TRACE, __FILE__, __LINE__, message, ##__VA_ARGS__)

#endif // LI_BASE_LOGGING_H
