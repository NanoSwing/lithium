#ifndef LI_PLATFORM_MEMORY_H
#define LI_PLATFORM_MEMORY_H

#include "base/base_types.h"
#include "base/base_defines.h"

LIAPI void *liMemoryReserve(U64 size);
LIAPI void liMemoryCommit(void *ptr, U64 size);
LIAPI void liMemoryDecommit(void *ptr, U64 size);
LIAPI void liMemoryRelease(void *ptr);
LIAPI U64 liMemoryCalculateCommit(U64 size);

// Helpers
#define liGigabytes(n) ((U64) n << 30)

#endif // LI_PLATFORM_MEMORY_H
