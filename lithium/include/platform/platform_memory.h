#ifndef LI_PLATFORM_MEMORY_H
#define LI_PLATFORM_MEMORY_H

#include "base/base_types.h"
#include "base/base_defines.h"

LIAPI void *liMemoryReserve(Usize size);
LIAPI void liMemoryCommit(void *ptr, Usize size);
LIAPI void liMemoryDecommit(void *ptr, Usize size);
LIAPI void liMemoryRelease(void *ptr);

#endif // LI_PLATFORM_MEMORY_H
