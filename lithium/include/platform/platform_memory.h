#ifndef LI_PLATFORM_MEMORY_H
#define LI_PLATFORM_MEMORY_H

#include "base/base_types.h"
#include "base/base_defines.h"

// Reserve size amount of bytes.
LIAPI void *liMemoryReserve(U64 size);
// Commit size amount bytes at ptr location in memory.
LIAPI void liMemoryCommit(void *ptr, U64 size);
// Decommit size amount bytes at ptr location in memory.
LIAPI void liMemoryDecommit(void *ptr, U64 size);
// Release reserved memory.
LIAPI void liMemoryRelease(void *ptr);
// Returns size snapped to commit size.
LIAPI U64 liMemoryCalculateCommit(U64 size);

// Converts n into n gigabytes.
#define liGigabytes(n) ((U64) n << 30)
// Converts n into n megabytes.
#define liMegabytes(n) ((U64) n << 20)
// Converts n into n kilobytes.
#define liKilobytes(n) ((U64) n << 10)

#endif // LI_PLATFORM_MEMORY_H
