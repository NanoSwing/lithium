#ifndef LI_BASE_ERROR_H
#define LI_BASE_ERROR_H

#include "base/base_types.h"
#include "base/base_defines.h"
#include "base/base_string.h"

typedef enum {
	LI_ERROR_SEVERITY_HEAVY = 0,
	LI_ERROR_SEVERITY_MEDIUM,
	LI_ERROR_SEVERITY_LIGHT
} LiErrorSeverity;

typedef struct {
	LiErrorSeverity severity;
	LiString message; 
} LiError;

typedef void (*LiErrorCallback)(const LiError error);

LIAPI void liErrorInit(void);
LIAPI void liErrorCleanup(void);
LIAPI void liErrorFormat(LiErrorSeverity severity, const char *message, ...); 
LIAPI void liError(LiErrorSeverity severity, char *message); 
LIAPI const LiError *liErrorGet(U8 *count);
LIAPI void liErrorCallback(LiErrorCallback callback);

#endif // LI_BASE_ERROR_H
