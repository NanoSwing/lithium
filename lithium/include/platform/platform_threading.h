#ifndef LI_PLATFORM_THREADING_H
#define LI_PLATFORM_THREADING_H

#include "base/base_types.h"
#include "base/base_defines.h"
#include "base/base_arena.h"

typedef U64 LiThread;
typedef struct LiMutex LiMutex;
typedef void *(*LiThreadFunc)(void *arg);

LIAPI LiThread liThreadCreate(LiThreadFunc thread_func, void *arg);
LIAPI void liThreadDestroy(LiThread thread);
LIAPI void liThreadWait(LiThread thread, void **output);
LIAPI LiThread liThreadGetSelf(void);

LIAPI LiMutex *liMutexCreate(LiArena *arena);
LIAPI void liMutexDestroy(LiMutex *mutex);
LIAPI void liMutexLock(LiMutex *mutex);
LIAPI void liMutexUnlock(LiMutex *mutex);

#endif // LI_PLATFORM_THREADING_H
