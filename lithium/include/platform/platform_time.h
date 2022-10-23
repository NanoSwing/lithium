#ifndef LI_PLATFORM_TIME_H
#define LI_PLATFORM_TIME_H

#include "base/base_defines.h"
#include "base/base_types.h"

typedef struct {
	U32 year;
	U8 month;
	U8 day;
	U8 hour;
	U8 minute;
	U8 second;
} LiDate;

LIAPI F64 liTimeGet(void);
LIAPI void liTimeSleep(U64 ms);
LIAPI LiDate liTimeGetDate(void);

#endif // LI_PLATFORM_TIME_H
