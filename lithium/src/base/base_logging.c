#include "base/base_logging.h"
#include "platform/platform_time.h"
#include "base/base_context_crack.h"

#include <stdarg.h>
#include <stdio.h>

// TODO: Impelemnt multiline printing so when it encounters a \n it starts a new log message instead of just printing a new line.
// Add file output.
// Add windows coloring
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
	printf("%s%.2d:%.2d:%.2d %s %s:%d: %s\033[0;0m\n", color[level], time.hour, time.minute, time.second, prefix[level], file, line, buffer);
#endif // LI_OS_LINUX
#ifdef LI_OS_WINDOWS
	printf("%.2d:%.2d:%.2d %s %s:%d: %s\n", time.hour, time.minute, time.second, prefix[level], file, line, buffer);
#endif // LI_OS_WINDOWS
}
