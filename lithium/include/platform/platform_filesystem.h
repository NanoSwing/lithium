#ifndef LI_PLATFORM_FILESYSTEM_H
#define LI_PLATFORM_FILESYSTEM_H

#include "base/base_types.h"
#include "base/base_defines.h"
#include "base/base_arena.h"
#include "base/base_string.h"

typedef enum {
	LI_FILE_MODE_BINARY,
	LI_FILE_MODE_NORMAL,
} LiFileMode;

LIAPI char *liFileRead(LiArena *arena, const char *filepath);
LIAPI void liFileWrite(const char *filepath, const LiString content, LiFileMode write_mode);
LIAPI void liFileCreate(const char *filepath);
LIAPI void liFileAppend(const char *filepath, const LiString content, LiFileMode append_mode);
LIAPI B8 liFileExists(const char *filepath);

#endif
