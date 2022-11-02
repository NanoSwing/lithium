#include "base/base_context_crack.h"
#ifdef LI_OS_WINDOWS

#include "platform/platform_time.h"

#include <Windows.h>

static F32 clock_freq = 0;
static LARGE_INTEGER start_time;

static void clock_setup(void)
{
	U64 freq;
	QueryPerformanceFrequency(&freq);
	clock_freq = 1.0f / (F32) freq;
	QueryPerformanceCounter(&start_time);
}

F64 liTimeGet(void)
{
	if (clock_freq == 0) {
		clock_setup();
	}

	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	return (F32) now.QuadPart * clock_freq;
}

void liTimeSleep(U64 ms)
{
	Sleep(ms);
}

LiDateTime liTimeGetDateTime(void)
{
	LiDateTime date = {0};

	SYSTEMTIME st, lt;

	GetLocalTime(&st);
	date.year = st.wYear;
	date.month = st.wMonth;
	date.day = st.wDay;
	date.hour = st.wHour;
	date.minute = st.wMinute;
	date.second = st.wSecond;

	return date;
}

#endif // LI_OS_WINDOWS