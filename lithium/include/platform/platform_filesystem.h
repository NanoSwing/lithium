#ifndef LI_PLATFORM_FILESYSTEM_H
#define LI_PLATFORM_FILESYSTEM_H

#include "base/base_types.h"
#include "base/base_defines.h"
#include "base/base_arena.h"

typedef enum {
	LI_FILE_WRITE_MODE_BINARY,
	LI_FILE_WRITE_MODE_NORMAL,
} LiFileWriteMode;

LIAPI char *liFileRead(LiArena *arena, const char *filepath);
LIAPI void liFileWrite(const char *filepath, const char *content, U64 content_length, LiFileWriteMode write_mode);
LIAPI void liFileCreate(const char *filepath);
LIAPI void liFileAppend(const char *filepath, const char *content, U64 content_length);
LIAPI B8 liFileExists(const char *filepath);

#endif
