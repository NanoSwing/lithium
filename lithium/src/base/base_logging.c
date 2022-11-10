#include "base/base_logging.h"
#include "platform/platform_time.h"
#include "base/base_context_crack.h"

#ifdef LI_OS_WINDOWS
#include <Windows.h>
#endif // LI_OS_WINDOWS
#include <stdarg.h>
#include <stdio.h>

void liLog(LiLogLevel level, const char *file, U32 line, const char *format, ...)
{
	static const char *prefix[LI_LOG_LEVEL_COUNT] = {
		"FATAL",
		"ERROR",
		"WARN ",
		"INFO ",
		"DEBUG",
		"TRACE"
	};

	char buffer[1024] = {0};

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	LiDateTime time = liTimeGetDateTime();

#ifdef LI_OS_LINUX
	const char *color[LI_LOG_LEVEL_COUNT] = {
		"\033[7;31m",
		"\033[0;91m",
		"\033[0;33m",
		"",
		"\033[0;34m",
		"\033[0;35m"
	};
	// Print prefix.
	printf("%s%.2d:%.2d:%.2d %s %s:%d: ", color[level], time.hour, time.minute, time.second, prefix[level], file, line);
	for (U32 i = 0; buffer[i] != '\0'; i++) {
		if (buffer[i] == '\r') {
			i++;
			continue;
		}
		if (buffer[i] == '\n') {
			printf("\n%s%.2d:%.2d:%.2d %s %s:%d: ", color[level], time.hour, time.minute, time.second, prefix[level], file, line);
			i++;
		}
		printf("%c", buffer[i]);
	}
	printf("\n\033[0;0m");
#endif // LI_OS_LINUX
#ifdef LI_OS_WINDOWS
	const U32 RESET_COLOR = 7;
	HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	U32 color[LI_LOG_LEVEL_COUNT] = {
		64,
		4,
		6,
		7,
		1,
		13
	};
	// Set output color
	SetConsoleTextAttribute(console_handle, color[level]);
	// Print prefix.
	printf("%.2d:%.2d:%.2d %s %s:%d: ", time.hour, time.minute, time.second, prefix[level], file, line);
	for (U32 i = 0; buffer[i] != '\0'; i++) {
		if (buffer[i] == '\r') {
			i++;
			continue;
		}
		if (buffer[i] == '\n') {
			printf("\n%.2d:%.2d:%.2d %s %s:%d: ", time.hour, time.minute, time.second, prefix[level], file, line);
			i++;
		}
		printf("%c", buffer[i]);
	}
	printf("\033[0;0m\n");
	SetConsoleTextAttribute(console_handle, RESET_COLOR);
#endif // LI_OS_WINDOWS
}
