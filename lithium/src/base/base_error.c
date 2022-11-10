#include "base/base_error.h"
#include "base/base_arena.h"
#include "base/base_string.h"
#include "platform/platform_memory.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define MAX_ERROR_COUNT 64

// Global error storage.
// Double buffered error buffers to clear one while the users reads the other.
static LiError err_buff[2][MAX_ERROR_COUNT] = {0};
static LiArena *err_arena[2] = { NULL, NULL };
static U8 curr_buff = 0;
static U8 err_count = 0;
static LiErrorCallback local_callback = NULL;

static void internal_liErrorReport(LiError error)
{
	if (local_callback != NULL) {
		local_callback(error);
	}
	// Push back old errors.
	memmove(&err_buff[curr_buff][1], &err_buff[curr_buff][0], (MAX_ERROR_COUNT - 1) * sizeof(LiError));
	err_buff[curr_buff][0] = error;
	if (err_count != MAX_ERROR_COUNT) {
		err_count++;
	}
}

void liErrorInit(void)
{
	for (U8 i = 0; i < 2; i++) {
		err_arena[i] = liArenaCreate(liMegabytes(512), 8);
	}
}

void liErrorCleanup(void)
{
	for (U8 i = 0; i < 2; i++) {
		liArenaDestroy(err_arena[i]);
	}
}

void liErrorFormat(LiErrorSeverity severity, const char *message, ...)
{
	va_list ptr;
	va_start(ptr, message);
	char buff[1024];
	vsprintf(buff, message, ptr);
	va_end(ptr);

	internal_liErrorReport((LiError) { severity, liStringPush(err_arena[curr_buff], buff) });
}

void liError(LiErrorSeverity severity, char *message)
{
	internal_liErrorReport((LiError) { severity, liString(message) });
}

const LiError *liErrorGet(U8 *count)
{
	*count = err_count;
	// Swap buffers.
	curr_buff = !curr_buff;
	// Reset error count.
	err_count = 0;
	return err_buff[!curr_buff];
}

void liErrorCallback(LiErrorCallback callback)
{
	local_callback = callback;
}
