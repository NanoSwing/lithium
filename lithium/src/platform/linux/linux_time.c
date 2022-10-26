#include "base/base_context_crack.h"

#ifdef LI_OS_LINUX

#include "platform/platform_time.h"

#include <time.h>

F64 liTimeGet(void)
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC_RAW, &now);
	return (now.tv_sec * 1E6 + now.tv_nsec) * 0.001f;
}

void liTimeSleep(U64 ms)
{
	struct timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;
	nanosleep(&ts, 0);
}

LiDateTime liTimeGetDateTime(void)
{
	LiDateTime date = {0};

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	date.year   = tm.tm_year + 1900;
	date.month  = tm.tm_mon + 1;
	date.day    = tm.tm_mday;
	date.hour   = tm.tm_hour;
	date.minute = tm.tm_min;
	date.second = tm.tm_sec;

	return date;
}

#endif // LI_OS_LINUX
