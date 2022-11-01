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

// Read contents of filename. Returns NULL if operation fails, returns a pointer otherwise.
LIAPI char *liFileRead(LiArena *arena, const char *filename);
// Write content to filename.
LIAPI void liFileWrite(const char *filename, const LiString content, LiFileMode write_mode);
// Create a file at filename.
LIAPI void liFileCreate(const char *filename);
// Append content to filename.
LIAPI void liFileAppend(const char *filename, const LiString content, LiFileMode append_mode);
// Returns true if filename exists.
LIAPI B8 liFileExists(const char *filename);

#endif
