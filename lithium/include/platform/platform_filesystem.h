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

// Read contents of filename. Returns NULL if file coudln't be opened, returns a pointer otherwise.
LIAPI char *liFileRead(LiArena *arena, const char *filename);
// Write content to filename. Returns false if file couldn't be opened.
LIAPI B8 liFileWrite(const char *filename, const LiString content, LiFileMode write_mode);
// Create a file at filename. Return false if file couldn't be created.
LIAPI B8 liFileCreate(const char *filename);
// Append content to filename. Return false if file couldn't be opened or created.
LIAPI B8 liFileAppend(const char *filename, const LiString content, LiFileMode append_mode);
// Returns true if filename exists.
LIAPI B8 liFileExists(const char *filename);

#endif
